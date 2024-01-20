#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

static const size_t HEIGHT_MAP = 25;
static const size_t WIDTH_MAP = 40;

struct Map
{
    sf::Image mapImage;
    sf::Texture map;
    sf::Sprite spriteMap;
    sf::Sprite *sprites;
};

void initializeMap(Map &map);
void drawMap(sf::RenderWindow &window, const Map &map);
bool checkMapWallsCollision(const sf::Vector2f &position);
void cleanupMap(Map &map);