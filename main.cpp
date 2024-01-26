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
        else if (event.type == sf::Event::MouseMoved)
        {
            onMouseMove(event.mouseMove, scene.mousePosition, scene.camera, window);
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            shoot(scene.bullet, scene.player.player.getPosition().x,
                  scene.player.player.getPosition().y, scene.mousePosition.x, scene.mousePosition.y);
            playShotSound(scene.sound);
        }
        handleEventsGameScene(window, event, scene);
    }
}

void update(sf::Clock &clock, sf::Clock &hitTimeEnemy, sf::Clock hitTimePlayer, sf::View &view,
            sf::Vector2f &mousePosition, GameScene &scene)
{
    const float elapsedTime = clock.getElapsedTime().asSeconds();
    updateGameScene(elapsedTime, hitTimeEnemy, hitTimePlayer, mousePosition, scene);
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
    sf::Clock hitTimeEnemy;
    sf::Clock hitTimePlayer;
    while (window.isOpen())
    {
        handleEvents(window, scene);
        update(clock, hitTimeEnemy, hitTimePlayer, scene.camera.camera,
               scene.mousePosition, scene);
        render(window, scene);
    }
    destroyGameScene(scene);
    return 0;
}
