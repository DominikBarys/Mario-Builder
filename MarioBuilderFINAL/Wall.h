#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Wall
{
private:
	const float gridSize = 20.f;
public:
	
	sf::RectangleShape wall;

	Wall(float x, float y);

};

