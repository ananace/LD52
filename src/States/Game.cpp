#include "Game.hpp"
#include <entt/entt.hpp>

#include "../Components/State.hpp"

using namespace States;

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
}

Game::~Game()
{
    printf("Destroying game state...\n");

    for (auto ent : m_entities)
        m_registry.destroy(ent);
}
