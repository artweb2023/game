#pragma once

#include <SFML/Graphics.hpp>
#include "map.h"

const unsigned maxHelth = 265;

enum struct Direction
{
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Player
{
    sf::Texture playerTexture;
    sf::Sprite player;
    sf::Vector2f position;
    sf::IntRect sourceRect;
    sf::Time lastHit;
    sf::Clock animationClock;
    Direction direction;
    int spriteLeft;
    int helth;
    bool isMoving;
    bool isAnimationStopped;
    bool isLive;
};

void movePlayer(Player &player, float elapsedTime);
void updatePlayer(float elapsedTime, Player &player, const sf::Vector2f &mousePosition);
void initPlayer(Player &player);
bool handlePlayerKeyPress(const sf::Event::KeyEvent &event, Player &player);
bool handlePlayerKeyRelease(const sf::Event::KeyEvent &event, Player &player);
bool hit(sf::Clock &hitClock, Player &player);
bool isLive(Player &player);
sf::Vector2f toEuclidean(float radius, float angle);