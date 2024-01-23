#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

static const size_t HEIGHT_MAP = 25;
static const size_t WIDTH_MAP = 40;
const unsigned BLOCK_SIZE = 100;

struct Map
{
    sf::Image mapImage;
    sf::Texture map;
    sf::Sprite block;
    sf::Sprite spriteMap;
    sf::Sprite *sprites;
};

void initMap(Map &map);
void drawMap(sf::RenderWindow &window, const Map &map);
bool checkMapWallsCollision(const sf::Vector2f &position);
void cleanupMap(Map &map);