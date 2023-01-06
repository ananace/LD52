#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>

namespace Drawables
{

class MultiPartText : public sf::Drawable, public sf::Transformable
{
public:
    struct Part
    {
        sf::String String;
        sf::Color FillColor{sf::Color::White}, OutlineColor{sf::Color::Black};
        float OutlineThickness{0};
        bool Monospace{false};
    };

    MultiPartText();
    ~MultiPartText() = default;

    void setFontSize(uint16_t size);
    uint16_t getFontSize() const;

    void addPart(Part&& part);
    void clear();

    sf::FloatRect getLocalBounds() const;

    virtual void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

private:
    uint16_t m_fontSize;
    std::vector<Part> m_parts;
};

}
