#include "player.h"
#include <cmath>

constexpr float PLAYER_SPEED = 80.f;
static const sf::Vector2f HERO_INITIAL_POSITION(400, 300);
const float ANIMATION_TIME = 0.1f;
constexpr int SPRITE_WIDTH = 137;
constexpr int SPRITE_HEIGTH = 105;
constexpr int SPRITE_TOP = 0;
constexpr int MAX_SPRITE_LEFT_LIVE = 411;
constexpr int MAX_SPRITE_LEFT_DEAD = 1096;
constexpr int MIN_PLAYER_HELTH = 20;
constexpr unsigned HIT_INTERVAL_TIME = 100;

sf::Vector2f toEuclidean(float radius, float angle)
{
    float x = radius * cos(angle);
    float y = radius * sin(angle);
    return sf::Vector2f(x, y);
}

void animatePlayer(float elapsedTime, Player &player)
{
    if (player.isMoving && !player.isAnimationStopped)
    {
        if (player.animationClock.getElapsedTime().asSeconds() > ANIMATION_TIME)
        {
            if (player.spriteLeft == MAX_SPRITE_LEFT_LIVE)
                player.spriteLeft = SPRITE_WIDTH;
            else
                player.spriteLeft += SPRITE_WIDTH;

            player.player.setTextureRect(sf::IntRect(player.spriteLeft, SPRITE_TOP,
                                                     SPRITE_WIDTH, SPRITE_HEIGTH));
            player.animationClock.restart();
        }
    }
    if (player.helth <= MIN_PLAYER_HELTH)
    {
        if (player.animationClock.getElapsedTime().asSeconds() > ANIMATION_TIME)
        {
            if (player.spriteLeft == MAX_SPRITE_LEFT_DEAD)
                player.isAnimationStopped = true;
            else
                player.spriteLeft += SPRITE_WIDTH;
            player.player.setTextureRect(sf::IntRect(player.spriteLeft, SPRITE_TOP,
                                                     SPRITE_WIDTH, SPRITE_HEIGTH));
            player.animationClock.restart();
        }
    }
    if (player.isAnimationStopped)
    {
        player.player.setTextureRect(sf::IntRect(MAX_SPRITE_LEFT_DEAD - SPRITE_WIDTH, SPRITE_TOP,
                                                 SPRITE_WIDTH, SPRITE_HEIGTH));
        player.isLive = false;
    }
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

void updatePlayer(float elapsedTime, Player &player, const sf::Vector2f &mousePosition)
{
    player.position = player.player.getPosition();
    const sf::Vector2f delta = mousePosition - player.position;
    player.player.setRotation(atan2(delta.y, delta.x) * 180 / M_PI);
    animatePlayer(elapsedTime, player);
}

void initPlayer(Player &player)
{
    player.spriteLeft = 0;
    player.playerTexture.loadFromFile("img/player.png");
    player.playerTexture.setSmooth(true);
    player.player.setTexture(player.playerTexture);
    sf::IntRect playerSource(player.spriteLeft, SPRITE_TOP, SPRITE_WIDTH, SPRITE_HEIGTH);
    player.player.setTextureRect(playerSource);
    player.player.setOrigin(player.player.getLocalBounds().width / 2,
                            player.player.getLocalBounds().height / 2);
    player.player.setPosition(HERO_INITIAL_POSITION);
    player.player.setScale(0.5, 0.5);
    player.helth = 265;
    player.isMoving = false;
    player.isAnimationStopped = false;
    player.isLive = true;
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

bool isLive(Player &player)
{
    return player.isLive;
}

bool hit(sf::Clock &hitClock, Player &player)
{
    static sf::Time accumulatedTime;
    accumulatedTime += hitClock.restart();
    const sf::Time hitInterval = sf::milliseconds(HIT_INTERVAL_TIME);
    if (accumulatedTime >= hitInterval && player.helth > 0)
    {
        player.lastHit = hitClock.getElapsedTime();
        accumulatedTime = sf::Time::Zero;
        player.helth -= 1;
        if (player.helth < 0)
            player.helth = 0;

        return true;
    }
    else
    {
        return false;
    }
}