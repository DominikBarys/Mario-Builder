#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Entity
{
public:

	const unsigned int WINDOW_WIDTH = 800;
	const unsigned int WINDOW_HEIGHT = 600;
	
	sf::Clock spawnTimer;
	sf::Texture enemyTex;
	sf::Vector2f enemyVelocity{5.f,5.f};
	sf::Sprite enemySprite;

	int enemyScorePoints;
	bool enemydestroyed = false;

	virtual void enemyCollisionWithScreen() = 0;
	virtual void enemyCollisionWithWalls(std::vector<sf::RectangleShape> walls) = 0;
};

