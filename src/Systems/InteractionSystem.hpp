#pragma once

#include <entt/entity/fwd.hpp>
#include <SFML/Graphics/View.hpp>

namespace sf
{
    struct Event;
    class RenderWindow;
}

namespace Systems
{

class InteractionSystem
{
public:
    InteractionSystem(entt::registry&, const sf::RenderWindow&);

    void setView(const sf::View& view);
    void handleEvent(const sf::Event& ev);

private:
    entt::registry& m_registry;
    const sf::RenderWindow& m_target;
    sf::View m_gameView;
};

}
