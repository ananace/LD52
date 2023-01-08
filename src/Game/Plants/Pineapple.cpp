#include "Pineapple.hpp"
#include "../Fruit.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <random>
#include <cmath>

#include "../../Drawables/CappedLineStrip.hpp"
#include <entt/entity/entity.hpp>

using namespace Plants;

Pineapple::Pineapple()
{
    setFruit(entt::null);
}

void Pineapple::update(float dt)
{
    if (m_fruit != entt::null)
        return;

    if (m_growthTime > 0)
    {
        m_growthTime -= dt;
        return;
    }
}

void Pineapple::setFruit(entt::entity fruit)
{
    m_fruit = fruit;

    std::random_device rand;
    m_growthTime = std::uniform_real_distribution(GrowthTimes::FruitGrowth, GrowthTimes::FruitGrowth + GrowthTimes::FruitGrowth * GrowthTimes::FruitGrowthDeviation)(rand);
}

void Pineapple::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
    auto stateCopy = states;
    stateCopy.transform *= getTransform();

    Drawables::CappedLineStrip strip;
    strip.setFillColor(Colors::Stem);
    strip.setThickness(5.f);

    // 0, 0 origin
    strip.addPoint({});

    for (int i = 0; i < 7; ++i)
    {
        strip.addPoint({ 0, i * -15.f });
    }

    target.draw(strip, stateCopy);

    strip.setFillColor(Colors::Leaf);
    strip.setThickness(2.5f);
    for (int i = 0; i < 7; ++i)
    {
        strip.clear();

        float ang = -110 - (30 - (7 - i)*3);
        sf::Vector2f point(-0.5f, i * -10.f);
        strip.addPoint(point);
        for (int j = 0; j < 8 + (7-i) * 2; ++j)
        {
            float rad = sf::degrees(ang).asRadians();
            point += { std::cos(rad) * 5.f, std::sin(rad) * 5.f };
            strip.addPoint(point);
            ang -= 5;
        }

        target.draw(strip, stateCopy);

        strip.clear();

        ang = -70 + (30 - (7 - i)*3);
        point = { 0.5f, i * -10.f };

        strip.addPoint(point);
        for (int j = 0; j < 8 + (7-i) * 2; ++j)
        {
            float rad = sf::degrees(ang).asRadians();
            point += { std::cos(rad) * 5.f, std::sin(rad) * 5.f };
            strip.addPoint(point);
            ang += 5;
        }

        target.draw(strip, stateCopy);
    }

    //stateCopy.transform.translate({ 0, -90 }).rotate(sf::degrees(90));
//target.draw(m_fruit, stateCopy);
}

template<>
void Fruit<Pineapple>::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
    auto stateCopy = states;
    stateCopy.transform *= getTransform();
    stateCopy.transform.translate({ 15, 0 });
    stateCopy.transform.scale({ m_fruitScale.getValue(), m_fruitScale.getValue() });

    Drawables::CappedLineStrip strip;
    auto col = PlantColors::Leaf;
    col.a = m_fruitAlpha.getValue();
    strip.setFillColor(col);
    strip.setThickness(5.f);
    for (int i = 0; i < 3; ++i)
    {
        sf::Vector2f point(-30 + i * 7.f, 0);

        for (int j = 0; j < 2; ++j)
        {
            strip.clear();
            strip.addPoint(point);

            strip.addPoint(point - sf::Vector2f{ 15, 10 * (0.5f - j) * 2 });
            target.draw(strip, stateCopy);
        }
    }

    sf::ConvexShape fruit;
    col = sf::toColor(m_fruitColor.getValue()) * (m_hover ? 1.25f : 1.f);
    col.a = m_fruitAlpha.getValue();
    fruit.setFillColor(col);
    // if (m_hover || m_fruitStage == FruitStage::Destroyed)
    // {
    //     printf("Fruit (rgba(%d, %d, %d, %d)->rgba(%d, %d, %d, %d)) rgba(%d, %d, %d, %d)\n",
    //            m_fruitColor.getStart().r,m_fruitColor.getStart().g,m_fruitColor.getStart().b,m_fruitColor.getStart().a,
    //            m_fruitColor.getEnd().r,m_fruitColor.getEnd().g,m_fruitColor.getEnd().b,m_fruitColor.getEnd().a,
    //            fruit.getFillColor().r, fruit.getFillColor().g, fruit.getFillColor().b, fruit.getFillColor().a);
    // }
    fruit.setPointCount(11);
    fruit.setPosition({ -15, 0 });

    for (int i = 0; i < 11; ++i)
    {
        auto ang = sf::degrees((360.f / 11.f) * i);
        float rad = ang.asRadians();
        float dist = 0.5 + std::cos(rad * 2) / 2;

        fruit.setPoint(i, { std::cos(rad) * 15 * (0.5f + dist / 2.f), std::sin(rad) * 15 * (0.5f + dist / 2.f) });
    }

    target.draw(fruit, stateCopy);
}
