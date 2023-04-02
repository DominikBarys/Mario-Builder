#pragma once

#include "MapManager.h"
#include "Entity.h"

class Enemy : public Entity
{
private:

    float enemySize = 40.f;

    sf::Clock enemyAnimTimer;

    int enemyIntRectPos = 0;

    int enemyScorePoints = 500;

public:

    sf::Clock& getSpawnTimer();
    sf::Vector2f& getEnemyVelocity();
    sf::Sprite& getEnemySprite();
    void setEnemyTexture(std::string);
    void setEnemy(int x, int y);

    void setEnemyDestroyed();

    void updateEnenyAnim();

    int& getEnemyScorePoints();

    bool& getEnemyDestroyed();

    sf::Clock& getEnemySpawnTimer();

    void enemyCollisionWithScreen();
    void enemyCollisionWithWalls(std::vector<sf::RectangleShape> walls);

    static void enemyUpdate(Enemy& enemy, std::vector<sf::RectangleShape>& walls);

    static void enemySpawn(Enemy& enemy);
};

