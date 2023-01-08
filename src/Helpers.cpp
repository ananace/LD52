#include "Helpers.hpp"

sf::Color sf::operator*(const Color& lhs, float rhs)
{
    return sf::Color {
        uint8_t(std::clamp(lhs.r * rhs, 0.f, 255.f)),
        uint8_t(std::clamp(lhs.g * rhs, 0.f, 255.f)),
        uint8_t(std::clamp(lhs.b * rhs, 0.f, 255.f)),
        uint8_t(std::clamp(lhs.a * rhs, 0.f, 255.f))
    };
}

sf::Color& sf::operator*=(Color& lhs, float rhs)
{
    lhs.r = uint8_t(std::clamp(lhs.r * rhs, 0.f, 255.f));
    lhs.g = uint8_t(std::clamp(lhs.g * rhs, 0.f, 255.f));
    lhs.b = uint8_t(std::clamp(lhs.b * rhs, 0.f, 255.f));
    lhs.a = uint8_t(std::clamp(lhs.a * rhs, 0.f, 255.f));

    return lhs;
}

sf::Color sf::toColor(const sf::Vector3f& vec)
{
    return {
        uint8_t(vec.x),
        uint8_t(vec.y),
        uint8_t(vec.z),
        255
    };
}

sf::Vector3f sf::toVector(const sf::Color& col)
{
    return {
        float(col.r),
        float(col.g),
        float(col.b)
    };
}
