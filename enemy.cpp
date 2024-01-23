#include "enemy.h"

constexpr float ANIMATION_TIME = 0.1f;
constexpr int SPRITE_WIDTH = 170;
constexpr int SPRITE_HEIGTH = 140;
constexpr int SPRITE_TOP = 760;
constexpr int MAX_SPRITE_LEFT_LIVE = 510;
constexpr int SPRITE_TOP_DETH = 935;
constexpr float MIN_COLLISION_OVERLAP = 5.0f;
constexpr int MAP_LEFT = 130;
constexpr int MAP_TOP = 120;
constexpr int MAP_RIGTH = 3600;
constexpr int MAP_BUTTON = 2200;
const float THRES_HOLD_DISTANCE = 35.0f;
constexpr unsigned HIT_INTERVAL_TIME = 1;

void initEnemy(Enemy &enemy)
{
    enemy.spriteLeft = 0;
    enemy.enemyTexture.loadFromFile("img/mon4.png");
    enemy.enemyTexture.setSmooth(true);
    enemy.enemy.setTexture(enemy.enemyTexture);
    sf::IntRect enemyRect(enemy.spriteLeft, SPRITE_TOP, SPRITE_WIDTH, SPRITE_HEIGTH);
    enemy.enemy.setTextureRect(enemyRect);
    enemy.enemy.setOrigin(enemy.enemy.getLocalBounds().width / 2, enemy.enemy.getLocalBounds().height / 2);
    enemy.enemy.setScale(0.5, 0.5);
    enemy.isLive = true;
    enemy.isVisible = true;
    enemy.helth = 10;
}

void spawn(Enemy &enemy)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(0.f, static_cast<float>(WIDTH_MAP * 130));
    std::uniform_real_distribution<float> distY(0.f, static_cast<float>(HEIGHT_MAP * 130));
    std::uniform_int_distribution<> speed_plus(0, 9);
    enemy.speed = 1 - (0.1 * 0.1f) + (speed_plus(gen) * 0.01f);
    enemy.position.x = distX(gen);
    enemy.position.y = distY(gen);
    if (enemy.position.x < MAP_LEFT || enemy.position.y < MAP_TOP || enemy.position.x > MAP_RIGTH || enemy.position.y > MAP_BUTTON)
        spawn(enemy);
    else
        enemy.enemy.setPosition(enemy.position);
}

bool isAlive(const Enemy &enemy)
{
    return enemy.isLive;
}

bool isVisible(Enemy &enemy)
{
    return enemy.isVisible;
}

void getVisible(Enemy &enemy)
{
    enemy.isLive ? enemy.isVisible = true : enemy.isVisible = false;
}

void animateEnemy(float elapsedTime, Enemy &enemy, sf::Clock &animationClock)
{
    if (enemy.isLive)
    {
        if (animationClock.getElapsedTime().asSeconds() > ANIMATION_TIME)
        {
            if (enemy.spriteLeft == MAX_SPRITE_LEFT_LIVE)
                enemy.spriteLeft = 0;
            else
                enemy.spriteLeft += SPRITE_WIDTH;

            enemy.enemy.setTextureRect(sf::IntRect(enemy.spriteLeft, SPRITE_TOP, SPRITE_WIDTH, SPRITE_HEIGTH));
            animationClock.restart();
        }
    }
    else
    {
        if (animationClock.getElapsedTime().asSeconds() > ANIMATION_TIME)
        {
            if (enemy.spriteLeft == MAX_SPRITE_LEFT_LIVE)
                enemy.spriteLeft = MAX_SPRITE_LEFT_LIVE;
            else
                enemy.spriteLeft += SPRITE_WIDTH;
            enemy.enemy.setTextureRect(sf::IntRect(enemy.spriteLeft, SPRITE_TOP_DETH, SPRITE_WIDTH, SPRITE_HEIGTH));
            animationClock.restart();
        }
    }
}

bool hitEnemy(sf::Clock &hitClock, Enemy &enemy)
{
    static sf::Time accumulatedTime;
    accumulatedTime += hitClock.restart();
    const sf::Time hitInterval = sf::milliseconds(HIT_INTERVAL_TIME);
    if (accumulatedTime >= hitInterval && enemy.helth > 0)
    {
        enemy.lastHit = hitClock.getElapsedTime();
        accumulatedTime = sf::Time::Zero;
        enemy.helth -= 1;
        if (enemy.helth < 0)
            enemy.helth = 0;

        return true;
    }
    else
    {
        return false;
    }
}

void updateEnemy(float deltaTime, Enemy &enemy, Player &player, sf::Clock &animationClock)
{
    if (enemy.isLive && enemy.isVisible)
    {
        enemy.speed = 150.f;
        sf::Vector2f direction = player.position - enemy.position;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0)
            direction /= length;
        if (length > THRES_HOLD_DISTANCE)
        {
            enemy.position += direction * enemy.speed * deltaTime;
            float angle = std::atan2(direction.y, direction.x) * (180 / M_PI);

            enemy.enemy.setPosition(enemy.position);
            enemy.enemy.setRotation(angle);
        }
    }
    animateEnemy(deltaTime, enemy, animationClock);
}

bool checkEnemyCollision(const Enemy &enemy1, const Enemy &enemy2)
{
    sf::FloatRect rect1 = enemy1.enemy.getGlobalBounds();
    sf::FloatRect rect2 = enemy2.enemy.getGlobalBounds();
    return rect1.intersects(rect2) && rect1.width - MIN_COLLISION_OVERLAP > 0 && rect1.height - MIN_COLLISION_OVERLAP > 0;
}

void drawEnemy(sf::RenderWindow &window, const Enemy &enemy)
{
    window.draw(enemy.enemy);
}

void drawEnemies(sf::RenderWindow &window, const std::vector<std::unique_ptr<Enemy>> &enemies)
{
    for (const auto &enemy : enemies)
    {
        drawEnemy(window, *enemy);
    }
}
