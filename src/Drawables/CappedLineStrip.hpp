#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <vector>

namespace Drawables
{

class CappedLineStrip : public sf::Drawable, public sf::Transformable
{
public:
    CappedLineStrip();
    ~CappedLineStrip() = default;

    void setThickness(float thickness);
    float getThickness() const;

    void setCapCount(size_t capCount);
    size_t getCapCount() const;

    size_t getPointCount() const;
    void addPoint(const sf::Vector2f& vec);
    void clear();

    void setFillColor(sf::Color);
    sf::Color getFillColor() const;

    sf::FloatRect getLocalBounds() const;

    virtual void draw(sf::RenderTarget& target, const sf::RenderStates& states) const;

private:
    float m_thickness;
    size_t m_capCount;
    sf::Color m_fillColor;
    std::vector<sf::Vector2f> m_points;
};

}
