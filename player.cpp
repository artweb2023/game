#include "player.h"
#include <cmath>

constexpr float PLAYER_SPEED = 80.f;
static const sf::Vector2f HERO_INITIAL_POSITION(400, 300);
static const float AIM_DISTANCE = 80.0f;
const float animationTime = 0.1f;
constexpr int spriteWidth = 137;
constexpr int spriteHeigth = 105;
constexpr int spriteTop = 0;
constexpr int maxSpriteLeftLive = 411;
constexpr int maxSpriteLeftDead = 1096;
constexpr int minPlayerHelth = 20;

sf::Vector2f toEuclidean(float radius, float angle)
{
    float x = radius * cos(angle);
    float y = radius * sin(angle);
    return sf::Vector2f(x, y);
}

void animatePlayer(float elapsedTime, Player &player, sf::Clock &animationClock)
{
    if (player.isMoving && !player.isAnimationStopped)
    {
        if (animationClock.getElapsedTime().asSeconds() > animationTime)
        {
            if (player.spriteLeft == maxSpriteLeftLive)
                player.spriteLeft = spriteWidth;
            else
                player.spriteLeft += spriteWidth;

            player.player.setTextureRect(sf::IntRect(player.spriteLeft, spriteTop, spriteWidth, spriteHeigth));
            animationClock.restart();
        }
    }
    if (player.helth <= minPlayerHelth)
    {
        if (animationClock.getElapsedTime().asSeconds() > animationTime)
        {
            if (player.spriteLeft == maxSpriteLeftDead)
                player.isAnimationStopped = true;
            else
                player.spriteLeft += spriteWidth;
            player.player.setTextureRect(sf::IntRect(player.spriteLeft, spriteTop, spriteWidth, spriteHeigth));
            animationClock.restart();
        }
    }
    if (player.isAnimationStopped)
        player.player.setTextureRect(sf::IntRect(maxSpriteLeftDead - spriteWidth, spriteTop, spriteWidth, spriteHeigth));
}

void movePlayer(Player &player, float elapsedTime)
{
    const float step = PLAYER_SPEED * elapsedTime;
    sf::Vector2f position = player.player.getPosition();

    switch (player.direction)
    {
    case Direction::UP:
        player.isMoving = true;
        position.y -= step;
        break;
    case Direction::DOWN:
        player.isMoving = true;
        position.y += step;
        break;
    case Direction::LEFT:
        player.isMoving = true;
        position.x -= step;
        break;
    case Direction::RIGHT:
        player.isMoving = true;
        position.x += step;
        break;
    case Direction::NONE:
        player.isMoving = false;
        break;
    }
    if (checkMapWallsCollision(position))
    {
        player.player.setPosition(player.player.getPosition());
    }
    else
    {
        player.player.setPosition(position);
    }
}

void updatePlayer(Player &player, const sf::Vector2f &mousePosition)
{
    player.position = player.player.getPosition();
    const sf::Vector2f delta = mousePosition - player.position;
    player.player.setRotation(atan2(delta.y, delta.x) * 180 / M_PI);
}

void updateAim(Player &player, Aim &aim)
{
    sf::Vector2f aimOffset = toEuclidean(AIM_DISTANCE, player.player.getRotation() * M_PI / 180.0f);
    aim.position = player.position + aimOffset;
    aim.aim.setPosition(aim.position);
}

void initPlayer(Player &player)
{
    player.spriteLeft = 0;
    player.playerTexture.loadFromFile("img/player.png");
    player.playerTexture.setSmooth(true);
    player.player.setTexture(player.playerTexture);
    sf::IntRect playerSource(player.spriteLeft, spriteTop, spriteWidth, spriteHeigth);
    player.player.setTextureRect(playerSource);
    player.player.setOrigin(player.player.getLocalBounds().width / 2, player.player.getLocalBounds().height / 2);
    player.player.setPosition(HERO_INITIAL_POSITION);
    player.player.setScale(0.5, 0.5);
    player.helth = 200;
    player.isMoving = false;
    player.isAnimationStopped = false;
}

void initAim(Aim &aim)
{
    aim.aimTexture.loadFromFile("img/crosshair1.png");
    aim.aimTexture.setSmooth(true);
    aim.aim.setTexture(aim.aimTexture);
    aim.aim.setOrigin(aim.aim.getLocalBounds().width / 2, aim.aim.getLocalBounds().height / 2);
    aim.aim.setScale(0.5, 0.5);
}

bool handlePlayerKeyPress(const sf::Event::KeyEvent &event, Player &player)
{
    bool handled = true;
    switch (event.code)
    {
    case sf::Keyboard::W:
        player.direction = Direction::UP;
        break;
    case sf::Keyboard::S:
        player.direction = Direction::DOWN;
        break;
    case sf::Keyboard::A:
        player.direction = Direction::LEFT;
        break;
    case sf::Keyboard::D:
        player.direction = Direction::RIGHT;
        break;
    default:
        handled = false;
        break;
    }
    return handled;
}

bool handlePlayerKeyRelease(const sf::Event::KeyEvent &event, Player &player)
{
    bool handled = true;
    switch (event.code)
    {
    case sf::Keyboard::W:
        if (player.direction == Direction::UP)
        {
            player.direction = Direction::NONE;
        }
        break;
    case sf::Keyboard::S:
        if (player.direction == Direction::DOWN)
        {
            player.direction = Direction::NONE;
        }
        break;
    case sf::Keyboard::A:
        if (player.direction == Direction::LEFT)
        {
            player.direction = Direction::NONE;
        }
        break;
    case sf::Keyboard::D:
        if (player.direction == Direction::RIGHT)
        {
            player.direction = Direction::NONE;
        }
        break;
    default:
        handled = false;
        break;
    }

    return handled;
}
