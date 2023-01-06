#include "MultiPartText.hpp"
#include "../Font.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

using namespace Drawables;

MultiPartText::MultiPartText()
    : m_fontSize(72u)
{
}

void MultiPartText::setFontSize(uint16_t size)
{
    m_fontSize = size;
}
uint16_t MultiPartText::getFontSize() const
{
    return m_fontSize;
}

void MultiPartText::addPart(Part&& part)
{
    m_parts.push_back(std::move(part));
}

void MultiPartText::clear()
{
    m_parts.clear();
}

sf::FloatRect MultiPartText::getLocalBounds() const
{
    sf::FloatRect bounds;

    sf::Text render;
    render.setCharacterSize(m_fontSize);

    for (auto& part : m_parts)
    {
        if (part.Monospace)
            render.setFont(Font::GetMonospaceFont());
        else
            render.setFont(Font::GetMainFont());

        render.setString(part.String);
        render.setOutlineThickness(part.OutlineThickness);

        auto partBounds = render.getLocalBounds();
        bounds.height = std::max(bounds.height, partBounds.height);
        bounds.width += partBounds.width;
    }

    return bounds;
}

void MultiPartText::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
    auto stateCopy = states;
    stateCopy.transform *= getTransform();

    sf::Text render;
    render.setCharacterSize(m_fontSize);

    for (auto& part : m_parts)
    {
        if (part.Monospace)
            render.setFont(Font::GetMonospaceFont());
        else
            render.setFont(Font::GetMainFont());

        render.setString(part.String);
        render.setFillColor(part.FillColor);
        render.setOutlineThickness(part.OutlineThickness);
        render.setOutlineColor(part.OutlineColor);

        target.draw(render, stateCopy);
        stateCopy.transform.translate({ render.getLocalBounds().width, 0 });
    }
}
