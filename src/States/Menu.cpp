#include "Menu.hpp"
#include "../Font.hpp"
#include <entt/entt.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../Components/Drawable.hpp"
#include "../Components/Layer.hpp"
#include "../Components/State.hpp"
#include "../Components/Updating.hpp"

#include "../Drawables/MultiPartText.hpp"

#include "../Events/Input.hpp"

#include "../States/Game.hpp"

using namespace States;

void Menu::SetMenuState(entt::registry& registry)
{
    auto state = registry.create();
    registry.emplace<Menu>(state, registry, state);
}

Menu::Menu(entt::registry& registry, entt::entity entity)
    : m_registry(registry)
    , m_entity(entity)
    , m_bounce(-2, 2, 2.f)
{
    m_registry.emplace<Components::State>(entity);
    m_registry.emplace<Components::Drawable>(entity, this);
    m_registry.emplace<Components::Layers::UI>(entity);

    m_registry.emplace<Components::UpdatingEvery>(entity, [&](float dt) {
        m_bounce.advance(dt);
        if (m_bounce.finished())
            m_bounce.reverse();
    });

    m_registry.ctx().get<entt::dispatcher>().sink<Events::Input>().connect<&Menu::onInput>(*this);
}

Menu::~Menu()
{
    printf("Destroying menu state...\n");

    for (auto ent : m_entities)
        m_registry.destroy(ent);

    m_registry.ctx().get<entt::dispatcher>().sink<Events::Input>().disconnect<&Menu::onInput>(*this);
}

void Menu::onInput(const Events::Input& inp) const
{
    if (inp.event.type != sf::Event::KeyReleased || inp.event.key.code != sf::Keyboard::Enter)
        return;

    printf("Switching to game state...\n");

    Game::SetGameState(m_registry);
    m_registry.destroy(m_entity);
}

void Menu::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
    target.clear({ 100, 149, 237 });

    Drawables::MultiPartText menuText;
    menuText.setFontSize(96u);

    menuText.addPart({ {"Ludum "}, { 238, 85, 51 },  sf::Color::Black, 3.f });
    menuText.addPart({ {"Dare "},  { 247, 145, 34 }, sf::Color::Black, 3.f });
    menuText.addPart({ {"52"},     { 156, 0, 232 },  sf::Color::Black, 3.f });

    // sf::Text menuText("Ludum Dare 52", Font::GetMainFont(), 96u);
    // menuText.setFillColor(sf::Color::White);
    // menuText.setOutlineColor(sf::Color::Black);
    // menuText.setOutlineThickness(2.f);
    menuText.setRotation(sf::degrees(m_bounce.getValue()));

    auto bounds = menuText.getLocalBounds();
    menuText.setOrigin({ bounds.width / 2.f, bounds.height / 2.f });
    menuText.setPosition({ target.getSize().x / 2.f, target.getSize().y / 3.f });
    target.draw(menuText, states);

    menuText.clear();
    menuText.setRotation(sf::degrees(0));
    menuText.setFontSize(72u);

    menuText.addPart({ {"Press "},   sf::Color::White, sf::Color::Black, 2.f });
    menuText.addPart({ {"<Enter>"},  sf::Color::White, sf::Color::Black, 2.f, true });
    menuText.addPart({ {" to play"}, sf::Color::White, sf::Color::Black, 2.f });

    bounds = menuText.getLocalBounds();
    menuText.setOrigin({ bounds.width / 2.f, bounds.height / 2.f });
    menuText.move({ 0, target.getSize().y / 3.f });
    target.draw(menuText, states);
}
