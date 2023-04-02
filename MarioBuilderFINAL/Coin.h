#pragma once

#include "Item.h"

class Coin : public Item
{
private:
	
	int coinIntRectPos = 0;

	float coinRandX = rand() % (WINDOW_WIDTH - 20);
	float coinRandY = rand() % (WINDOW_HEIGHT - 20);
	sf::Clock coinAnimTimer;
	
public:

	void setCoinTexture(std::string);
	sf::Sprite& getCoinSprite();
	sf::Clock& getCoinSpawnTimer();
	sf::Clock getCoinAnimTimer();

	int& getCoinScorePoints();

	bool& getIsCollected();

	void spawnCoin();

	void setCoin();
	void updateCoinAnim();
};

