#pragma once

#include <SFML/Graphics.hpp>
#include "player.h"

struct Camera
{
    sf::View camera;
};

void initСamera(Camera &camera, const unsigned WINDOW_WIDTH, const unsigned WINDOW_HEIGHT);
void setCamera(sf::RenderWindow &window, const Camera &camera);
void setCenterCamera(Player &player, Camera &camera);
void scrollCamera(const sf::Event::MouseWheelScrollEvent &event, Camera &camera);
void changeRotateCamera(const sf::Event::KeyEvent &event, Camera &camera,
                        const unsigned WINDOW_WIDTH, const unsigned WINDOW_HEIGHT);