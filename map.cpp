#include "map.h"

static const std::string TEXTURE_PATH = "img/plan.png";
sf::String tileMap[HEIGHT_MAP] = {
    "0000000000000000000000000000000000000000",
    "0                                      0",
    "0   s           s          s           0",
    "0                                      0",
    "0                  s                   0",
    "0                                      0",
    "0                               s      0",
    "0                                      0",
    "0        s                             0",
    "0                                      0",
    "0      s            s        s         0",
    "0                                      0",
    "0                                      0",
    "0           s                          0",
    "0                                      0",
    "0                                      0",
    "0                              s       0",
    "0           s                          0",
    "0                                      0",
    "0                        s             0",
    "0     s                                0",
    "0                                  s   0",
    "0            s                         0",
    "0                                      0",
    "0000000000000000000000000000000000000000",
};

void initMap(Map &map)
{
    map.mapImage.loadFromFile(TEXTURE_PATH);
    map.map.loadFromImage(map.mapImage);
    map.map.setSmooth(true);
    map.spriteMap.setTexture(map.map);
    map.sprites = new sf::Sprite[HEIGHT_MAP * WIDTH_MAP];
    for (int i = 0; i < HEIGHT_MAP; i++)
    {
        for (int j = 0; j < WIDTH_MAP; j++)
        {
            sf::Sprite block;
            block.setTexture(map.map);
            if (tileMap[i][j] == '0')
                block.setTextureRect(sf::IntRect(1800, 0, 100, 100));
            else if (tileMap[i][j] == ' ')
            {
                block.setTextureRect(sf::IntRect(0, 0, 200, 200));
                block.setScale(0.5, 0.5);
            }
            else if (tileMap[i][j] == 's')
            {
                block.setTextureRect(sf::IntRect(210, 0, 200, 200));
                block.setScale(0.5, 0.5);
            }
            block.setPosition(j * 100, i * 100);
            map.sprites[i * WIDTH_MAP + j] = block;
        }
    }
}

void drawMap(sf::RenderWindow &window, const Map &map)
{
    for (size_t i = 0; i < HEIGHT_MAP; i++)
    {
        for (size_t j = 0; j < WIDTH_MAP; j++)
        {
            window.draw(map.sprites[i * WIDTH_MAP + j]);
        }
    }
}

bool checkMapWallsCollision(const sf::Vector2f &position)
{
    int columnIndex = static_cast<int>(position.x / BLOCK_SIZE);
    int rowIndex = static_cast<int>(position.y / BLOCK_SIZE);
    if (rowIndex >= 0 && rowIndex < HEIGHT_MAP && columnIndex >= 0 && columnIndex < WIDTH_MAP)
    {
        return tileMap[rowIndex][columnIndex] == '0';
    }
    return false;
}

void cleanupMap(Map &map)
{
    delete[] map.sprites;
}
