#pragma once

#include <string>

#include "FileHandler.h"
class Player;

class UI
{
private:

    sf::Font font;
    sf::Text livesText;
    sf::Text scoreText;
    sf::Text materialsText;
    sf::Text pauseText;
    sf::Text pauseInstruction;
   
    sf::Text inGameTimerText;

    sf::Uint8 transparency = 255;
    float tmp = 0;
    sf::Clock animScoreTimer;

    int lengthOfGame = 60;

    void initScoreText(int playerScore);
    void initMaterialsText(int playerMaterials);
    void initAnimScore();
    void initLivesText(int playerLives);
    void initInGameTimer();
    void initPauseText();
    void initPauseInstructionText();

    

public:

    const unsigned int WINDOW_WIDTH = 800;
    const unsigned int WINDOW_HEIGHT = 600;

    const unsigned int getWindowWidth();
    const unsigned int getWindowHeight();

    sf::Text animScore;
    int getLengthOfGame();

    sf::Font& getFont();

    void setFont(std::string& path);

    void initUI(int playerLives, int playerScore, int playerMaterials);

    void updateUI(int playerMaterials, int playerLives, int playerScore, int lengthOfGame);

    void drawUI(sf::RenderWindow& window);

    void drawPauseUI(sf::RenderWindow& window);

    void setTmp();

    float& getTmp();

    sf::Uint8& getTransparency();

    void setTransparency();

    sf::Clock& getAnimScoreTimer();

    void animationOfScorePoints(sf::RenderWindow& window, bool& hitScore, int& lastScore, float& playerSize, sf::Sprite& player);
};