#pragma once

#include <entt/entity/entity.hpp>
#include <vector>

namespace States
{

class Game
{
public:
    static void SetGameState(entt::registry& registry);

    Game(entt::registry& registry, entt::entity entity);
    ~Game();

private:
    entt::registry& m_registry;
    entt::entity m_entity;
    std::vector<entt::entity> m_entities;
};

}
