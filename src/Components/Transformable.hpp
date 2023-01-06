#pragma once

namespace sf { class Transform; }

namespace Components
{

struct Transformable
{
    sf::Transform& transformable;
};

}
