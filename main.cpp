#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "map.h"

const unsigned ANTIALIASING_LEVEL = 8;
const unsigned WINDOW_WIDTH = 800;
const unsigned WINDOW_HEIGHT = 600;
const unsigned MAX_FPS = 120;
const unsigned viewTop = 300;
const unsigned viewLeft = 400;
const unsigned viewButton = 2200;
const unsigned viewRigth = 3600;

void createWindow(sf::RenderWindow &window)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Starship Troopers",
                  sf::Style::Default, settings);
    window.setFramerateLimit(MAX_FPS);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition, sf::View &view, sf::RenderWindow &window)
{
    mousePosition = window.mapPixelToCoords(sf::Vector2i(event.x, event.y), view);
}

void setCenterCamera(Player &player, sf::View &view)
{
    float tempX = player.position.x;
    float tempY = player.position.y;
    if (player.position.x < viewLeft)
        tempX = viewLeft;
    if (player.position.y < viewTop)
        tempY = viewTop;
    if (player.position.x > viewRigth)
        tempX = viewRigth;
    if (player.position.y > viewButton)
        tempY = viewButton;
    view.setCenter(tempX, tempY);
}

void changeViewScroll(const sf::Event::MouseWheelScrollEvent &event, sf::View &view)
{
    float zoomFactor = 1.1f;
    if (event.delta > 0)
    {
        view.zoom(1.f / zoomFactor);
    }
    else if (event.delta < 0)
    {
        view.zoom(zoomFactor);
    }
}

void changeView(const sf::Event::KeyEvent &event, sf::View &view)
{
    switch (event.code)
    {
    case sf::Keyboard::Right:
        view.rotate(1.f);
        break;
    case sf::Keyboard::Left:
        view.rotate(-1.f);
        break;
    case sf::Keyboard::Space:
        view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        break;
    default:
        break;
    }
}

void handleEvents(sf::RenderWindow &window, Player &player, sf::Vector2f &mousePosition,
                  Bullet &bullet, sf::View &view)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition, view, window);
            break;
        case sf::Event::KeyPressed:
            handlePlayerKeyPress(event.key, player);
            changeView(event.key, view);
            break;
        case sf::Event::KeyReleased:
            handlePlayerKeyRelease(event.key, player);
            break;
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                shoot(bullet, player.player.getPosition().x, player.player.getPosition().y, mousePosition.x, mousePosition.y);
            }
            break;
        case sf::Event::Resized:
            view.setSize(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
            break;
        case sf::Event::MouseWheelScrolled:
            changeViewScroll(event.mouseWheelScroll, view); // Передаем событие колеса мыши
            break;
        default:
            break;
        }
    }
}

void updateEntities(const sf::Vector2f &mousePosition, Player &player, Aim &aim)
{
    updatePlayer(player, mousePosition);
    updateAim(player, aim);
}

void update(Player &player, sf::Clock &clock, sf::Clock &animationClockPlayer,
            sf::Clock &animationClockEnemy, Bullet &bullet, Enemy &enemy, sf::View &view,
            sf::Vector2f &mousePosition, Aim &aim)
{
    const float elapsedTime = clock.getElapsedTime().asSeconds();
    updateEntities(mousePosition, player, aim);
    animatePlayer(elapsedTime, player, animationClockPlayer);
    updateEnemy(elapsedTime, enemy, player, animationClockEnemy);
    updateBullet(bullet, elapsedTime);
    movePlayer(player, elapsedTime);
    setCenterCamera(player, view);
    clock.restart();
}

void render(sf::RenderWindow &window, Player &player, Aim &aim, Bullet &bullet, Enemy &enemy, Map &map, const sf::View &view)
{
    window.clear(sf::Color(128, 106, 89));
    drawMap(window, map);
    window.setView(view);
    window.draw(player.player);
    window.draw(enemy.enemy);
    window.draw(aim.aim);
    if (isInFlight(bullet))
    {
        window.draw(getSprite(bullet));
    }
    window.display();
}

int main(int, char *[])
{
    sf::RenderWindow window;
    createWindow(window);
    Player player;
    initPlayer(player);
    Aim aim;
    initAim(aim);
    Bullet bullet;
    initBullet(bullet);
    Enemy enemy;
    initEnemy(enemy);
    spawn(enemy);
    Map map;
    initializeMap(map);
    sf::Clock clock;
    sf::Clock animationClockPlayer;
    sf::Clock animationClockEnemy;
    sf::View view;
    view.setSize(static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT));
    sf::Vector2f mousePosition;
    while (window.isOpen())
    {
        handleEvents(window, player, mousePosition, bullet, view);
        update(player, clock, animationClockPlayer, animationClockEnemy, bullet, enemy, view, mousePosition, aim);
        render(window, player, aim, bullet, enemy, map, view);
    }
    cleanupMap(map);
    return 0;
}
