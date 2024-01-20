#include "enemy.h"

const float animationTime = 0.1f;
constexpr int spriteWidth = 170;
constexpr int spriteHeigth = 140;
constexpr int spriteTop = 760;
constexpr int maxSpriteLeftLive = 510;
constexpr int minPlayerHelth = 10;
constexpr int spriteTopDeth = 935;

void initEnemy(Enemy &enemy)
{
    enemy.spriteLeft = 0;
    enemy.enemyTexture.loadFromFile("img/mon4.png");
    enemy.enemyTexture.setSmooth(true);
    enemy.enemy.setTexture(enemy.enemyTexture);
    sf::IntRect enemyRect(enemy.spriteLeft, spriteTop, spriteWidth, spriteHeigth);
    enemy.enemy.setTextureRect(enemyRect);
    enemy.enemy.setOrigin(enemy.enemy.getLocalBounds().width / 2, enemy.enemy.getLocalBounds().height / 2);
    enemy.enemy.setScale(0.5, 0.5);
    enemy.isLive = true;
    enemy.isNoVisible = false;
}

void spawn(Enemy &enemy)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(0.f, static_cast<float>(WIDTH_MAP * 130));
    std::uniform_real_distribution<float> distY(0.f, static_cast<float>(HEIGHT_MAP * 130));
    std::uniform_int_distribution<> speed_plus(0, 9);

    do
    {
        enemy.speed = 1 - (0.1 * 0.1f) + (speed_plus(gen) * 0.01f);
        enemy.position.x = distX(gen);
        enemy.position.y = distY(gen);
    } while (checkMapWallsCollision(enemy.position));
    enemy.enemy.setPosition(enemy.position);
}
bool isAlive(Enemy &enemy)
{
    return enemy.isLive;
}

bool isNoVisible(Enemy &enemy)
{
    return enemy.isNoVisible;
}

void getVisible(Enemy &enemy)
{
    enemy.isLive ? enemy.isNoVisible = true : enemy.isNoVisible = false;
}

void animateEnemy(float elapsedTime, Enemy &enemy, sf::Clock &animationClock)
{
    if (enemy.isLive)
    {
        if (animationClock.getElapsedTime().asSeconds() > animationTime)
        {
            if (enemy.spriteLeft == maxSpriteLeftLive)
                enemy.spriteLeft = 0;
            else
                enemy.spriteLeft += spriteWidth;

            enemy.enemy.setTextureRect(sf::IntRect(enemy.spriteLeft, spriteTop, spriteWidth, spriteHeigth));
            animationClock.restart();
        }
    }
    else
    {
        if (animationClock.getElapsedTime().asSeconds() > animationTime)
        {
            if (enemy.spriteLeft == maxSpriteLeftLive)
                enemy.spriteLeft = maxSpriteLeftLive;
            else
                enemy.spriteLeft += spriteWidth;
            enemy.enemy.setTextureRect(sf::IntRect(enemy.spriteLeft, spriteTopDeth, spriteWidth, spriteHeigth));
            animationClock.restart();
        }
    }
}

bool hit(Enemy &enemy)
{
    return enemy.isLive = false;
}

void updateEnemy(float deltaTime, Enemy &enemy, Player &player, sf::Clock &animationClock)
{
    const float thresholdDistance = 35.0f;
    enemy.speed = 50.f;
    sf::Vector2f direction = player.position - enemy.position;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
        direction /= length;
    if (length > thresholdDistance)
    {
        enemy.position += direction * enemy.speed * deltaTime;
        enemy.enemy.setPosition(enemy.position);
        float angle = std::atan2(direction.y, direction.x) * (180 / M_PI);
        enemy.enemy.setRotation(angle);
    }

    animateEnemy(deltaTime, enemy, animationClock);
}