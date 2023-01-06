#pragma once

#include "../Tween.hpp"
#include "../Events/Input.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <entt/entity/entity.hpp>
#include <vector>

namespace States
{

class Menu : public sf::Drawable
{
public:
    static void SetMenuState(entt::registry& registry);

    Menu(entt::registry& registry, entt::entity entity);
    ~Menu();

    void onInput(const Events::Input& inp) const;

    virtual void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

private:
    entt::registry& m_registry;
    entt::entity m_entity;
    TweenF<TweenAlgorithm::Quint, TweenEase::InOut> m_bounce;
    std::vector<entt::entity> m_entities;
};

}
