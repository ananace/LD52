#include "InteractionSystem.hpp"

#include "../Components/Interactive.hpp"

#include <entt/entt.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

using namespace Systems;

InteractionSystem::InteractionSystem(entt::registry& registry, const sf::RenderWindow& target)
    : m_registry(registry)
    , m_target(target)
{
}

void InteractionSystem::setView(const sf::View& view)
{
    m_gameView = view;
}

void InteractionSystem::handleEvent(const sf::Event& ev)
{
    sf::Vector2f mousePos;
    switch (ev.type)
    {
    case sf::Event::MouseMoved:
        mousePos = sf::Vector2f(ev.mouseMove.x, ev.mouseMove.y);
        break;

    case sf::Event::MouseButtonPressed:
    case sf::Event::MouseButtonReleased:
        mousePos = sf::Vector2f(ev.mouseButton.x, ev.mouseButton.y);
        break;

    default:
        return;
    }

    mousePos = m_target.mapPixelToCoords(sf::Vector2i(mousePos), m_gameView);
    for (auto &&[ent, interactive] : m_registry.view<Components::Interactive>().each())
    {
        auto pos = interactive.transform->getPosition();
        auto inside = (mousePos - pos).length() <= interactive.size;

        if (ev.type == sf::Event::MouseMoved)
            interactive.mouseMove(inside);
        else
            interactive.mouseClick();
    }
}
