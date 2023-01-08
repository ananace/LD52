#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <cstdint>

namespace Drawables
{

class GroundSlice : public sf::Drawable, public sf::Transformable
{
public:
    GroundSlice();

    void generate();
    virtual void draw(sf::RenderTarget&, const sf::RenderStates& states) const override;

private:
    uint32_t m_seed;
};

}
