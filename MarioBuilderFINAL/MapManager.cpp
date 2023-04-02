#include "MapManager.h"

void MapManager::loadMap(std::string path)
{
	file.open(path, std::ios::in);
	if (file.good())
	{
		while (!this->file.eof())
		{
			std::getline(file, line);
			this->fromFile.push_back(line);
		}
	}
	file.close();
}

void MapManager::regexCheck()
{
	for (int i = 0; i < MAP_ROWS; i++)
	{
		std::string tmp = fromFile[i];
		checkMap = std::regex_match(fromFile[i], rule);
		if (!checkMap)
		{
			std::cout << "Pattern in map file is incorrect!" << std::endl;
			exit(0);
		}
		for (int j = 0; j < MAP_COLS; j++)
		{
			if (tmp[j] == '#')
			{
				Wall block(j, i);
				walls.push_back(block.wall);
			}
		}
	}
}

void MapManager::addWalls(sf::RenderWindow& window, int& materials)
{
	mousePosGrid.x = sf::Mouse::getPosition(window).x / (int)gridSize;
	mousePosGrid.y = sf::Mouse::getPosition(window).y / (int)gridSize;

	bool exists = false;

	for (int i = 0; i < walls.size(); i++)
	{
		if (walls[i].getPosition().x / (int)gridSize == mousePosGrid.x
			&& walls[i].getPosition().y / (int)gridSize == mousePosGrid.y)
		{
			exists = true;
		}

	}
		if (!exists)
		{
			if (materials != 0)
			{
				Wall block(mousePosGrid.x, mousePosGrid.y);
				walls.push_back(block.wall);
				materials--;
			}
		}
	
}

void MapManager::removeWalls(sf::RenderWindow& window, int& materials)
{
	mousePosGrid.x = sf::Mouse::getPosition(window).x / (int)gridSize;
	mousePosGrid.y = sf::Mouse::getPosition(window).y / (int)gridSize;

	bool exists = false;
	int index = -1;
	for (int i = 0; i < walls.size() && !exists; i++)
	{
		if (walls[i].getPosition().x / (int)gridSize == mousePosGrid.x
			&& walls[i].getPosition().y / (int)gridSize == mousePosGrid.y)
		{
			exists = true;
			index = i;
		}
	}

	if (exists)
	{
		if (materials < 30)
		{
			walls.erase(walls.begin() + index);
			materials++;

		}
	}
}

std::string& MapManager::getMainMap()
{
	return mainMap;
}

std::string& MapManager::getTestMap()
{
	return testMap;
}

void MapManager::initMap(std::string& path)
{
	loadMap(path);
	regexCheck();
}

void MapManager::draw(sf::RenderWindow& window)
{
	for (auto& i : walls)
	{
		window.draw(i);
	}
}

