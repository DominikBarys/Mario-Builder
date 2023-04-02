#pragma once

#include "FileHandler.h"
#include "Wall.h"
#include <fstream>
#include <vector>
#include <regex>

class MapManager
{
private:

	const float gridSize = 20.f;

	sf::Vector2i mousePosGrid;

	std::regex rule{"[.#]{40}"};
	bool checkMap;


	std::vector<std::string> fromFile;
	std::fstream file;
	std::string line;


	static const short unsigned int MAP_COLS = 40;
	static const short unsigned int MAP_ROWS = 30;
	
	char map[MAP_ROWS][MAP_COLS];

	std::string mainMap = "Main_Map.txt";
	std::string testMap = "Test_Map.txt";

	void loadMap(std::string path);

	void regexCheck();

public:

	std::vector<sf::RectangleShape> walls;

	void addWalls(sf::RenderWindow& window, int& materials);
	void removeWalls(sf::RenderWindow& window, int& materials);

	std::string& getMainMap();
	std::string& getTestMap();

	void initMap(std::string& cur_map);

	void draw(sf::RenderWindow& window);

};

