#pragma once

#include "../Plant.hpp"

namespace Plants
{

class Pineapple : public Plant
{
public:
    virtual std::string getName() const override { return "Pineapple"; }
    virtual uint32_t getCost() const override { return 10; }

    virtual void draw(sf::RenderTarget&, const sf::RenderStates&) const override;
private:
};

}
