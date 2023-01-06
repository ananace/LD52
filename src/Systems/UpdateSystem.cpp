#include "UpdateSystem.hpp"
#include <entt/entt.hpp>

#include "../Components/Updating.hpp"

using namespace Systems;

UpdateSystem::UpdateSystem(entt::registry& registry)
    : m_registry(registry)
    , m_ticks()
    , m_fixedTicks()
    , m_accum()
{

}

void UpdateSystem::update(float dt)
{
    ++m_ticks;
    m_accum += dt;

    for (auto &&[ent, updating]: m_registry.view<Components::Updating<UpdateRate::Every>>().each()) {
        updating.update(dt);
    }

    if (m_ticks % 2 == 0)
        for (auto &&[ent, updating]: m_registry.view<Components::Updating<UpdateRate::Every2>>().each()) {
            updating.update(dt * 2);
        }

    if (m_ticks % 10 == 0)
        for (auto &&[ent, updating]: m_registry.view<Components::Updating<UpdateRate::Every10>>().each()) {
            updating.update(dt * 10);
        }

    const float timestep = 1.f / 60.f;
    while (m_accum > timestep)
    {
        m_accum -= timestep;

        if (m_fixedTicks % 6 == 0)
            for (auto &&[ent, updating]: m_registry.view<Components::Updating<UpdateRate::Fixed10>>().each()) {
                updating.update(timestep * 6);
            }

        for (auto &&[ent, updating]: m_registry.view<Components::Updating<UpdateRate::Fixed60>>().each()) {
            updating.update(timestep);
        }
    }
}
