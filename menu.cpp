#include "menu.h"

constexpr int NUM_BUTTONS = 3;
constexpr float BUTTON_WIDTH = 200.0f;
constexpr float BUTTON_HEIGHT = 50.0f;
constexpr float BUTTON_SPACING = 20.0f;
constexpr float RECT_WIDTH = 250.0f;
constexpr float RECT_HEIGHT = 300.0f;
const sf::Color LIGHT_GRAY(200, 200, 200, 150);
const sf::Color DARK_GRAY(100, 100, 100, 150);
sf::Color COLOR(255, 255, 255, 150);

void initButton(float centerX, float centerY, Menu &menu)
{
    float buttonX = centerX + (RECT_WIDTH - BUTTON_WIDTH) / 2.0f;
    float totalButtonHeight = NUM_BUTTONS * BUTTON_HEIGHT + (NUM_BUTTONS - 1) * BUTTON_SPACING;
    float buttonY = centerY + (RECT_HEIGHT - totalButtonHeight) / 2.0f;

    for (int i = 0; i < NUM_BUTTONS; ++i)
    {
        sf::RectangleShape buttonRect(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
        buttonRect.setPosition(buttonX, buttonY);
        buttonRect.setFillColor(COLOR);
        buttonRect.setOutlineColor(sf::Color(255, 255, 255));
        buttonRect.setOutlineThickness(1.0f);
        menu.buttonRectangles.push_back(buttonRect);
        buttonY += BUTTON_HEIGHT + BUTTON_SPACING;
    }
}

void initMenu(Menu &menu)
{
    menu.menuBackground.loadFromFile("img/menu.jpg");
    menu.menuBackground.setSmooth(true);
    menu.menu.setTexture(menu.menuBackground);
    menu.menu.setPosition(0, 0);
    menu.rectangle = sf::RectangleShape(sf::Vector2f(RECT_WIDTH, RECT_HEIGHT));
    float centerX = (800 - RECT_WIDTH) / 2.0f;
    float centerY = (600 - RECT_HEIGHT) / 2.0f;
    menu.rectangle.setPosition(centerX, centerY);
    menu.rectangle.setFillColor(COLOR);
    menu.rectangle.setOutlineColor(sf::Color(255, 255, 255));
    menu.rectangle.setOutlineThickness(1.0f);
    menu.mainMenuSelected = 3;
    initButton(centerX, centerY, menu);
    showText("Play", 50, sf::Vector2f(350, 198), sf::Color::White, menu.playText);
    showText("Level", 50, sf::Vector2f(350, 268), sf::Color::White, menu.levelText);
    showText("Exit", 50, sf::Vector2f(350, 338), sf::Color::White, menu.exitText);
}

void moveUp(Menu &menu)
{
    if (menu.mainMenuSelected > 0 && menu.mainMenuSelected <= 3)
    {
        menu.buttonRectangles[menu.mainMenuSelected].setFillColor(LIGHT_GRAY);
        menu.mainMenuSelected--;
        menu.buttonRectangles[menu.mainMenuSelected].setFillColor(DARK_GRAY);
    }
}

void moveDown(Menu &menu)
{
    if (menu.mainMenuSelected < menu.buttonRectangles.size() - 1)
    {
        menu.buttonRectangles[menu.mainMenuSelected].setFillColor(LIGHT_GRAY);
        menu.mainMenuSelected++;
        menu.buttonRectangles[menu.mainMenuSelected].setFillColor(DARK_GRAY);
    }
}

void drawMenu(sf::RenderWindow &window, Menu &menu)
{
    window.draw(menu.menu);
    window.draw(menu.rectangle);

    for (const auto &buttonRect : menu.buttonRectangles)
    {
        window.draw(buttonRect);
    }

    window.draw(menu.playText.text);
    window.draw(menu.levelText.text);
    window.draw(menu.exitText.text);
}