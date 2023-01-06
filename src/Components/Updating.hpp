#pragma once

#include <functional>

enum class UpdateRate
{
    Every,
    Every2,
    Every10,
    Fixed60,
    Fixed10
};

namespace Components
{

template<UpdateRate rate>
struct Updating
{
    std::function<void(float)> update;
};

using UpdatingEvery = Updating<UpdateRate::Every>;

}
