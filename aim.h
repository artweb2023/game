#pragma once

#include <SFML/Graphics.hpp>
#include "player.h"

struct Aim
{
    sf::Texture aimTexture;
    sf::Sprite aim;
    sf::Vector2f position;
};

void initAim(Aim &aim);
void updateAim(Player &player, Aim &aim);
