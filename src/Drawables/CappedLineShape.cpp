#include "CappedLineShape.hpp"

#include <cmath>

using namespace Drawables;
using namespace sf;

CappedLineShape::CappedLineShape()
    : m_startPoint()
    , m_endPoint()
    , m_thickness(1)
    , m_capCount(3)
{
}

CappedLineShape::CappedLineShape(const Vector2f& startPoint, const Vector2f& endPoint, float thickness)
    : m_startPoint(startPoint)
    , m_endPoint(endPoint)
    , m_thickness(thickness)
    , m_capCount(3)
{
  update();
}

void CappedLineShape::setThickness(float thickness)
{
    if (m_thickness == thickness) [[unlikely]]
        return;

    m_thickness = thickness;
    update();
}

void CappedLineShape::setStartPoint(const Vector2f& startPoint)
{
    if (m_startPoint == startPoint) [[unlikely]]
        return;

    m_startPoint = startPoint;
    update();
}

void CappedLineShape::setEndPoint(const Vector2f& endPoint)
{
    if (m_endPoint == endPoint) [[unlikely]]
        return;

    m_endPoint = endPoint;
    update();
}

void CappedLineShape::setCapCount(size_t capCount)
{
    if (m_capCount == capCount) [[unlikely]]
        return;

    m_capCount = capCount;
    update();
}

Vector2f CappedLineShape::getPoint(std::size_t index) const
{
    auto diff = (m_endPoint - m_startPoint);
    float angle = std::atan2(diff.y, diff.x) + (M_PI * 0.5f);
    size_t realCapCount = 2 + m_capCount;
    Vector2f sourcePoint = m_startPoint;
    std::size_t anglePoint = index;

    if (index >= realCapCount)
    {
        sourcePoint = m_endPoint;
        anglePoint -= 1;
    }

    angle += (M_PI / float(realCapCount - 1)) * anglePoint;

    Vector2f offset(std::cos(angle), std::sin(angle));
    auto result = sourcePoint + offset * (m_thickness / 2.f);

    return result;
}
