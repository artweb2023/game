#include "gamescene.h"

void createWindow(sf::RenderWindow &window)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Starship Troopers",
                  sf::Style::Default, settings);
    window.setFramerateLimit(MAX_FPS);
}

void handleEvents(sf::RenderWindow &window, GameScene &scene)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        handleEventsGameScene(window, event, scene);
    }
}

void update(sf::Clock &clock, sf::Clock &animationClockPlayer, sf::Clock &animationClockEnemy,
            sf::Clock &hitTime, sf::View &view, sf::Vector2f &mousePosition, GameScene &scene)
{
    const float elapsedTime = clock.getElapsedTime().asSeconds();
    updateGameScene(elapsedTime, animationClockPlayer, animationClockEnemy, hitTime, mousePosition, scene);
    clock.restart();
}

void render(sf::RenderWindow &window, GameScene &scene)
{
    window.clear(COLOR);
    drawGameScene(window, scene);
    window.display();
}

int main(int, char *[])
{
    sf::RenderWindow window;
    createWindow(window);
    GameScene scene;
    initializeGameScene(scene);
    sf::Clock clock;
    sf::Clock animationClockPlayer;
    sf::Clock animationClockEnemy;
    sf::Clock hitTime;
    while (window.isOpen())
    {
        handleEvents(window, scene);
        update(clock, animationClockPlayer, animationClockEnemy, hitTime, scene.camera.camera,
               scene.mousePosition, scene);
        render(window, scene);
    }
    destroyGameScene(scene);
    return 0;
}
