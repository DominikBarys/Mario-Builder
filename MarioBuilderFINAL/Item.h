#pragma once

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Item
{
public:

	const unsigned int WINDOW_WIDTH = 800;
	const unsigned int WINDOW_HEIGHT = 600;

	bool isCollected = false;

	sf::Texture coinTex;
	sf::Sprite coinSprite;

	sf::Clock coinSpawnTimer;

	int coinScorePoints = 300;

	virtual void spawnCoin() = 0;

};

