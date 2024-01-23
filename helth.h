#pragma once

#include <SFML/Graphics.hpp>
#include "player.h"

struct Helth
{
    sf::Image image;
    sf::Texture textureHelth;
    sf::Sprite spriteHelth;
    sf::RectangleShape bar;
};

void initHelth(Helth &helth);
void update(Player &player, Helth &helth);
void drawHelth(sf::RenderWindow &window, Helth &helth);