#pragma once

#include <cstddef>

enum class TweenEase
{
    In,
    Out,
    InOut
};

enum class TweenAlgorithm
{
    Linear,
    Sine,
    Quad,
    Cubic,
    Quart,
    Quint,
    Circular,
    Exponential,
    Elastic,
    Back,
    Bounce,
};

template<TweenAlgorithm>
struct TweenAlgorithms
{
    constexpr static float Apply(float input);

    template<TweenEase>
    constexpr static float Tween(float percent, float start, float end);
};

template<TweenEase Ease>
float ApplyAlgorithm(float input);

template<typename T, TweenAlgorithm Alg = TweenAlgorithm::Linear, TweenEase Ease = TweenEase::In>
class Tween
{
public:
    constexpr Tween();
    constexpr Tween(T start);
    constexpr Tween(T sStart, T end, float duration);
    constexpr Tween(const Tween&) = default;
    constexpr Tween(Tween&&) = default;
    ~Tween() = default;

    constexpr Tween& operator=(const Tween&) = default;
    constexpr Tween& operator=(Tween&&) = default;

    constexpr void reset();
    constexpr void reverse();
    constexpr void start(T start, T end, float duration);
    constexpr void start(T end);
    constexpr void start(T end, float duration);

    constexpr void advance(float aDeltaTime);
    constexpr bool finished() const;

    constexpr T getStart() const { return m_start; }
    constexpr void setStart(T start) { m_start = start; }
    constexpr T getEnd() const { return m_end; }
    constexpr void setEnd(T end) { m_end = end; }
    constexpr float getDuration() const { return m_duration; }
    constexpr void setDuration(float duration) { m_duration = duration; }
    constexpr float getElapsed() const { return m_elapsed; }
    constexpr void setElapsed(float elapsed) { m_elapsed = elapsed; }

    constexpr operator T() const;
    constexpr T getValue() const;
    constexpr T getValueAt(float percent) const;

private:
    T m_start, m_end;
    float m_duration, m_elapsed;
};

template<TweenAlgorithm Alg = TweenAlgorithm::Linear, TweenEase Ease = TweenEase::In>
using TweenF = Tween<float, Alg, Ease>;

#include "Tween.inl"
