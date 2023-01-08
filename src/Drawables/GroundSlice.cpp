#include "GroundSlice.hpp"
#include "../Helpers.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <random>

using namespace Drawables;

GroundSlice::GroundSlice()
{
    generate();
}

void GroundSlice::generate()
{
    std::random_device dev;
    m_seed = std::uniform_int_distribution<uint32_t>()(dev);
}

void GroundSlice::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
    std::mt19937 rand(m_seed);

    auto stateCopy = states;
    stateCopy.transform *= getTransform();

    sf::Color earth{ 110, 73, 0 };
    sf::Color grass{ 70, 125, 0 };

    sf::CircleShape groundBump;
    groundBump.setRadius(50);
    groundBump.setOrigin({ 50, 50 });
    groundBump.setFillColor(earth);
    groundBump.setOutlineColor(earth * 0.5f);
    groundBump.setOutlineThickness(5.f);

    sf::RectangleShape ground;
    ground.setSize({ 50000, 2000 });
    ground.setOrigin({ 25000, 0 });
    ground.setFillColor(grass);

    target.draw(ground, stateCopy);

    ground.setSize({ 10000, 1000 });
    ground.setOrigin({ 5000, 0 });
    ground.setFillColor(earth);

    for (int i = 0; i < std::uniform_int_distribution(100, 200)(rand); ++i)
    {
        groundBump.setPosition({ std::uniform_real_distribution(-5000.f, 5000.f)(rand), 10 });
        groundBump.setRadius(groundBump.getRadius() - 0.2f);
        groundBump.setOrigin({ groundBump.getRadius(), groundBump.getRadius() });
        target.draw(groundBump, stateCopy);
    }

    target.draw(ground, stateCopy);

    groundBump.setRadius(0.5f);
    groundBump.setOrigin({ 0.5f, 0.5f });

    for (int i = 0; i < std::uniform_int_distribution(500, 1000)(rand); ++i)
    {
        groundBump.setPosition({ std::uniform_real_distribution(-5000.f, 5000.f)(rand), std::uniform_real_distribution(0.f, 1000.f)(rand) });
        target.draw(groundBump, stateCopy);
    }
}
