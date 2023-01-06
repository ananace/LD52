#pragma once

enum class Layer
{
    Background,
    Game,
    UI,
    Overlay
};

namespace Components
{

template<Layer layer>
struct Layer { };

namespace Layers
{

using Background = Layer<::Layer::Background>;
using Game = Layer<::Layer::Game>;
using UI = Layer<::Layer::UI>;
using Overlay = Layer<::Layer::Overlay>;

}

}
