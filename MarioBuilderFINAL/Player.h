#pragma once

#include "Enemy.h"
#include "Coin.h"
#include "UI.h"

enum Jumping_Tools { IDLE = 0, IN_AIR };

enum PlayerStates { STAYING_RIGHT = 0, STAYING_LEFT, MOVING_RIGHT, MOVING_LEFT};

class Player
{
private:

	const unsigned int WINDOW_WIDTH = 800;
	const unsigned int WINDOW_HEIGHT = 600;

	sf::Vector2f velocity;
	sf::Sprite playerSprite;
	
	sf::Clock playerAnimTimer;
	int walking_var = 0;
	
	const float movementSpeed = 7.f;
	const float gravity = 7.f;
	int lives = 3;
	int playerScore = 0;
	int materials = 30;
	bool hitScore = false;
	int lastScore = 0;
	short int animationState = 0;
	short int jumpingState = IDLE;
	float playerSize = 40.f;

	int playerIntRectPos = 0;

	sf::Clock jumpingClock;
	short int inAir = 0;
	bool hitTheGround = false;
	sf::Texture marioStaying;
	sf::Texture marioWalking;

public:

	float& getPlayerSize();
	int& getLastScore();
	bool& getHitScore();
	int getPlayerLives();
	int& getPlayerMaterials();
	int getPlayerScore();
	sf::Sprite& getPlayerSprite();
	void setMarioStaying(std::string);
	void setMarioWalking(std::string);
	int getPlayerIntRectPos();
	void updatePlayerAnim();
	void updatePlayerMovement(sf::Vector2f& velocity);
	void setPlayer(int x, int y);
	sf::Vector2f& getPlayerVelocity();

	void playerCollisionWithWalls(sf::Vector2f& velocity/*nwm czy to jest potrzebne*/, std::vector<sf::RectangleShape>);

	void playerCollisionWithEnemy(sf::Sprite& enemy, int& enemyScorePoints, float& tmp, sf::Uint8& transparency, sf::Clock& animScoreTimer,
		bool& enemydestroyed, sf::Clock& spawnTimer);

	void playerCollisionWithCoin(sf::Sprite& coinSprite, int coinScorePoints, float& tmp, sf::Uint8& transparency, sf::Clock& animScoreTimer, 
		bool& isCollected, sf::Clock& coinSpawnTimer);

	void updatePlayerAnimation();

	static void updatePlayer(Player& player, std::vector<sf::RectangleShape> walls, Coin& coin, UI& ui);
};

