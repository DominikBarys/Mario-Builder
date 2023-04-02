#include "Enemy.h"

sf::Clock& Enemy::getSpawnTimer()
{
    return spawnTimer;
}

sf::Vector2f& Enemy::getEnemyVelocity()
{
	return enemyVelocity;
}

sf::Sprite& Enemy::getEnemySprite()
{
	return enemySprite;
}

void Enemy::setEnemyTexture(std::string path)
{
	if (!enemyTex.loadFromFile(path))
	{
		std::cout<<"Cannot load Gooba texture from file!"<<std::endl;
		exit(0);
	}
}

void Enemy::updateEnenyAnim()
{
	if (enemyAnimTimer.getElapsedTime().asSeconds() >= 0.5f)
	{
		enemyAnimTimer.restart();
		if (enemyIntRectPos == 16)
		{
			enemyIntRectPos = 0;
		}
		else if (enemyIntRectPos == 0)
		{
			enemyIntRectPos = 16;
		}

		enemySprite.setTextureRect(sf::IntRect(enemyIntRectPos, 0, 16, 16));
	}
}

int& Enemy::getEnemyScorePoints()
{
    return enemyScorePoints;
}

bool& Enemy::getEnemyDestroyed()
{
    return enemydestroyed;
}

sf::Clock& Enemy::getEnemySpawnTimer()
{
    return spawnTimer;
}

void Enemy::setEnemy(int x, int y)
{
	enemySprite.setPosition(x, y);
	enemySprite.setScale(3.f, 3.f);
	enemySprite.setTexture(enemyTex);
	enemySprite.setTextureRect(sf::IntRect(enemyIntRectPos, 0, 16, 16));
	updateEnenyAnim();
}

void Enemy::setEnemyDestroyed()
{
    enemydestroyed = true;
}

void Enemy::enemyCollisionWithScreen()
{
	if (enemySprite.getPosition().x <= 0)
	{
		enemySprite.setPosition(0, enemySprite.getPosition().y);
		enemyVelocity.x = -enemyVelocity.x;
	}
	if (enemySprite.getPosition().x + enemySize >= WINDOW_WIDTH)
	{
		enemySprite.setPosition(WINDOW_WIDTH - enemySize, enemySprite.getPosition().y);
		enemyVelocity.x = -enemyVelocity.x;
	}
	if (enemySprite.getPosition().y <= 0)
	{
		enemySprite.setPosition(enemySprite.getPosition().x, 0);
	}
	if (enemySprite.getPosition().y + enemySize >= WINDOW_HEIGHT)
	{
		enemySprite.setPosition(enemySprite.getPosition().x, WINDOW_HEIGHT - enemySize);
	}
}

void Enemy::enemyCollisionWithWalls(std::vector<sf::RectangleShape> walls)
{
    sf::FloatRect nextEnemyPos;

    enemyVelocity.y = 5.f;
    for (auto& wall : walls)
    {
        sf::FloatRect enemyBounds = enemySprite.getGlobalBounds();
        sf::FloatRect wallBounds = wall.getGlobalBounds();

        nextEnemyPos = enemyBounds;

        nextEnemyPos.left += enemyVelocity.x;
        nextEnemyPos.top += enemyVelocity.y;

        if (wallBounds.intersects(nextEnemyPos))
        {
            //Bottom collision
            if (enemyBounds.top < wallBounds.top
                && enemyBounds.top + enemyBounds.height < wallBounds.top + wallBounds.height
                && enemyBounds.left < wallBounds.left + wallBounds.width
                && enemyBounds.left + enemyBounds.width > wallBounds.left)
            {
                enemyVelocity.y = 0.f;
                enemySprite.setPosition(enemyBounds.left, wallBounds.top - enemyBounds.height);
            }

            //Top collision
            if (enemyBounds.top > wallBounds.top
                && enemyBounds.top + enemyBounds.height > wallBounds.top + wallBounds.height
                && enemyBounds.left < wallBounds.left + wallBounds.width
                && enemyBounds.left + enemyBounds.width > wallBounds.left)
            {
                enemyVelocity.y = 0.f;
                enemySprite.setPosition(enemyBounds.left, wallBounds.top + wallBounds.height);
            }

            //Right collision
            if (enemyBounds.left < wallBounds.left
                && enemyBounds.left + enemyBounds.width < wallBounds.left + wallBounds.width
                && enemyBounds.top < wallBounds.top + wallBounds.height
                && enemyBounds.top + enemyBounds.height > wallBounds.top)
            {
                enemyVelocity.x = -enemyVelocity.x;
                enemySprite.setPosition(wallBounds.left - enemyBounds.width, enemyBounds.top);
            }

            //Left collision
            if (enemyBounds.left > wallBounds.left
                && enemyBounds.left + enemyBounds.width > wallBounds.left + wallBounds.width
                && enemyBounds.top < wallBounds.top + wallBounds.height
                && enemyBounds.top + enemyBounds.height > wallBounds.top)
            {
                enemyVelocity.x = -enemyVelocity.x;
                enemySprite.setPosition(wallBounds.left + wallBounds.width, enemyBounds.top);
            }
        }
    }
}

void Enemy::enemyUpdate(Enemy& enemy, std::vector<sf::RectangleShape>& walls)
{
    enemy.enemyCollisionWithScreen();
    enemy.getEnemySprite().move(enemy.getEnemyVelocity());
    enemy.enemyCollisionWithWalls(walls);
    enemy.updateEnenyAnim();
}

void Enemy::enemySpawn(Enemy& enemy)
{
    srand(time(NULL));
    float x = (rand() % 730) + 30;
    float y = (rand() % 100) + 20;
    std::cout << "ENEMY X: " << x << std::endl;
    std::cout << "ENEMY Y: " << y << std::endl;
    enemy.getEnemySprite().setScale(3.f, 3.f);
    enemy.getEnemySprite().setPosition(x, y);
    enemy.getEnemyDestroyed() = false;
    enemy.getEnemySpawnTimer().restart();
}

