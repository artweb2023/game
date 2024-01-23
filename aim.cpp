#include "aim.h"

static const float AIM_DISTANCE = 80.0f;

void initAim(Aim &aim)
{
    aim.aimTexture.loadFromFile("img/crosshair1.png");
    aim.aimTexture.setSmooth(true);
    aim.aim.setTexture(aim.aimTexture);
    aim.aim.setOrigin(aim.aim.getLocalBounds().width / 2, aim.aim.getLocalBounds().height / 2);
    aim.aim.setScale(0.5, 0.5);
}

void updateAim(Player &player, Aim &aim)
{
    sf::Vector2f aimOffset = toEuclidean(AIM_DISTANCE, player.player.getRotation() * M_PI / 180.0f);
    aim.position = player.position + aimOffset;
    aim.aim.setPosition(aim.position);
}