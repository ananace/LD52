#include <cmath>

template<typename T, TweenAlgorithm Alg, TweenEase Ease>
constexpr Tween<T, Alg, Ease>::Tween()
    : m_start()
    , m_end()
    , m_duration()
    , m_elapsed()
{
}

template<typename T, TweenAlgorithm Alg, TweenEase Ease>
constexpr Tween<T, Alg, Ease>::Tween(T start)
    : m_start(start)
    , m_end(start)
    , m_duration()
    , m_elapsed()
{
}

template<typename T, TweenAlgorithm Alg, TweenEase Ease>
constexpr Tween<T, Alg, Ease>::Tween(T start, T end, float duration)
    : m_start(start)
    , m_end(end)
    , m_duration(duration)
    , m_elapsed()
{
}

template<typename T, TweenAlgorithm Alg, TweenEase Ease>
constexpr void Tween<T, Alg, Ease>::reset()
{
    m_elapsed = 0;
}

template<typename T, TweenAlgorithm Alg, TweenEase Ease>
constexpr void Tween<T, Alg, Ease>::start(T start, T end, float duration)
{
    m_start = start;
    m_end = end;
    m_duration = duration;
    m_elapsed = 0;
}

template<typename T, TweenAlgorithm Alg, TweenEase Ease>
constexpr void Tween<T, Alg, Ease>::start(T end, float duration)
{
    m_start = m_end;
    m_end = end;
    m_duration = duration;
    m_elapsed = 0;
}

template<typename T, TweenAlgorithm Alg, TweenEase Ease>
constexpr void Tween<T, Alg, Ease>::start(T end)
{
    m_start = m_end;
    m_end = end;
    m_elapsed = 0;
}

template<typename T, TweenAlgorithm Alg, TweenEase Ease>
constexpr void Tween<T, Alg, Ease>::reverse()
{
    auto start = m_start;
    m_start = m_end;
    m_end = start;
    m_elapsed = 0;
}

template<typename T, TweenAlgorithm Alg, TweenEase Ease>
constexpr void Tween<T, Alg, Ease>::advance(float deltaTime)
{
    m_elapsed = std::min(m_duration, m_elapsed + deltaTime);
}

template<typename T, TweenAlgorithm Alg, TweenEase Ease>
constexpr bool Tween<T, Alg, Ease>::finished() const
{
    return m_elapsed >= m_duration;
}


template<typename T, TweenAlgorithm Alg, TweenEase Ease>
constexpr Tween<T, Alg, Ease>::operator T() const
{
    return getValueAt(m_elapsed / m_duration);
}

template<typename T, TweenAlgorithm Alg, TweenEase Ease>
constexpr T Tween<T, Alg, Ease>::getValue() const
{
    return getValueAt(m_elapsed / m_duration);
}

template<typename T, TweenAlgorithm Alg, TweenEase Ease>
constexpr T Tween<T, Alg, Ease>::getValueAt(float percent) const
{
    return m_start + (m_end - m_start) * TweenAlgorithms<Alg>::template Tween<Ease>(percent, 0.f, 1.f);
}

template<>
constexpr float TweenAlgorithms<TweenAlgorithm::Linear>::Apply(float input) { return input; }
template<>
constexpr float TweenAlgorithms<TweenAlgorithm::Sine>::Apply(float input) { return 1 - std::cos(input * M_PI * 0.5); }
template<>
constexpr float TweenAlgorithms<TweenAlgorithm::Quad>::Apply(float input) { return input * input; }
template<>
constexpr float TweenAlgorithms<TweenAlgorithm::Cubic>::Apply(float input) { return input * input * input; }
template<>
constexpr float TweenAlgorithms<TweenAlgorithm::Quart>::Apply(float input) { return input * input * input * input; }
template<>
constexpr float TweenAlgorithms<TweenAlgorithm::Quint>::Apply(float input) { return input * input * input * input * input; }
template<>
constexpr float TweenAlgorithms<TweenAlgorithm::Circular>::Apply(float input) { return 1 - std::sqrt(1 - input * input); }
template<>
constexpr float TweenAlgorithms<TweenAlgorithm::Exponential>::Apply(float input) { return input == 0 ? 0 : std::pow(2, 10 * (input - 1)); }
template<>
constexpr float TweenAlgorithms<TweenAlgorithm::Elastic>::Apply(float input) { return -std::pow(2, 10 * input) * std::sin(input - 1.075) * 2 * M_PI / 0.3; }
template<>
constexpr float TweenAlgorithms<TweenAlgorithm::Back>::Apply(float input) { return input * input * (2.70158 * input - 1.70158); }
template<>
constexpr float TweenAlgorithms<TweenAlgorithm::Bounce>::Apply(float input) {
    float a = 0, b = 0;
    input = 1 - input;

    if (input < 1 / 2.75)
    {
        a = input;
        b = 0;
    }
    else if (input < 2 / 2.75)
    {
        a = input - 1.5 / 2.75;
        b = 0.75;
    }
    else if (input < 2.5 < 2.75)
    {
        a = input - 2.25 / 2.75;
        b = 0.9375;
    }
    else
    {
        a = input - 2.625 / 2.75;
        b = 0.984375;
    }

    return 1 - 7.5625 * a * a + b;
}

template<TweenAlgorithm Alg>
template<TweenEase Ease>
constexpr float TweenAlgorithms<Alg>::Tween(float percent, float start, float end)
{
    if constexpr (Ease == TweenEase::In)
        return start + (end - start) * Apply(percent);
    else if constexpr (Ease == TweenEase::Out)
        return start + (end - start) * (1 - Apply(1 - percent));
    else
    {
      float t = 0;
      if (percent <= 0.5)
          t = Apply(percent * 2) * 0.5;
      else
      {
          percent -= 0.5;
          t = (1 - Apply(1 - (percent * 2))) * 0.5 + 0.5;
      }
      return start + (end - start) * t;
    }
}
