#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <filesystem>
#include <string>

#include "UI.h"


class FileHandler
{
private:

    std::filesystem::path path;
    std::string background_path;
    std::string map_path;
    std::string font_path;
    std::string marioIdle_path;
    std::string marioWalk_path;
    std::string gooba_path;
    std::string coin_path;
    
    void setBackground_Path();
    void setMap_Path(std::string& cur_map);
    void setFont_Path();
    void setMarioIdle_Path();
    void setMarioWalk_Path();
    void setEnemy_Path();
    void setCoin_Path();

public:

    FileHandler(sf::Texture& backgroundTex, sf::Sprite& background, std::string& main_map);

    std::string getBackground_Path();
    std::string& getMap_Path();
    std::string& getFont_Path();
    std::string getMarioIdle_Path();
    std::string getMarioWalk_Path();
    std::string getEnemy_Path();
    std::string getCoin_Path();
    void initBackground(sf::Texture& backgroundTex,  sf::Sprite& background);
    void initMap(std::string& cur_map);
    void initFont();
    void initPlayer();
    void initEnemy();
    void initCoin();
    
};

