#pragma once

#include "text.h"

struct Menu
{
    int mainMenuSelected;
    sf::Texture menuBackground;
    sf::Sprite menu;
    sf::RectangleShape rectangle;
    std::vector<sf::RectangleShape> buttonRectangles;
    Text playText;
    Text helpText;
    Text exitText;
};

void initMenu(Menu &menu);
void updateMenuPostion(Menu &menu, sf::Vector2f postion);
void moveUp(Menu &menu);
void moveDown(Menu &menu);
void drawMenu(sf::RenderWindow &window, Menu &menu);
