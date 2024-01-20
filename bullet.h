#pragma once

#include <SFML/Graphics.hpp>

struct Bullet
{
    sf::Texture bulletTexture;
    sf::Sprite bullet;
    bool isFlight = false;
    sf::Vector2f bulletDistance;
    sf::Vector2f position;
    sf::Vector2f max;
    sf::Vector2f min;
};

void initBullet(Bullet &bullet);
void shoot(Bullet &bullet, float startX, float startY, float targetX, float targetY);
void stop(Bullet &bullet);
bool isInFlight(Bullet &bullet);
sf::FloatRect getPosition(Bullet &bullet);
sf::Sprite getSprite(Bullet &bullet);
void updateBullet(Bullet &bullet, float elapsedTime);