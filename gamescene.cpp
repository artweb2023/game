
#include "gamescene.h"

constexpr int numEnemies = 50;
constexpr float HIT_COOL_DOWN = 100;
/*void creatingEnemies(GameScene &scene, int numEnemies)
{
    for (int i = 0; i < numEnemies; ++i)
    {
        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>();
        initEnemy(*enemy);
        spawn(*enemy);
        scene.enemies.push_back(std::move(*enemy));
    }
}
*/
void initializeGameScene(GameScene &scene)
{
    initMenu(scene.menu);
    initMap(scene.map);
    initСamera(scene.camera, WINDOW_WIDTH, WINDOW_HEIGHT);
    initPlayer(scene.player);
    initAim(scene.aim);
    initBullet(scene.bullet);
    initHelth(scene.helth);
    initEnemy(scene.enemy);
    spawn(scene.enemy);
    scene.playerScore = 0;
    scene.imageGameOver.loadFromFile("img/game_over.jpg");
    scene.imageGameOverBackground.loadFromImage(scene.imageGameOver);
    scene.imageGameWin.loadFromFile("img/game_win.jpg");
    scene.imageGameWinBackground.loadFromImage(scene.imageGameWin);
    scene.gameState = GameState::Playing;
}

void updateEntities(const sf::Vector2f &mousePosition, Player &player, Aim &aim)
{
    updatePlayer(player, mousePosition);
    updateAim(player, aim);
}

void getDamagePlayer(sf::Clock &hitClock, GameScene &scene)
{
    if (scene.enemy.enemy.getGlobalBounds().intersects(scene.player.player.getGlobalBounds()))
    {
        if (scene.enemy.isLive)
        {
            if (hit(hitClock, scene.player))
            {
                hitClock.restart();
            }
        }
    }
}

void getDamageEnemy(sf::Clock &hitClock, GameScene &scene)
{
    if (scene.enemy.enemy.getGlobalBounds().intersects(scene.bullet.bullet.getGlobalBounds()))
    {
        if (hitEnemy(hitClock, scene.enemy))
        {
            scene.bullet.isFlight = false;
            scene.enemy.isLive = false;
            scene.playerScore += 1;
        }
    }
}

void updateGameScene(float elapsedTime, sf::Clock &animationClockPlayer,
                     sf::Clock &animationClockEnemy, sf::Clock &hitClock,
                     sf::Vector2f &mousePosition, GameScene &scene)
{
    if (scene.gameState == GameState::Playing)
    {
        setCenterCamera(scene.player, scene.camera);
        updateEntities(mousePosition, scene.player, scene.aim);
        animatePlayer(elapsedTime, scene.player, animationClockPlayer);
        updateEnemy(elapsedTime, scene.enemy, scene.player, animationClockEnemy);
        updateBullet(scene.bullet, elapsedTime);
        movePlayer(scene.player, elapsedTime);
        update(scene.player, scene.helth);
        getDamagePlayer(hitClock, scene);
        getDamageEnemy(hitClock, scene);
        if (scene.player.helth == 0)
        {
            scene.bullet.isFlight = false;
            scene.gameState = GameState::PlayerLosed;
        }
        if (scene.playerScore == 1)
        {
            scene.bullet.isFlight = false;
            scene.gameState = GameState::PlayerWin;
        }
    }
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition,
                 Camera &camera, sf::RenderWindow &window)
{
    mousePosition = window.mapPixelToCoords(sf::Vector2i(event.x, event.y), camera.camera);
}

void handleEventsGameScene(sf::RenderWindow &window, sf::Event &event, GameScene &scene)
{
    switch (event.type)
    {
    case sf::Event::MouseMoved:
        onMouseMove(event.mouseMove, scene.mousePosition, scene.camera, window);
        break;
    case sf::Event::KeyPressed:
        handlePlayerKeyPress(event.key, scene.player);
        changeRotateCamera(event.key, scene.camera, WINDOW_WIDTH, WINDOW_HEIGHT);
        break;
    case sf::Event::KeyReleased:
        handlePlayerKeyRelease(event.key, scene.player);
        break;
    case sf::Event::MouseButtonPressed:
        if (event.mouseButton.button == sf::Mouse::Left)
            shoot(scene.bullet, scene.player.player.getPosition().x,
                  scene.player.player.getPosition().y, scene.mousePosition.x, scene.mousePosition.y);
        break;
    case sf::Event::MouseWheelScrolled:
        if (scene.player.isLive)
            scrollCamera(event.mouseWheelScroll, scene.camera);
        break;
    default:
        break;
    }
}

void drawPlayerScore(sf::RenderWindow &window, GameScene &scene)
{
    std::ostringstream playerScoreString;
    playerScoreString << scene.playerScore;
    std::string text = "frag: " + playerScoreString.str();
    sf::Vector2f viewCenter = window.getView().getCenter();
    sf::Vector2f viewSize = window.getView().getSize();
    float xPosition = viewCenter.x - scene.helth.spriteHelth.getGlobalBounds().width / 7.8f;
    float yPosition = viewCenter.y - viewSize.y / 2.0f + 20;
    sf::Vector2f playerScorePosition(xPosition, yPosition);
    showText(text, 30, playerScorePosition, sf::Color::Red, scene.text);
    drawText(window, scene.text, playerScorePosition);
}

void drawGameScreen(sf::RenderWindow &window, GameScene &scene)
{
    sf::Vector2f cameraPosition = scene.camera.camera.getCenter();
    sf::Vector2f gameOverScreenPosition(cameraPosition.x - WINDOW_WIDTH / 2, cameraPosition.y - WINDOW_HEIGHT / 2);
    std::string gameOverText = "Game Over";
    std::string gameWinText = "You Win";

    sf::Sprite gameOverSprite;
    sf::Vector2f textPosition;

    if (scene.gameState == GameState::PlayerLosed)
    {
        gameOverSprite.setTexture(scene.imageGameOverBackground);
        textPosition = sf::Vector2f(cameraPosition.x - 100, cameraPosition.y - 100);
        showText(gameOverText, 50, textPosition, sf::Color::White, scene.text);
    }
    else if (scene.gameState == GameState::PlayerWin)
    {
        gameOverSprite.setTexture(scene.imageGameWinBackground);
        textPosition = sf::Vector2f(cameraPosition.x - 60, cameraPosition.y - 150);
        showText(gameWinText, 50, textPosition, sf::Color::White, scene.text);
    }

    gameOverSprite.setPosition(gameOverScreenPosition);
    window.draw(gameOverSprite);
    drawText(window, scene.text, textPosition);
}

void drawGameScene(sf::RenderWindow &window, GameScene &scene)
{
    if (scene.gameState == GameState::Playing)
    {
        drawMap(window, scene.map);
        window.draw(scene.player.player);
        setCamera(window, scene.camera);
        drawPlayerScore(window, scene);
        if (isVisible(scene.enemy))
            drawEnemy(window, scene.enemy);

        if (isLive(scene.player))
            window.draw(scene.aim.aim);

        if (isInFlight(scene.bullet))
            window.draw(scene.bullet.bullet);

        drawHelth(window, scene.helth);
    }
    if (scene.gameState == GameState::PlayerLosed || scene.gameState == GameState::PlayerWin)
    {
        drawGameScreen(window, scene);
    }
}

void destroyGameScene(GameScene &scene)
{
    cleanupMap(scene.map);
}
