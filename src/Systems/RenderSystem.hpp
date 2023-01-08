#pragma once

#include <entt/entity/fwd.hpp>
#include <SFML/Graphics/View.hpp>

namespace sf
{
    struct Time;
    class RenderTarget;
}

namespace Systems
{

class RenderSystem
{
public:
    RenderSystem(entt::registry& registry);

    void setGameView(const sf::View& gameView);
    sf::View getGameView() const;

    void draw(const sf::Time& time, sf::RenderTarget& target);

private:
    entt::registry& m_registry;
    sf::View m_gameView;
};

}
