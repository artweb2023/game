#pragma once

#include <iostream>
#include <random>
#include <deque>
#include <array>
#include "player.h"
#include "map.h"
#include "bullet.h"

struct Enemy
{
    sf::Texture enemyTexture;
    sf::Sprite enemy;
    sf::Vector2f position;
    sf::IntRect enemyRect;
    sf::Clock lastHitTime;
    sf::Time lastHit;
    sf::Clock animationClock;
    int spriteLeft;
    int helth;
    bool isLive;
    bool isVisible;
    float speed;
};

void initEnemy(Enemy &enemy);
void spawn(Enemy &enemy);
bool isAlive(const Enemy &enemy);
bool isVisible(const Enemy &enemy);
void getVisible(Enemy &enemy);
bool hitEnemy(sf::Clock &hitClock, Enemy &enemy, Bullet &bullet);
void updateEnemy(float deltaTime, Enemy &enemy, Player &player);
bool checkEnemyCollision(const Enemy &enemy1, const Enemy &enemy2);
void drawEnemies(sf::RenderWindow &window, const std::vector<std::unique_ptr<Enemy>> &enemies);
sf::Sprite getSprite(Enemy &enemy);