#include "Player.h"

float& Player::getPlayerSize()
{
    return playerSize;
}

int& Player::getLastScore()
{
    return lastScore;
}

bool& Player::getHitScore()
{
    return hitScore;
}

int Player::getPlayerLives()
{
	return lives;
}

int& Player::getPlayerMaterials()
{
	return materials;
}

int Player::getPlayerScore()
{
	return playerScore;
}

sf::Sprite& Player::getPlayerSprite()
{
	return playerSprite;
}

void Player::setMarioStaying(std::string path)
{
	if (!marioStaying.loadFromFile(path))
	{
		std::cout << "Cannot load mario staying file!" << std::endl;
		exit(0);
	}
}

void Player::setMarioWalking(std::string path)
{
	if (!marioWalking.loadFromFile(path))
	{
		std::cout << "Cannot load mario walking file!" << std::endl;
		exit(0);
	}
}

int Player::getPlayerIntRectPos()
{
	return playerIntRectPos;
}

void Player::updatePlayerAnim()
{
	playerSprite.setTexture(marioStaying);
	playerSprite.setTextureRect(sf::IntRect(playerIntRectPos, 0, 16, 16));

}

void Player::updatePlayerMovement(sf::Vector2f& velocity)
{
    velocity.x = 0.f;
    velocity.y = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && inAir == 0
        && hitTheGround && jumpingState != IN_AIR)
    {
        hitTheGround = false;
        inAir = 30;
        jumpingClock.restart();
    }
    if (inAir <= 30 && inAir > 0)
    {
        velocity.y -= movementSpeed;
        if (inAir > 0)
            inAir--;
    }
    else if (inAir == 0)
    {
        velocity.y += gravity;
        jumpingState = IN_AIR;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        //std::cout << "A" << std::endl;
        velocity.x -= movementSpeed;
        animationState = MOVING_LEFT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        //std::cout << "D" << std::endl;
        velocity.x += movementSpeed;
        animationState = MOVING_RIGHT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        inAir = 0;
        velocity.y += movementSpeed / 2;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)
        && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (animationState == MOVING_LEFT)
        {
            animationState = STAYING_LEFT;
        }
        else if (animationState == MOVING_RIGHT)
        {
            animationState = STAYING_RIGHT;
        }
    }
    
    if (playerSprite.getPosition().x <= 0)
    {
        playerSprite.setPosition(0, playerSprite.getPosition().y);
    }
    if (playerSprite.getPosition().x + playerSize >= WINDOW_WIDTH)
    {
        playerSprite.setPosition(WINDOW_WIDTH - playerSize, playerSprite.getPosition().y);
    }
    if (playerSprite.getPosition().y <= 0)
    {
        playerSprite.setPosition(playerSprite.getPosition().x, 0);
        inAir = 0;
    }
    if (playerSprite.getPosition().y + playerSize >= WINDOW_HEIGHT)
    {
        hitTheGround = true;
        jumpingState = IDLE;
        playerSprite.setPosition(playerSprite.getPosition().x, WINDOW_HEIGHT - playerSize);
    }

}

void Player::setPlayer(int x, int y)
{
	playerSprite.setPosition(x, y);
	playerSprite.setScale(3.f, 3.f);
	updatePlayerAnim();
}

sf::Vector2f& Player::getPlayerVelocity()
{
    return velocity;
}

void Player::playerCollisionWithWalls(sf::Vector2f& velocity, std::vector<sf::RectangleShape> walls)
{
    sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
    sf::FloatRect nextPos;

    for (auto& wall : walls)
    {
        sf::FloatRect wallBounds = wall.getGlobalBounds();

        nextPos = playerBounds;
        nextPos.left += velocity.x;
        nextPos.top += velocity.y;

        if (wallBounds.intersects(nextPos))
        {
            //Bottom collision
            if (playerBounds.top < wallBounds.top
                && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
                && playerBounds.left < wallBounds.left + wallBounds.width
                && playerBounds.left + playerBounds.width > wallBounds.left)
            {
                velocity.y = 0.f;
                playerSprite.setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
                hitTheGround = true;
                jumpingState = IDLE;
            }

            //Top collision
            if (playerBounds.top > wallBounds.top
                && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
                && playerBounds.left < wallBounds.left + wallBounds.width
                && playerBounds.left + playerBounds.width > wallBounds.left)
            {
                velocity.y = 0.f;
                playerSprite.setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
                inAir = 0;
            }

            //Right collision
            if (playerBounds.left < wallBounds.left
                && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
                && playerBounds.top < wallBounds.top + wallBounds.height
                && playerBounds.top + playerBounds.height > wallBounds.top)
            {
                velocity.x = 0.f;
                playerSprite.setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
            }

            //Left collision
            if (playerBounds.left > wallBounds.left
                && playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
                && playerBounds.top < wallBounds.top + wallBounds.height
                && playerBounds.top + playerBounds.height > wallBounds.top)
            {
                velocity.x = 0.f;
                playerSprite.setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
            }
        }
    }
}

void Player::playerCollisionWithEnemy(sf::Sprite& enemy, int& enemyScorePoints, float& tmp, sf::Uint8& transparency, sf::Clock& animScoreTimer,
                                        bool& enemydestroyed, sf::Clock& spawnTimer)
{
    sf::FloatRect enemyBounds = enemy.getGlobalBounds();

    //Killing enemy
    if (playerSprite.getGlobalBounds().intersects(enemyBounds)) // if (playerBounds.intersects(enemyBounds))
    {
        if (playerSprite.getGlobalBounds().top < enemyBounds.top
            && playerSprite.getGlobalBounds().top + playerSprite.getGlobalBounds().height < enemyBounds.top + enemyBounds.height
            && playerSprite.getGlobalBounds().left < enemyBounds.left + enemyBounds.width
            && playerSprite.getGlobalBounds().left + playerSprite.getGlobalBounds().width > enemyBounds.left)
        {
            //Bunch of actions and variables to properly show and animate player score UI
            playerScore += enemyScorePoints; 
            //scoreText.setString("Score: " + std::to_string(playerScore)); // Po wykonaniu tej metody zaktualizuj wyswietlanie player score
            hitScore = true;
            tmp = 0; 
            transparency = 255; 
            animScoreTimer.restart(); 
            lastScore = enemyScorePoints;
            enemydestroyed = true; 
            spawnTimer.restart(); 
        }
        else
        {
            playerSprite.setPosition({ 400.f,0.f });
            lives--;
            //livesText.setString("Lives : " + std::to_string(lives)); // Tez zaktualizuj wyswietlanie zyc
        }
    }
}

void Player::playerCollisionWithCoin(sf::Sprite& coinSprite, int coinScorePoints, float& tmp, sf::Uint8& transparency, sf::Clock& animScoreTimer,
                                        bool& isCollected, sf::Clock& coinSpawnTimer)
{
    if (playerSprite.getGlobalBounds().intersects(coinSprite.getGlobalBounds()))
    {
        std::cout << "INTERSECT WITH COIN" << std::endl;
        playerScore += coinScorePoints;
        //zaktualizuj ui wyswietlajace score
        hitScore = true;
        tmp = 0;
        std::cout << "PLAYER SCORE:" << playerScore << std::endl;
        transparency = 255;
        animScoreTimer.restart();
        coinSpawnTimer.restart();
        lastScore = coinScorePoints;
        isCollected = true;
        coinSprite.setScale(0.f, 0.f);
    }
}

void Player::updatePlayerAnimation()
{
    if (animationState == STAYING_RIGHT)
    {
        playerSprite.setTexture(marioStaying);
        playerSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));

    }
    else if (animationState == STAYING_LEFT)
    {
        playerSprite.setTexture(marioStaying);
        playerSprite.setTextureRect(sf::IntRect(16, 0, 16, 16));
    }
    else if (animationState == MOVING_RIGHT && playerAnimTimer.getElapsedTime().asSeconds() >= 0.1f)
    {
        playerSprite.setTexture(marioWalking);
        if (walking_var == 0)
        {
            playerSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
            walking_var = 1;
            playerAnimTimer.restart();
        }
        else if (walking_var == 1)
        {
            playerSprite.setTextureRect(sf::IntRect(16, 0, 16, 16));
            walking_var = 2;
            playerAnimTimer.restart();
        }
        else if (walking_var == 2)
        {
            playerSprite.setTextureRect(sf::IntRect(32, 0, 16, 16));
            walking_var = 0;
            playerAnimTimer.restart();
        }
    }
    else if (animationState == MOVING_LEFT && playerAnimTimer.getElapsedTime().asSeconds() >= 0.1f)
    {
        playerSprite.setTexture(marioWalking);
        if (walking_var == 0)
        {
            playerSprite.setTextureRect(sf::IntRect(48, 0, 16, 16));
            walking_var = 1;
            playerAnimTimer.restart();
        }
        else if (walking_var == 1)
        {
            playerSprite.setTextureRect(sf::IntRect(64, 0, 16, 16));
            walking_var = 2;
            playerAnimTimer.restart();
        }
        else if (walking_var == 2)
        {
            playerSprite.setTextureRect(sf::IntRect(80, 0, 16, 16));
            walking_var = 0;
            playerAnimTimer.restart();
        }
    }
}

void Player::updatePlayer(Player& player, std::vector<sf::RectangleShape> walls, Coin& coin, UI& ui)
{
    player.updatePlayerMovement(player.getPlayerVelocity());
    player.playerCollisionWithWalls(player.getPlayerVelocity(),walls);
    player.playerCollisionWithCoin(coin.getCoinSprite(), coin.getCoinScorePoints(), ui.getTmp(), ui.getTransparency(),
        ui.getAnimScoreTimer(), coin.getIsCollected(), coin.getCoinSpawnTimer());
    player.getPlayerSprite().move(player.getPlayerVelocity());
    player.updatePlayerAnimation();
}
