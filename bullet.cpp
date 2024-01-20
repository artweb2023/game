#include "bullet.h"
#include <cmath>

constexpr int bulletRadius = 5;
constexpr int bulletSpeed = 1000;
constexpr float range = 1000;

void initBullet(Bullet &bullet)
{
    bullet.bulletTexture.loadFromFile("img/bullet.png");
    bullet.bulletTexture.setSmooth(true);
    bullet.bullet.setTexture(bullet.bulletTexture);
    sf::IntRect bulletRect(252, 0, 30, 30);
    bullet.bullet.setTextureRect(bulletRect);
    bullet.bullet.setScale(0.5, 0.5);
    bullet.bullet.setOrigin(bullet.bullet.getLocalBounds().width / 2, bullet.bullet.getLocalBounds().height / 2);
}

void shoot(Bullet &bullet, float startX, float startY, float targetX, float targetY)
{
    bullet.isFlight = true;
    bullet.position.x = startX;
    bullet.position.y = startY;

    float angle = atan2(targetY - startY, targetX - startX);

    bullet.bulletDistance.x = bulletSpeed * cos(angle);
    bullet.bulletDistance.y = bulletSpeed * sin(angle);

    bullet.min.x = startX - range;
    bullet.max.x = startX + range;
    bullet.min.y = startY - range;
    bullet.max.y = startY + range;
    bullet.bullet.setPosition(bullet.position);
    bullet.bullet.setRotation(angle * 180 / M_PI);
}

void stop(Bullet &bullet)
{
    bullet.isFlight = false;
}

bool isInFlight(Bullet &bullet)
{
    return bullet.isFlight;
}

sf::FloatRect getPosition(Bullet &bullet)
{
    return bullet.bullet.getGlobalBounds();
}

sf::Sprite getSprite(Bullet &bullet)
{
    return bullet.bullet;
}

void updateBullet(Bullet &bullet, float elapsedTime)
{
    if (bullet.isFlight)
    {
        bullet.position.x += bullet.bulletDistance.x * elapsedTime;
        bullet.position.y += bullet.bulletDistance.y * elapsedTime;
        bullet.bullet.setPosition(bullet.position);
        if (bullet.position.x < bullet.min.x || bullet.position.x > bullet.max.x ||
            bullet.position.y < bullet.min.y || bullet.position.y > bullet.max.y)
        {
            bullet.isFlight = false;
        }
    }
}
