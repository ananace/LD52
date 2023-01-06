#include "Font.hpp"
#include <SFML/Graphics/Font.hpp>
#include <vector>

bool loadFirstFont(sf::Font& font, const std::vector<std::string>& paths)
{
    for (auto& path : paths)
    {
        printf("Attempting to load font from %s...\n", path.c_str());
        if (font.loadFromFile(path))
            return true;
    }

    return false;
}

sf::Font& Font::GetMainFont()
{
    static sf::Font font;

    if (font.hasGlyph(0x41))
        return font;

    if (!loadFirstFont(font, {
#ifdef WIN32
        "C:\\Windows\\Fonts\\Arial.ttf",
#else
        "/usr/share/fonts/corefonts/arial.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/liberation-fonts/LiberationSans-Regular.ttf",
        "/usr/share/fonts/noto/NotoSans-Regular.ttf",
#endif
        "arial.ttf"
    }))
        throw std::runtime_error("Failed to load a main application font");

    return font;
}

sf::Font& Font::GetMonospaceFont()
{
    static sf::Font font;

    if (font.hasGlyph(0x41))
        return font;

    if (!loadFirstFont(font, {
#ifdef WIN32
        "C:\\Windows\\Fonts\\Consolas.ttf",
        "C:\\Windows\\Fonts\\Cour.ttf",
#else
        "/usr/share/fonts/corefonts/cour.ttf",
        "/usr/share/fonts/dejavu/DejaVuSansMono.ttf",
        "/usr/share/fonts/liberation-fonts/LiberationMono-Regular.ttf",
        "/usr/share/fonts/noto/NotoSansMono-Regular.ttf",
#endif
        "consolas.ttf",
        "cour.ttf"
    }))
        throw std::runtime_error("Failed to load a monospace application font");

    return font;
}


