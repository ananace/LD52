#include "RenderSystem.hpp"
#include <entt/entt.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "../Components/Drawable.hpp"
#include "../Components/Layer.hpp"
#include "../Components/Transformable.hpp"

using namespace Systems;

RenderSystem::RenderSystem(entt::registry& registry)
    : m_registry(registry)
{
}

void RenderSystem::setGameView(const sf::View& gameView)
{
    m_gameView = gameView;
}

sf::View RenderSystem::getGameView() const
{
    return m_gameView;
}

void RenderSystem::draw(const sf::Time& time, sf::RenderTarget& target)
{
    auto realView = target.getView();

    for (auto &&[ent, drawable]: m_registry.view<Components::Drawable, Components::Layers::Background>().each()) {
        target.draw(*drawable.drawable);
    }

    target.setView(m_gameView);

    for (auto &&[ent, drawable]: m_registry.view<Components::Drawable, Components::Layers::PreGame>().each())
    {
        target.draw(*drawable.drawable);
    }
    for (auto &&[ent, drawable]: m_registry.view<Components::Drawable, Components::Layers::Game>().each())
    {
        if (auto* transform = m_registry.try_get<Components::Transformable>(ent))
            target.draw(*drawable.drawable, transform->transformable);
        else
            target.draw(*drawable.drawable);
    }
    for (auto &&[ent, drawable]: m_registry.view<Components::Drawable, Components::Layers::PostGame>().each())
    {
        target.draw(*drawable.drawable);
    }

    m_gameView = target.getView();

    target.setView(realView);

    for (auto &&[ent, drawable]: m_registry.view<Components::Drawable, Components::Layers::UI>().each()) {
        target.draw(*drawable.drawable);
    }
    for (auto &&[ent, drawable]: m_registry.view<Components::Drawable, Components::Layers::Overlay>().each()) {
        target.draw(*drawable.drawable);
    }
}
