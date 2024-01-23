#pragma once

#include <SFML/Graphics.hpp>

struct Text
{
    sf::Font font;
    sf::Text text;
};

void showText(const std::string &value, int size, const sf::Vector2f &position, const sf::Color &color, Text &text);
void drawText(sf::RenderWindow &window, Text &text, sf::Vector2f position);