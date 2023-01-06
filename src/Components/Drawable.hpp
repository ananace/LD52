#pragma once

namespace sf { class Drawable; }


namespace Components
{

struct Drawable
{
    sf::Drawable* drawable;
    float z{};
};

}
