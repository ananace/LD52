#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Application
{
public:
    Application();

    void init();
    void run();

private:
    entt::registry m_mainRegistry;
    entt::dispatcher& m_eventDispatcher;
    sf::RenderWindow m_window;
};
