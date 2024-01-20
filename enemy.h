#pragma once

#include <random>
#include <deque>
#include <array>
#include "player.h"
#include "map.h"

struct Enemy
{
    sf::Texture enemyTexture;
    sf::Sprite enemy;
    sf::Vector2f position;
    sf::IntRect enemyRect;
    sf::Time moveTime;
    int spriteLeft;
    bool isLive;
    bool isNoVisible;
    float speed;
};

void initEnemy(Enemy &enemy);
void spawn(Enemy &enemy);
bool isAlive(Enemy &enemy);
bool isNoVisible(Enemy &enemy);
void getVisible(Enemy &enemy);
void animateEnemy(float elapsedTime, Enemy &enemy, sf::Clock &animationClock);
bool hit(Enemy &enemy);
void updateEnemy(float deltaTime, Enemy &enemy, Player &player, sf::Clock &animationClock);
