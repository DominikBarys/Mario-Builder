#include "Coin.h"

void Coin::setCoinTexture(std::string path)
{
	if (!coinTex.loadFromFile(path))
	{
		std::cout << "Cannot load coin file!" << std::endl;
	}
}

sf::Sprite& Coin::getCoinSprite()
{
	return coinSprite;
}

sf::Clock& Coin::getCoinSpawnTimer()
{
	return coinSpawnTimer;
}

int& Coin::getCoinScorePoints()
{
	return coinScorePoints;
}

bool& Coin::getIsCollected()
{
	return isCollected;
}

void Coin::spawnCoin()
{
	if (isCollected && coinSpawnTimer.getElapsedTime().asSeconds() >= 2)
	{
		coinRandX = rand() % (WINDOW_WIDTH - 20);
		coinRandY = rand() % (WINDOW_HEIGHT - 20);
		std::cout << "SPAWNUJE COIN" << std::endl;
		coinSprite.setPosition(coinRandX, coinRandY);
		coinSprite.setScale(2.5f, 2.5f);
		isCollected = false;
	}
}

void Coin::setCoin()
{
	coinSprite.setPosition(coinRandX, coinRandY);
	coinSprite.setScale(2.5f, 2.5f);
	coinSprite.setTexture(coinTex);
	coinSprite.setTextureRect(sf::IntRect(coinIntRectPos, 0, 16, 16));
	updateCoinAnim();
}

void Coin::updateCoinAnim()
{
	if (coinAnimTimer.getElapsedTime().asSeconds() >= 0.1f)
	{
		coinAnimTimer.restart();
		if (coinIntRectPos >= 144)
		{
			coinIntRectPos = 0;
		}

		coinSprite.setTextureRect(sf::IntRect(coinIntRectPos, 0, 16, 16));
		coinIntRectPos += 16;
	}
}
