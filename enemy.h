#pragma once

#include <iostream>
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
    sf::Clock lastHitTime;
    sf::Time lastHit;
    int spriteLeft;
    int helth;
    bool isLive;
    bool isVisible;
    float speed;
};

void initEnemy(Enemy &enemy);
void spawn(Enemy &enemy);
bool isAlive(const Enemy &enemy);
bool isVisible(Enemy &enemy);
void getVisible(Enemy &enemy);
void animateEnemy(float elapsedTime, Enemy &enemy, sf::Clock &animationClock);
bool hitEnemy(sf::Clock &hitClock, Enemy &enemy);
void updateEnemy(float deltaTime, Enemy &enemy, Player &player, sf::Clock &animationClock);
bool checkEnemyCollision(const Enemy &enemy1, const Enemy &enemy2);
void drawEnemy(sf::RenderWindow &window, const Enemy &enemy);
void drawEnemies(sf::RenderWindow &window, const std::vector<std::unique_ptr<Enemy>> &enemies);
