#include "bullet.h"
#include <cmath>

constexpr int BULLET_SPEED = 1000;
constexpr float RANGE = 1000;

void initBullet(Bullet &bullet)
{
    bullet.bulletTexture.loadFromFile("img/bullet.png");
    bullet.bulletTexture.setSmooth(true);
    bullet.bullet.setTexture(bullet.bulletTexture);
    sf::IntRect bulletRect(252, 0, 30, 30);
    bullet.bullet.setTextureRect(bulletRect);
    bullet.bullet.setScale(0.5, 0.5);
    bullet.bullet.setOrigin(bullet.bullet.getLocalBounds().width / 2, bullet.bullet.getLocalBounds().height / 2);
    bullet.isFlight = false;
    bullet.isLive = false;
}

void shoot(Bullet &bullet, float startX, float startY, float targetX, float targetY)
{
    bullet.isFlight = true;
    bullet.isLive = true;
    bullet.position.x = startX;
    bullet.position.y = startY;

    float angle = atan2(targetY - startY, targetX - startX);

    bullet.bulletDistance.x = BULLET_SPEED * cos(angle);
    bullet.bulletDistance.y = BULLET_SPEED * sin(angle);

    bullet.min.x = startX - RANGE;
    bullet.max.x = startX + RANGE;
    bullet.min.y = startY - RANGE;
    bullet.max.y = startY + RANGE;
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

void updateBullet(Bullet &bullet, float elapsedTime, Camera &camera,
                  const float WINDOW_WIDTH, const float WINDOW_HEIGHT)
{
    if (bullet.isFlight)
    {
        bullet.position.x += bullet.bulletDistance.x * elapsedTime;
        bullet.position.y += bullet.bulletDistance.y * elapsedTime;
        bullet.bullet.setPosition(bullet.position);

        // Проверяем, находится ли пуля в пределах камеры
        if (bullet.position.x < camera.camera.getCenter().x - WINDOW_WIDTH / 2 ||
            bullet.position.x > camera.camera.getCenter().x + WINDOW_WIDTH / 2 ||
            bullet.position.y < camera.camera.getCenter().y - WINDOW_HEIGHT / 2 ||
            bullet.position.y > camera.camera.getCenter().y + WINDOW_HEIGHT / 2 ||
            checkMapWallsCollision(bullet.position))
        {
            bullet.isFlight = false;
        }
    }
}