#pragma once

#include "camera.h"
#include "player.h"
#include "helth.h"
#include "map.h"
#include "enemy.h"
#include "bullet.h"
#include "aim.h"
#include "text.h"
#include "menu.h"
#include "sound.h"
#include <iostream>
#include <sstream>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
const unsigned ANTIALIASING_LEVEL = 8;
const unsigned MAX_FPS = 120;
const sf::Color COLOR(128, 106, 89);

enum class GameState
{
    Restart,
    Menu,
    Lavel,
    Playing,
    PlayerLosed,
    PlayerWin,
};

struct GameScene
{
    Camera camera;
    Map map;
    Player player;
    Aim aim;
    Bullet bullet;
    Helth helth;
    Enemy enemy;
    Text text;
    Menu menu;
    Sound sound;
    std::vector<std::unique_ptr<Enemy>> enemies;
    GameState gameState;
    sf::Vector2f mousePosition;
    sf::Image imageGameOver;
    sf::Texture imageGameOverBackground;
    sf::Image imageGameWin;
    sf::Texture imageGameWinBackground;
    sf::Vector2f gameScreenPosition;
    int playerScore;
    bool isMenuInitialized;
};

void initializeGameScene(GameScene &scene);
void updateGameScene(float elapsedTime, sf::Clock &hitTimeEnemy, sf::Clock &hitTimePlayer,
                     sf::Vector2f &mousePosition, GameScene &scene);
void drawGameScene(sf::RenderWindow &window, GameScene &scene);
void handleEventsGameScene(sf::RenderWindow &window, sf::Event &event, GameScene &scene);
void destroyGameScene(GameScene &scene);
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition,
                 Camera &camera, sf::RenderWindow &window);
