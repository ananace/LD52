#include "Pineapple.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <cmath>

#include "../../Drawables/CappedLineStrip.hpp"

using namespace Plants;

namespace
{

constexpr sf::Color StemColor { 51, 102, 0 };
constexpr sf::Color LeafColor { 115, 170, 29 };
constexpr sf::Color UnripeFruitColor { 159, 203, 23 };
constexpr sf::Color RipeFruitColor { 206, 196, 22 };

}

void Pineapple::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
    auto stateCopy = states;
    stateCopy.transform *= getTransform();

    Drawables::CappedLineStrip strip;
    strip.setFillColor(StemColor);
    strip.setThickness(5.f);

    // 0, 0 origin
    strip.addPoint({});

    for (int i = 0; i < 7; ++i)
    {
        strip.addPoint({ 0, i * -15.f });
    }

    target.draw(strip, stateCopy);

    strip.setFillColor(LeafColor);
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

    strip.setThickness(5.f);
    for (int i = 0; i < 3; ++i)
    {
        sf::Vector2f point(0, -125 - i * -7.f);

        for (int j = 0; j < 2; ++j)
        {
            strip.clear();
            strip.addPoint(point);

            strip.addPoint(point - sf::Vector2f{ 10 * (0.5f - j) * 2, 15 });
            target.draw(strip, stateCopy);
        }
    }

    sf::ConvexShape fruit;
    fruit.setFillColor(RipeFruitColor);
    fruit.setPointCount(11);
    fruit.setPosition({ 0, -105 });

    for (int i = 0; i < 11; ++i)
    {
        auto ang = sf::degrees((360.f / 11.f) * i);
        float rad = ang.asRadians();
        float dist = 0.5 + std::cos(3.14 + rad * 2) / 2;

        fruit.setPoint(i, { std::cos(rad) * 15 * (0.5f + dist / 2.f), std::sin(rad) * 15 * (0.5f + dist / 2.f) });
    }

    target.draw(fruit, stateCopy);
}
