#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <functional>

namespace Components
{
    struct Interactive
    {
        sf::Transformable* transform{ nullptr };
        float size{};

        std::function<void(bool)> mouseMove;
        std::function<void()> mouseClick;
    };
}
