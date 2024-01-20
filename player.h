#pragma once

#include <SFML/Graphics.hpp>
#include "map.h"
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
    Direction direction;
    int spriteLeft;
    int helth;
    bool isMoving;
    bool isAnimationStopped;
};

struct Aim
{
    sf::Texture aimTexture;
    sf::Sprite aim;
    sf::Vector2f position;
};

void movePlayer(Player &player, float elapsedTime);
void updatePlayer(Player &player, const sf::Vector2f &mousePosition);
void updateAim(Player &player, Aim &aim);
void initPlayer(Player &player);
void animatePlayer(float elapsedTime, Player &player, sf::Clock &animationClock);
void initAim(Aim &aim);
bool handlePlayerKeyPress(const sf::Event::KeyEvent &event, Player &player);
bool handlePlayerKeyRelease(const sf::Event::KeyEvent &event, Player &player);