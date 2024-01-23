#include "text.h"

void showText(const std::string &value, int size, const sf::Vector2f &position, const sf::Color &color, Text &text)
{
    text.font.loadFromFile("font/BebasNeue-Regular.ttf");
    text.text.setFont(text.font);
    text.text.setString(value);
    text.text.setFillColor(color);
    text.text.setCharacterSize(size);
    text.text.setPosition(position);
}

void drawText(sf::RenderWindow &window, Text &text, sf::Vector2f position)
{
    text.text.setPosition(position);
    window.draw(text.text);
}