#include "Game.hpp"
#include <entt/entt.hpp>

#include "../Components/Drawable.hpp"
#include "../Components/Interactive.hpp"
#include "../Components/Layer.hpp"
#include "../Components/State.hpp"
#include "../Components/Updating.hpp"

#include "../Events/Resize.hpp"

#include "../Drawables/GroundSlice.hpp"
#include "../Drawables/MultiPartText.hpp"
#include "../Game/Plants/Pineapple.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

using namespace States;

std::array<Plants::Pineapple, 10> pineapples;
std::array<Drawables::GroundSlice, 20> ground;
std::vector<std::unique_ptr<Fruit<Plants::Pineapple>>> fruits;
sf::RectangleShape background;

uint64_t score = 0;

class Camera : public sf::Drawable
{
public:
    Camera()
        : m_camera()
        , m_sized(false)
    {
        m_camera.setSize({ 1366, 768 });
        m_camera.setCenter({ 0, -250 });
    }

    void setSize(sf::RenderTarget& target)
    {
        float aspect = float(target.getSize().x) / float(target.getSize().y);

        m_camera.setSize({ 1000 * aspect, 1000 });
        m_sized = true;
    }

    void onResize(const Events::Resize& ev)
    {
        float aspect = float(ev.event.size.width) / float(ev.event.size.height);

        m_camera.setSize({ 1000 * aspect, 1000 });
        m_sized = true;
    }

    virtual void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override
    {
        if (!m_sized)
            const_cast<Camera*>(this)->setSize(target);

        target.setView(m_camera);
    }

private:
    sf::View m_camera;
    bool m_sized;
};

Camera gameCam;
Drawables::MultiPartText scoreText;

void Game::SetGameState(entt::registry& registry)
{
    auto state = registry.create();
    registry.emplace<Game>(state, registry, state);
}

Game::Game(entt::registry& registry, entt::entity entity)
    : m_registry(registry)
    , m_entity(entity)
{
    m_registry.emplace<Components::State>(entity);

    {
        auto ent = m_registry.create();
        m_entities.push_back(ent);

        scoreText.setFontSize(62u);
        scoreText.setPosition({ 10, 10 });

        m_registry.emplace<Components::Drawable>(ent, &scoreText);
        m_registry.emplace<Components::Layers::UI>(ent);
        m_registry.emplace<Components::Updating<UpdateRate::Every2>>(ent, [](float dt) {
            scoreText.clear();

            scoreText.addPart({ {"Score: "}, sf::Color::White, sf::Color::Black, 3.f });
            scoreText.addPart({ { std::to_string(score) }, sf::Color::White, sf::Color::Black, 3.f });
        });
    }

    for (int i = 0; i < 10; ++i)
    {
        auto& pineapple = pineapples[i];
        auto plant = m_registry.create();
        m_entities.push_back(plant);

        auto& layer = m_registry.emplace<Components::Drawable>(plant, &pineapple);
        layer.z = 5;
        m_registry.emplace<Components::Layers::Game>(plant);
        m_registry.emplace<Components::Updating<UpdateRate::Fixed10>>(plant, [&](float dt) {
            pineapple.update(dt);

            if (pineapple.fruiting())
            {
                auto fruit = m_registry.create();
                m_entities.push_back(fruit);

                fruits.push_back(std::make_unique<Fruit<Plants::Pineapple>>());
                auto fruitDraw = fruits.back().get();
                fruitDraw->setPosition(pineapple.getPosition() + sf::Vector2f(0, -105));
                fruitDraw->setRotation(sf::degrees(90));
                m_registry.emplace<Components::Drawable>(fruit, fruitDraw);
                m_registry.emplace<Components::Layers::PostGame>(fruit);
                m_registry.emplace<Components::UpdatingEvery>(fruit, [this, fruit, &pineapple, fruitDraw](float dt) {
                    fruitDraw->update(dt);

                    if (!fruitDraw->isAlive())
                    {
                        printf("Deleting fruit.\n");
                        m_registry.destroy(fruit);
                        pineapple.setFruit(entt::null);

                        if (fruitDraw->getPickedStage() == FruitStage::Ripe)
                            score += 10;
                        else if (fruitDraw->getPickedStage() == FruitStage::Overripe || fruitDraw->getPickedStage() == FruitStage::Young)
                            score += 2;

                        auto it = std::find_if(fruits.begin(), fruits.end(), [fruitDraw](const auto& ptr) { return ptr.get() == fruitDraw; });
                        if (it != fruits.end())
                            fruits.erase(it);
                    }
                });
                auto& i = m_registry.emplace<Components::Interactive>(fruit, fruitDraw);
                i.size = 15;
                i.mouseMove = [fruitDraw](bool inside) {
                    if (inside)
                        fruitDraw->mouseEnter();
                    else
                        fruitDraw->mouseLeave();
                };
                i.mouseClick = [fruitDraw]() {
                    fruitDraw->mouseClick();
                };

                pineapple.setFruit(fruit);
            }
        });

        pineapple.setPosition({ -625.f + i * 125.f, 0.f + std::cos(float(i)) * 25.f });
    }

    for (int i = 19; i >= 0; i--)
    {
        auto& slice = ground[i];
        auto ent = m_registry.create();
        m_entities.push_back(ent);

        auto& layer = m_registry.emplace<Components::Drawable>(ent, &slice);
        layer.z = i;
        m_registry.emplace<Components::Layers::Game>(ent);

        float scale = (i + 1.f) / 20.f;
        slice.setPosition({ 0, 0 - (19 - i) * 20.f });
        slice.setScale({ scale, scale });
    }

    {
        auto bgent = m_registry.create();
        m_entities.push_back(bgent);

        m_registry.emplace<Components::Drawable>(bgent, &background);
        m_registry.emplace<Components::Layers::Background>(bgent);

        background.setFillColor({ 100, 149, 237 });
        background.setPosition({ -2500, -2500 });
        background.setSize({ 7500, 7500 });
    }

    {
        auto camera = m_registry.create();
        m_entities.push_back(camera);

        m_registry.emplace<Components::Drawable>(camera, &gameCam);
        m_registry.emplace<Components::Layers::PreGame>(camera);

        m_registry.ctx().get<entt::dispatcher>().sink<Events::Resize>().connect<&Camera::onResize>(gameCam);
    }
}

Game::~Game()
{
    printf("Destroying game state...\n");

    for (auto ent : m_entities)
    {
        if (m_registry.valid(ent))
            m_registry.destroy(ent);
    }

    fruits.clear();

    printf("Destroyed game state.\n");
}
