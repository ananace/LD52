#include "Application.hpp"
#include "Font.hpp"
#include <SFML/System/String.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Systems/InteractionSystem.hpp"
#include "Systems/RenderSystem.hpp"
#include "Systems/UpdateSystem.hpp"

#include "Components/Drawable.hpp"
#include "Components/Layer.hpp"
#include "Components/Updating.hpp"
#include "Events/Input.hpp"
#include "Events/Resize.hpp"

#include "States/Menu.hpp"

Application::Application()
    : m_mainRegistry()
    , m_eventDispatcher(m_mainRegistry.ctx().emplace<entt::dispatcher>())
{
}

void Application::init()
{
    m_window.create(sf::VideoMode({ 1366, 768 }), {"Ludum Dare 52"}, sf::Style::Default);
    m_window.setVerticalSyncEnabled(true);
    // m_window.setFramerateLimit(60);
}

void Application::run()
{
    Systems::RenderSystem renderSys(m_mainRegistry);
    Systems::UpdateSystem updateSys(m_mainRegistry);
    Systems::InteractionSystem interactSys(m_mainRegistry, m_window);

    sf::View gameView, mainView;
    mainView.setSize(sf::Vector2f(m_window.getSize()));
    mainView.setCenter(mainView.getSize() / 2.f);
    gameView = mainView;

    renderSys.setGameView(gameView);

    auto metaEnt = m_mainRegistry.create();

#ifndef NDEBUG
    sf::Text DTString("DT: 0 ms\nFPS: 0\nEntities: 0", Font::GetMonospaceFont());
    {
        DTString.setCharacterSize(14u);
        DTString.setFillColor(sf::Color::White);
        uint16_t fps = 0;
        float accum = 0;

        m_mainRegistry.emplace<Components::Updating<UpdateRate::Every>>(metaEnt, [&](float dt) {
          accum += dt;
          ++fps;

          if (accum > 1)
          {
              DTString.setString(
                  "DT: " + std::to_string(dt * 1000) + " ms\n"
                  "FPS: " + std::to_string(fps) + "\n"
                  "Entities: " + std::to_string(m_mainRegistry.alive()));

              accum = 0;
              fps = 0;
          }
        });
        m_mainRegistry.emplace<Components::Drawable>(metaEnt, &DTString);
        m_mainRegistry.emplace<Components::Layers::Overlay>(metaEnt);
    }
#endif

    {
        // Re-sort all drawables every 10 frames
        m_mainRegistry.emplace<Components::Updating<UpdateRate::Every10>>(metaEnt, [&](float) {
          m_mainRegistry.sort<Components::Drawable>([](const auto& lhs, const auto& rhs) { return lhs.z < rhs.z; });
        });
    }

    States::Menu::SetMenuState(m_mainRegistry);

    bool fullscreen = false;
    for (sf::Clock frameClock; m_window.isOpen();)
    {
        auto dt = frameClock.getElapsedTime();
        frameClock.restart();

        interactSys.setView(renderSys.getGameView());

        for (sf::Event ev; m_window.pollEvent(ev);)
        {
            switch (ev.type)
            {
            case sf::Event::Closed: m_window.close(); break;
            case sf::Event::Resized:
                mainView.setSize(sf::Vector2f(m_window.getSize()));
                mainView.setCenter(mainView.getSize() / 2.f);
                m_eventDispatcher.trigger(Events::Resize{ev});
                // printf("Windows resized to %.0fx%.0f\n", mainView.getSize().x, mainView.getSize().y);
                break;
            case sf::Event::KeyReleased:
                if (ev.key.alt && ev.key.code == sf::Keyboard::Enter)
                {
                    printf("Toggling fullscreen.\n");
                    fullscreen = !fullscreen;
                    if (fullscreen)
                        m_window.create(sf::VideoMode::getDesktopMode(), {"Ludum Dare 52"}, sf::Style::Fullscreen);
                    else
                        m_window.create(sf::VideoMode({ 1366, 768 }), {"Ludum Dare 52"}, sf::Style::Default);
                    m_window.setVerticalSyncEnabled(true);
                }
            case sf::Event::KeyPressed:
            case sf::Event::MouseWheelScrolled:
            case sf::Event::MouseButtonReleased:
                m_eventDispatcher.trigger(Events::Input{ev});
                break;

            case sf::Event::MouseMoved:
            case sf::Event::MouseButtonPressed:
                interactSys.handleEvent(ev);
                m_eventDispatcher.trigger(Events::Input{ev});
                break;

            default: break;
            }

        }

        updateSys.update(dt.asSeconds());

        m_window.clear();

        m_window.setView(mainView);
        renderSys.draw(dt, m_window);

        m_window.display();
    }
}
