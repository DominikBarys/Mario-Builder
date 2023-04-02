#include "UI.h"

void UI::initScoreText(int playerScore)
{
	scoreText.setFont(getFont());
	scoreText.setCharacterSize(30);
	scoreText.setString("Score: " + std::to_string(playerScore));
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(WINDOW_WIDTH - (WINDOW_WIDTH - 10), WINDOW_HEIGHT - (WINDOW_HEIGHT - 10));
}

void UI::initMaterialsText(int playerMaterials)
{
	materialsText.setFont(getFont());
	materialsText.setCharacterSize(30);
	materialsText.setString("Materials: " + std::to_string(playerMaterials));
	materialsText.setFillColor(sf::Color::White);
	materialsText.setPosition(WINDOW_WIDTH - 200, WINDOW_HEIGHT - (WINDOW_HEIGHT - 60));
}

void UI::initAnimScore()
{
	animScore.setFont(getFont());
	animScore.setCharacterSize(20);
}

void UI::initLivesText(int playerLives)
{
	livesText.setFont(getFont());
	livesText.setCharacterSize(30);
	livesText.setString("Lives: " + std::to_string(playerLives));
	livesText.setFillColor(sf::Color::White);
	livesText.setPosition(WINDOW_WIDTH - 120, WINDOW_HEIGHT - (WINDOW_HEIGHT-10));
}

void UI::initInGameTimer()
{
	inGameTimerText.setFont(getFont());
	inGameTimerText.setCharacterSize(30);
	inGameTimerText.setString("Time: " + std::to_string(lengthOfGame));
	inGameTimerText.setFillColor(sf::Color::White);
	inGameTimerText.setPosition(330, WINDOW_HEIGHT - (WINDOW_HEIGHT - 10));
}

void UI::initPauseText()
{
	pauseText.setFont(getFont());
	pauseText.setCharacterSize(70);
	pauseText.setString("Game Paused");
	pauseText.setFillColor({ 0,100,0 });
	pauseText.setPosition(210, 50);
	pauseText.setOutlineThickness(5.f);
	pauseText.setOutlineColor(sf::Color::Black);
}

void UI::initPauseInstructionText()
{
	pauseInstruction.setFont(getFont());
	pauseInstruction.setCharacterSize(40);
	pauseInstruction.setString(" Press \"spacebar\" to continue\n\nPress \"enter\" to quit the game");
	pauseInstruction.setFillColor({ 0,100,0 });
	pauseInstruction.setPosition(120, 220);
	pauseInstruction.setOutlineThickness(4.f);
	pauseInstruction.setOutlineColor(sf::Color::Black);
}

const unsigned int UI::getWindowWidth()
{
	return WINDOW_WIDTH;
}

const unsigned int UI::getWindowHeight()
{
	return WINDOW_HEIGHT;
}

int UI::getLengthOfGame()
{
	return lengthOfGame;
}

sf::Font& UI::getFont()
{
	return font;
}

void UI::setFont(std::string& path)
{
	if (!font.loadFromFile(path))
	{
		std::cout << "Cannot load font file!" << std::endl;
		exit(0);
	}
}

void UI::initUI(int playerLives, int playerScore, int playerMaterials)
{
	initScoreText(playerScore);
	initMaterialsText(playerMaterials);
	initLivesText(playerLives);
	initAnimScore();
	initInGameTimer();
	initPauseText();
	initPauseInstructionText();
	
}

void UI::updateUI(int playerMaterials, int playerLives, int playerScore, int lengthOfGame)
{
	materialsText.setString("Materials: " + std::to_string(playerMaterials));
	livesText.setString("Lives: " + std::to_string(playerLives));
	scoreText.setString("Score: " + std::to_string(playerScore));
	inGameTimerText.setString("Time: " + std::to_string(lengthOfGame));
}

void UI::drawUI(sf::RenderWindow& window)
{
	window.draw(livesText);
	window.draw(materialsText);
	window.draw(scoreText);
	window.draw(inGameTimerText);

}

void UI::drawPauseUI(sf::RenderWindow& window)
{

	window.draw(pauseText);
	window.draw(pauseInstruction);
}

void UI::setTmp()
{
	tmp = 0;
}

float& UI::getTmp()
{
	return tmp;
}

sf::Uint8& UI::getTransparency()
{
	return transparency;
}

void UI::setTransparency()
{
	transparency = 255;
}

sf::Clock& UI::getAnimScoreTimer()
{
	return animScoreTimer;
}

void UI::animationOfScorePoints(sf::RenderWindow& window, bool& hitScore, int& lastScore, float& playerSize, sf::Sprite& player)
{
	if (hitScore)
	{
		tmp++;
		transparency -= 3;
		animScore.setCharacterSize(20);
		animScore.setString(std::to_string(lastScore));
		animScore.setPosition({ player.getPosition().x - 40, player.getPosition().y + playerSize / 2 - tmp });
		animScore.setFillColor({ 255,255,255, transparency});
		window.draw(animScore);

		if (animScoreTimer.getElapsedTime().asSeconds() >= 1)
		{
			animScore.setCharacterSize(0);
			transparency = 255;
			tmp = 0;
			hitScore = false;
		}
	}
}

