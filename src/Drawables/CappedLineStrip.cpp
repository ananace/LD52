#include "CappedLineStrip.hpp"
#include "CappedLineShape.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

using namespace Drawables;

CappedLineStrip::CappedLineStrip()
    : m_thickness(2)
    , m_capCount(1)
    , m_fillColor(sf::Color::White)
{
}

void CappedLineStrip::setThickness(float thickness)
{
    m_thickness = thickness;
}
float CappedLineStrip::getThickness() const
{
    return m_thickness;
}

void CappedLineStrip::setCapCount(size_t capCount)
{
    m_capCount = capCount;
}
size_t CappedLineStrip::getCapCount() const
{
    return m_capCount;
}

size_t CappedLineStrip::getPointCount() const
{
    return m_points.size();
}
void CappedLineStrip::addPoint(const sf::Vector2f& vec)
{
    m_points.push_back(vec);
}
void CappedLineStrip::clear()
{
    m_points.clear();
}

void CappedLineStrip::setFillColor(sf::Color color)
{
    m_fillColor = color;
}
sf::Color CappedLineStrip::getFillColor() const
{
    return m_fillColor;
}

sf::FloatRect CappedLineStrip::getLocalBounds() const
{
    sf::FloatRect bounds;

    CappedLineShape shape;
    shape.setThickness(m_thickness);
    shape.setCapCount(m_capCount);

    auto last = m_points.front();
    for (auto& point : m_points)
    {
        if (point == last)
            continue;

        shape.setStartPoint(last);
        shape.setEndPoint(point);

        auto shapeBounds = shape.getLocalBounds();
        bounds.top = std::min(bounds.top, shapeBounds.top);
        bounds.left = std::min(bounds.left, shapeBounds.left);
        // FIXME
        bounds.width = std::max(bounds.width, shapeBounds.width);
        bounds.height = std::max(bounds.height, shapeBounds.height);

        last = point;
    }

    return bounds;
}

void CappedLineStrip::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
    if (m_points.size() < 2)
        return;

    auto stateCopy = states;
    stateCopy.transform *= getTransform();

    CappedLineShape shape;
    shape.setFillColor(m_fillColor);
    shape.setThickness(m_thickness);
    shape.setCapCount(m_capCount);

    auto last = m_points.front();
    for (auto& point : m_points)
    {
        if (point == last)
            continue;

        shape.setStartPoint(last);
        shape.setEndPoint(point);
        target.draw(shape, stateCopy);

        last = point;
    }
}
