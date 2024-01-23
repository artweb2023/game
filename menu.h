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
    Text levelText;
    Text exitText;
};

void initButton(float centerX, float centerY, Menu &menu);
void initMenu(Menu &menu);
void moveUp(Menu &menu);
void moveDown(Menu &menu);
void drawMenu(sf::RenderWindow &window, Menu &menu);
