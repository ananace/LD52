#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector3.hpp>
#include <algorithm>

namespace sf
{

Color operator*(const Color& lhs, float rhs);
Color& operator*=(Color& lhs, float rhs);

Color toColor(const sf::Vector3f& vec);
sf::Vector3f toVector(const sf::Color& col);

}
