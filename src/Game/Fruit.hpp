#pragma once

#include "../Helpers.hpp"
#include "../Tween.hpp"
#include "../Events/Input.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

enum class FruitStage
{
    Growing = 0,  // Leaf -> Young, scale 0 -> 1
    Young = 1,    // Young -> Ripe
    Ripe = 2,     // Ripe -> Overripe
    Overripe = 3, // Overripe -> Bad, scale 1 -> 0.75
    Bad = 4,

    Destroyed = 10
};

template<typename T>
class Fruit : public sf::Drawable, public sf::Transformable
{
public:
    using PlantType = T;
    using PlantColors = typename T::Colors;
    using GrowthTimes = typename T::GrowthTimes;

    Fruit();

    void mouseEnter();
    void mouseLeave();
    void mouseClick();

    FruitStage getStage() const;
    FruitStage getPickedStage() const;
    bool isAlive() const;
    void update(float dt);

    virtual void draw(sf::RenderTarget&, const sf::RenderStates&) const override;

private:
    FruitStage m_fruitStage, m_fruitStagePicked;
    Tween<sf::Vector3f, TweenAlgorithm::Quint, TweenEase::Out> m_fruitColor;
    Tween<float, TweenAlgorithm::Quint, TweenEase::Out> m_fruitScale;
    Tween<int, TweenAlgorithm::Quart, TweenEase::Out> m_fruitAlpha;
    bool m_hover, m_destroyed;
};

#include "Fruit.inl"
