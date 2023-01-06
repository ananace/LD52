#include "Game.hpp"
#include <entt/entt.hpp>

#include "../Components/Drawable.hpp"
#include "../Components/Layer.hpp"
#include "../Components/State.hpp"

#include "../Game/Plants/Pineapple.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

using namespace States;

Plants::Pineapple pineapple;
sf::RectangleShape background;

void Game::SetGameState(entt::registry& registry)
{
    auto state = registry.create();
    registry.emplace<Game>(state, registry, state);
}

Game::Game(entt::registry& registry, entt::entity entity)
    : m_registry(registry)
    , m_entity(entity)
{
    m_registry.emplace<Components::State>(entity);

    auto plant = m_registry.create();
    m_registry.emplace<Components::Drawable>(plant, &pineapple);
    m_registry.emplace<Components::Layers::Game>(plant);

    pineapple.setPosition({ 500, 500 });

    auto bgent = m_registry.create();
    m_registry.emplace<Components::Drawable>(bgent, &background);
    m_registry.emplace<Components::Layers::Background>(bgent);

    background.setFillColor({ 100, 149, 237 });
    background.setPosition({ 0, 0 });
    background.setSize({ 1366, 768 });
}

Game::~Game()
{
    printf("Destroying game state...\n");

    for (auto ent : m_entities)
        m_registry.destroy(ent);
}
