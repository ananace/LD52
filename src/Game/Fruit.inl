#include <cstdio>

template<typename T>
Fruit<T>::Fruit()
    : m_fruitStage(FruitStage::Growing)
    , m_fruitColor(sf::toVector(PlantColors::Leaf), sf::toVector(PlantColors::YoungFruit), GrowthTimes::NewFruit)
    , m_fruitScale(0, 1, GrowthTimes::NewFruit)
    , m_fruitAlpha(0, 255, GrowthTimes::NewFruit)
    , m_hover(false)
    , m_destroyed(false)
{
    // auto s = m_fruitColor.getStart();
    // auto e = m_fruitColor.getEnd();
    //printf("Fruit update: stage %d, rgb(%d, %d, %d) -> rgb(%d, %d, %d)\n", int(m_fruitStage), s.r, s.g, s.b, e.r, e.g, e.b);
    printf("Created fruit.\n");
}

template<typename T>
void Fruit<T>::mouseEnter()
{
    if (m_fruitStage != FruitStage::Destroyed)
        m_hover = true;
}

template<typename T>
void Fruit<T>::mouseLeave()
{
    m_hover = false;
}

template<typename T>
void Fruit<T>::mouseClick()
{
    if (!m_hover || m_fruitStage == FruitStage::Destroyed)
        return;

    printf("Destroying fruit.\n");

    m_hover = false;
    m_fruitStagePicked = m_fruitStage;
    m_fruitStage = FruitStage::Destroyed;
    m_fruitScale.start(10.f, 1.f);
    m_fruitAlpha.start(0, 0.75f);

    auto col = m_fruitColor.getValue();
    m_fruitColor.start(col, 1.f);

    // auto s = m_fruitColor.getStart();
    // auto e = m_fruitColor.getEnd();
    //printf("Fruit update: stage %d, rgba(%d, %d, %d, %d) -> rgba(%d, %d, %d, %d)\n", int(m_fruitStage), s.r, s.g, s.b, s.a, e.r, e.g, e.b, e.a);
}

template<typename T>
FruitStage Fruit<T>::getStage() const
{
    return m_fruitStage;
}

template<typename T>
FruitStage Fruit<T>::getPickedStage() const
{
    return m_fruitStagePicked;
}

template<typename T>
bool Fruit<T>::isAlive() const
{
    return !m_destroyed;
}

template<typename T>
void Fruit<T>::update(float dt)
{
    m_fruitColor.advance(dt);
    m_fruitScale.advance(dt);
    m_fruitAlpha.advance(dt);

    // float perc = (m_fruitColor.getElapsed() / m_fruitColor.getDuration()) * 100;
    // auto c = m_fruitColor.getValue();
    // printf("Fruit update: %.2f%% (%d), color: %d, %d, %d, scale: %.2f\n", perc, int(m_fruitStage), c.r, c.g, c.b, m_fruitScale.getValue());

    if (m_fruitColor.finished())
    {
        switch(m_fruitStage)
        {
        case FruitStage::Growing:
            m_fruitStage = FruitStage(int(m_fruitStage) + 1);
            break;
        case FruitStage::Young:
            m_fruitColor.start(sf::toVector(PlantColors::RipeFruit), GrowthTimes::YoungFruit);
            {
            // auto s = m_fruitColor.getStart();
            // auto e = m_fruitColor.getEnd();
            // printf("Fruit update: stage %d, rgb(%d, %d, %d) -> rgb(%d, %d, %d)\n", int(m_fruitStage), s.r, s.g, s.b, e.r, e.g, e.b);
            }
            m_fruitStage = FruitStage(int(m_fruitStage) + 1);
            break;

        case FruitStage::Ripe:
            m_fruitColor.start(sf::toVector(PlantColors::OverripeFruit), GrowthTimes::RipeFruit);
            {
            // auto s = m_fruitColor.getStart();
            // auto e = m_fruitColor.getEnd();
            // printf("Fruit update: stage %d, rgb(%d, %d, %d) -> rgb(%d, %d, %d)\n", int(m_fruitStage), s.r, s.g, s.b, e.r, e.g, e.b);
            }
            m_fruitStage = FruitStage(int(m_fruitStage) + 1);
            break;

        case FruitStage::Overripe:
            m_fruitColor.start(sf::toVector(PlantColors::BadFruit), GrowthTimes::OverripeFruit);
            {
            // auto s = m_fruitColor.getStart();
            // auto e = m_fruitColor.getEnd();
            // printf("Fruit update: stage %d, rgb(%d, %d, %d) -> rgb(%d, %d, %d)\n", int(m_fruitStage), s.r, s.g, s.b, e.r, e.g, e.b);
            }
            m_fruitScale.start(0.75, GrowthTimes::OverripeFruit);
            m_fruitStage = FruitStage(int(m_fruitStage) + 1);
            break;

        case FruitStage::Destroyed:
            printf("Fruit is destroyed.\n");
            m_destroyed = true;
            break;
        }
    }
}
