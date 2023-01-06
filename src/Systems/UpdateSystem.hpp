#pragma once

#include <entt/entity/fwd.hpp>

namespace Systems
{

class UpdateSystem
{
public:
    UpdateSystem(entt::registry& registry);

    void update(float dt);

private:
    entt::registry& m_registry;
    uint8_t m_ticks, m_fixedTicks;
    float m_accum;
};

}
