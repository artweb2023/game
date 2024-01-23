#include "helth.h"

constexpr float BOTTOM_MARGIN = 10.0f;

void initHelth(Helth &helth)
{
    helth.image.loadFromFile("img/helth.png");
    helth.image.createMaskFromColor(sf::Color(50, 96, 166));
    helth.textureHelth.loadFromImage(helth.image);
    helth.textureHelth.setSmooth(true);
    helth.spriteHelth.setTexture(helth.textureHelth);
    helth.spriteHelth.setScale(0.7f, 0.7f);
    helth.bar.setFillColor(sf::Color(255, 0, 0));
}

void update(Player &player, Helth &helth)
{
    if (player.helth > 0)
    {
        float healthBarWidth = player.helth;
        helth.bar.setSize(sf::Vector2f(healthBarWidth, 13.5f));
    }
}
void drawHelth(sf::RenderWindow &window, Helth &helth)
{
    sf::Vector2f viewCenter = window.getView().getCenter();
    sf::Vector2f viewSize = window.getView().getSize();
    float xPosition = viewCenter.x - helth.spriteHelth.getGlobalBounds().width / 2.0f;
    float yPosition = viewCenter.y + viewSize.y / 2.0f - BOTTOM_MARGIN - helth.spriteHelth.getGlobalBounds().height;
    helth.spriteHelth.setPosition(xPosition, yPosition);
    helth.bar.setPosition(xPosition + 35.f, yPosition + 10.f);
    window.draw(helth.spriteHelth);
    window.draw(helth.bar);
}