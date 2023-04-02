#include "FileHandler.h"

void FileHandler::setBackground_Path() 
{
	path = std::filesystem::current_path();
	path /= "Textures";
	path /= "Background.jpg";
	background_path = path.string();
}

void FileHandler::setMap_Path(std::string& cur_map)
{
	path = std::filesystem::current_path();
	path /= "Maps";
	path /= cur_map;
	map_path = path.string();
}

void FileHandler::setFont_Path()
{
	path = std::filesystem::current_path();
	path /= "Fonts";
	path /= "Metropolitan.ttf";
	font_path = path.string();
}

void FileHandler::setMarioIdle_Path()
{
	path = std::filesystem::current_path();
	path /= "Textures";
	path /= "MarioIdle.png";
	marioIdle_path = path.string();
}

void FileHandler::setMarioWalk_Path()
{
	path = std::filesystem::current_path();
	path /= "Textures";
	path /= "MarioWalk.png";
	marioWalk_path = path.string();
}

void FileHandler::setEnemy_Path()
{
	path = std::filesystem::current_path();
	path /= "Textures";
	path /= "Gooba.png";
	gooba_path = path.string();
}

void FileHandler::setCoin_Path()
{
	path = std::filesystem::current_path();
	path /= "Textures";
	path /= "Coin.png";
	coin_path = path.string();
}

FileHandler::FileHandler(sf::Texture& backgroundTex, sf::Sprite& background, std::string& main_map)
{
	initFont();
	initBackground(backgroundTex, background);
	initMap(main_map);
	initPlayer();
	initEnemy();
	initCoin();
}

std::string FileHandler::getBackground_Path()
{
	return background_path;
}

std::string& FileHandler::getMap_Path()
{
	return map_path;
}

std::string& FileHandler::getFont_Path()
{
	return font_path;
}

std::string FileHandler::getMarioIdle_Path()
{
	return marioIdle_path;
}

std::string FileHandler::getMarioWalk_Path()
{
	return marioWalk_path;
}

std::string FileHandler::getEnemy_Path()
{
	return gooba_path;
}

std::string FileHandler::getCoin_Path()
{
	return coin_path;
}

void FileHandler::initBackground(sf::Texture& backgroundTex, sf::Sprite& background)
{
	setBackground_Path();
	if (!backgroundTex.loadFromFile(getBackground_Path()))
	{
		std::cout << "Cannot load background from file!" << std::endl;
		exit(0);
	}
	background.setTexture(backgroundTex);
	
}

void FileHandler::initMap(std::string& cur_map)
{
	setMap_Path(cur_map);
}

void FileHandler::initFont()
{
	setFont_Path();
}

void FileHandler::initPlayer()
{
	setMarioIdle_Path();
	setMarioWalk_Path();
}

void FileHandler::initEnemy()
{
	setEnemy_Path();
}

void FileHandler::initCoin()
{
	setCoin_Path();
}



