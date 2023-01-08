#pragma once

#include "../Fruit.hpp"
#include "../Plant.hpp"

#include <entt/entity/fwd.hpp>

namespace Plants
{

class Pineapple : public Plant
{
public:
    struct Colors
    {
        static constexpr sf::Color Stem { 51, 102, 0 };
        static constexpr sf::Color Sprig { 51, 102, 0 };
        static constexpr sf::Color Leaf { 115, 170, 29 };
        static constexpr sf::Color YoungFruit { 159, 203, 23 };
        static constexpr sf::Color RipeFruit { 206, 196, 22 };
        static constexpr sf::Color OverripeFruit { 154, 147, 16 };
        static constexpr sf::Color BadFruit { 51, 49, 5 };
    };

    struct GrowthTimes
    {
        static constexpr float PlantGrowth = 10.f;
        static constexpr float PlantGrowthDeviation = 0.5f;
        static constexpr float FruitGrowth = 10.f;
        static constexpr float FruitGrowthDeviation = 1.5f;

        static constexpr float NewFruit = 3.f;
        static constexpr float NewFruitDeviation = 0.5f;
        static constexpr float YoungFruit = 4.f;
        static constexpr float YoungFruitDeviation = 0.5f;
        static constexpr float RipeFruit = 8.f;
        static constexpr float RipeFruitDeviation = 0.5f;
        static constexpr float OverripeFruit = 2.f;
        static constexpr float OverripeFruitDeviation = 0.5f;
    };

    Pineapple();

    virtual std::string getName() const override { return "Pineapple"; }
    virtual uint32_t getCost() const override { return 10; }

    void update(float dt);
    bool fruiting() const { return m_growthTime <= 0; }
    void setFruit(entt::entity fruit);

    virtual void draw(sf::RenderTarget&, const sf::RenderStates&) const override;

private:
    float m_growthTime;
    entt::entity m_fruit;
    //Fruit<Pineapple> m_fruit;
};

}
