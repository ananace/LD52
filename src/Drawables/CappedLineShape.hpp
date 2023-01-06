#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>

namespace Drawables
{

class CappedLineShape : public sf::Shape
{
public:
    CappedLineShape();
    CappedLineShape(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, float thickness = 1.f);
    CappedLineShape(const CappedLineShape&) = default;
    CappedLineShape(CappedLineShape&&) = default;
    ~CappedLineShape() = default;

    CappedLineShape& operator=(const CappedLineShape&) = default;
    CappedLineShape& operator=(CappedLineShape&&) = default;

    void setThickness(float thickness);
    float getThickness() const { return m_thickness; }

    void setCapCount(size_t capCount);
    size_t getCapCount() const { return m_capCount; }

    void setStartPoint(const sf::Vector2f& point);
    const sf::Vector2f& getStartPoint() const { return m_startPoint; }
    void setEndPoint(const sf::Vector2f& point);
    const sf::Vector2f& getEndPoint() const { return m_endPoint; }

    virtual std::size_t getPointCount() const override { return 4 + m_capCount * 2; }
    virtual sf::Vector2f getPoint(std::size_t index) const override;

private:
    sf::Vector2f m_startPoint, m_endPoint;
    float m_thickness;
    size_t m_capCount;
};

}
