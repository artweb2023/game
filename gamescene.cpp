#include "gamescene.h"

constexpr int NUM_ENEMIES = 50;
constexpr float MAX_DAMAGE_DISTANCE = 10.f;

void creatingEnemies(GameScene &scene, int numEnemies)
{
    for (int i = 0; i < numEnemies; ++i)
    {
        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>();
        initEnemy(*enemy);
        spawn(*enemy);
        scene.enemies.push_back(std::move(enemy));
    }
}

void initializeGameScene(GameScene &scene)
{
    if (!scene.isMenuInitialized)
        initMenu(scene.menu);
    initMap(scene.map);
    initСamera(scene.camera, WINDOW_WIDTH, WINDOW_HEIGHT);
    initPlayer(scene.player);
    initAim(scene.aim);
    initBullet(scene.bullet);
    initHelth(scene.helth);
    creatingEnemies(scene, NUM_ENEMIES);
    scene.playerScore = 0;
    scene.imageGameOver.loadFromFile("img/game_over.jpg");
    scene.imageGameOverBackground.loadFromImage(scene.imageGameOver);
    scene.imageGameWin.loadFromFile("img/game_win.jpg");
    scene.imageGameWinBackground.loadFromImage(scene.imageGameWin);
    scene.gameState = GameState::Menu;
    scene.isMenuInitialized = false;
}

void updateEntities(float elapsedTime, const sf::Vector2f &mousePosition, Player &player, Aim &aim)
{
    updatePlayer(elapsedTime, player, mousePosition);
    updateAim(player, aim);
}

float calculateDistance(const sf::Vector2f &point1, const sf::Vector2f &point2)
{
    float dx = point1.x - point2.x;
    float dy = point1.y - point2.y;
    return std::sqrt(dx * dx + dy * dy);
}

void getDamagePlayer(sf::Clock &hitClock, GameScene &scene)
{
    for (const auto &enemyPtr : scene.enemies)
    {
        sf::Sprite enemySprite = getSprite(*enemyPtr);

        if (enemySprite.getGlobalBounds().intersects(scene.player.player.getGlobalBounds()) && enemyPtr->isLive)
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
    for (const auto &enemyPtr : scene.enemies)
    {
        sf::Sprite enemySprite = getSprite(*enemyPtr);

        if (enemySprite.getGlobalBounds().intersects(scene.bullet.bullet.getGlobalBounds()))
        {
            float distance = calculateDistance(enemySprite.getPosition(), scene.bullet.bullet.getPosition());
            if (distance < MAX_DAMAGE_DISTANCE && hitEnemy(hitClock, *enemyPtr, scene.bullet))
            {
                scene.bullet.isFlight = false;
                enemyPtr->isLive = false;
                scene.playerScore += 1;
                hitClock.restart();
            }
        }
    }
}

void updateGameScene(float elapsedTime, sf::Clock &hitTimeEnemy, sf::Clock &hitTimePlayer,
                     sf::Vector2f &mousePosition, GameScene &scene)
{
    if (scene.gameState == GameState::Playing)
    {
        setCenterCamera(scene.player, scene.camera);
        updateEntities(elapsedTime, mousePosition, scene.player, scene.aim);
        for (const auto &enemy : scene.enemies)
        {
            updateEnemy(elapsedTime, *enemy, scene.player);
        }
        updateBullet(scene.bullet, elapsedTime, scene.camera, WINDOW_WIDTH, WINDOW_HEIGHT);
        movePlayer(scene.player, elapsedTime);
        update(scene.player, scene.helth);
        getDamagePlayer(hitTimeEnemy, scene);
        getDamageEnemy(hitTimePlayer, scene);
        if (scene.player.helth == 0)
        {
            scene.bullet.isFlight = false;
            scene.gameState = GameState::PlayerLosed;
        }
        if (scene.playerScore == NUM_ENEMIES)
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

void selectInMenu(sf::RenderWindow &window, const sf::Event::KeyEvent &event, GameScene &scene)
{
    switch (event.code)
    {
    case sf::Keyboard::Up:
        moveUp(scene.menu);
        break;
    case sf::Keyboard::Down:
        moveDown(scene.menu);
        break;
    case sf::Keyboard::Enter:
        if (scene.menu.mainMenuSelected == 0)
            scene.gameState = GameState::Playing;
        else if (scene.menu.mainMenuSelected == 1)
            scene.gameState = GameState::Lavel;
        else
            window.close();
        break;
    case sf::Keyboard::Escape:
        if (scene.gameState == GameState::PlayerWin || scene.gameState == GameState::PlayerLosed)
        {
            scene.gameState = GameState::Menu;
            scene.isMenuInitialized = true;
            initializeGameScene(scene);
        }
        break;
    default:
        break;
    }
}

void handleEventsGameScene(sf::RenderWindow &window, sf::Event &event, GameScene &scene)
{
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        if (scene.gameState == GameState::Playing)
        {
            handlePlayerKeyPress(event.key, scene.player);
            changeRotateCamera(event.key, scene.camera, WINDOW_WIDTH, WINDOW_HEIGHT);
        }
        else
        {
            selectInMenu(window, event.key, scene);
        }
        break;
    case sf::Event::KeyReleased:
        handlePlayerKeyRelease(event.key, scene.player);
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
    scene.gameScreenPosition = sf::Vector2f(cameraPosition.x - WINDOW_WIDTH / 2, cameraPosition.y - WINDOW_HEIGHT / 2);
    std::string gameOverText = "Game Over";
    std::string gameWinText = "You Win";
    sf::Sprite gameStateSprite;
    sf::Vector2f textPosition;

    if (scene.gameState == GameState::PlayerLosed)
    {
        gameStateSprite.setTexture(scene.imageGameOverBackground);
        textPosition = sf::Vector2f(cameraPosition.x - 100, cameraPosition.y - 100);
        showText(gameOverText, 50, textPosition, sf::Color::White, scene.text);
    }
    else if (scene.gameState == GameState::PlayerWin)
    {
        gameStateSprite.setTexture(scene.imageGameWinBackground);
        textPosition = sf::Vector2f(cameraPosition.x - 60, cameraPosition.y - 150);
        showText(gameWinText, 50, textPosition, sf::Color::White, scene.text);
    }
    updateMenuPostion(scene.menu, scene.gameScreenPosition);
    gameStateSprite.setPosition(scene.gameScreenPosition);
    window.draw(gameStateSprite);
    drawText(window, scene.text, textPosition);
}

void drawGameScene(sf::RenderWindow &window, GameScene &scene)
{
    drawMenu(window, scene.menu);
    if (scene.gameState == GameState::Playing)
    {
        drawMap(window, scene.map);
        drawPlayerScore(window, scene);
        drawEnemies(window, scene.enemies);
        window.draw(scene.player.player);
        setCamera(window, scene.camera);
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
