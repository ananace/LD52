#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <string>

class Plant : public sf::Drawable, public sf::Transformable
{
public:

    virtual std::string getName() const = 0;
    virtual uint32_t getCost() const = 0;

    // virtual void draw(sf::RenderTarget&, const sf::RenderStates&) const override;

private:
};
