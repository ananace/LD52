#pragma once

enum class Layer
{
    Background,
    PreGame,
    Game,
    PostGame,
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
using PreGame = Layer<::Layer::PreGame>;
using Game = Layer<::Layer::Game>;
using PostGame = Layer<::Layer::PostGame>;
using UI = Layer<::Layer::UI>;
using Overlay = Layer<::Layer::Overlay>;

}

}
