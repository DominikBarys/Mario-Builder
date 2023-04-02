#include "Wall.h"

Wall::Wall(float x, float y)
{
	this->wall.setFillColor({ 139,69,19 }); // Brown RGB color
	this->wall.setSize({ gridSize,gridSize });
	this->wall.setPosition(x * gridSize, y * gridSize);
}
