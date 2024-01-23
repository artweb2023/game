#include "camera.h"

constexpr unsigned VIEW_TOP = 300;
constexpr unsigned VIEW_LEFT = 400;
constexpr unsigned VIEW_BUTTON = 2200;
constexpr unsigned VIEW_RIGTH = 3600;

void initСamera(Camera &camera, const unsigned WINDOW_WIDTH, const unsigned WINDOW_HEIGHT)
{
    camera.camera.setSize(static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT));
}

void setCamera(sf::RenderWindow &window, const Camera &camera)
{
    window.setView(camera.camera);
}

void setCenterCamera(Player &player, Camera &camera)
{
    float tempX = player.position.x;
    float tempY = player.position.y;
    if (player.position.x < VIEW_LEFT)
        tempX = VIEW_LEFT;
    if (player.position.y < VIEW_TOP)
        tempY = VIEW_TOP;
    if (player.position.x > VIEW_RIGTH)
        tempX = VIEW_RIGTH;
    if (player.position.y > VIEW_BUTTON)
        tempY = VIEW_BUTTON;
    camera.camera.setCenter(tempX, tempY);
}

void scrollCamera(const sf::Event::MouseWheelScrollEvent &event, Camera &camera)
{
    float zoomFactor = 1.1f;
    if (event.delta > 0)
    {
        camera.camera.zoom(1.f / zoomFactor);
    }
    else if (event.delta < 0)
    {
        camera.camera.zoom(zoomFactor);
    }
}

void changeRotateCamera(const sf::Event::KeyEvent &event, Camera &camera,
                        const unsigned WINDOW_WIDTH, const unsigned WINDOW_HEIGHT)
{
    switch (event.code)
    {
    case sf::Keyboard::Right:
        camera.camera.rotate(1.f);
        break;
    case sf::Keyboard::Left:
        camera.camera.rotate(-1.f);
        break;
    case sf::Keyboard::Space:
        camera.camera.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        break;
    default:
        break;
    }
}