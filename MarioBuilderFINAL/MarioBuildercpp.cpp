#include "Enemy.h"
#include "Coin.h"
#include "Enemy.h"
#include "Player.h"


int main()
{
    //Statr randomizing values to random coin spawn
    srand(time(NULL));

    //Game variables
    int lengthOfGame = 60;
    sf::Clock inGameTimer;
    sf::Texture backgroundTex;
    sf::Sprite background;
    std::string mainMap = "Main_Map.txt";
    FileHandler fileHandler(backgroundTex, background, mainMap);

    //Init font
    UI ui;                
    ui.setFont(fileHandler.getFont_Path());

    //Window
    sf::RenderWindow window(sf::VideoMode(ui.getWindowWidth(), ui.getWindowHeight()), "MARIO BUILDER!");
    window.setFramerateLimit(60);

    //Map init
    MapManager mapManager; 
    mapManager.initMap(fileHandler.getMap_Path());
   
    //Init player
    Player player;       
    player.setMarioStaying(fileHandler.getMarioIdle_Path());
    player.setMarioWalking(fileHandler.getMarioWalk_Path());
    player.setPlayer(300,400);

    //Init enemies
    Enemy enemy1;        
    enemy1.setEnemyTexture(fileHandler.getEnemy_Path());
    enemy1.setEnemy(130, 70);

    Enemy enemy2;
    enemy2.setEnemyTexture(fileHandler.getEnemy_Path());
    enemy2.setEnemy(400, 80);

    Enemy enemy3;
    enemy3.setEnemyTexture(fileHandler.getEnemy_Path());
    enemy3.setEnemy(550, 100);
    
    //Init coin
    Coin coin;
    coin.setCoinTexture(fileHandler.getCoin_Path());
    coin.setCoin();

    //Init ui
    ui.initUI(player.getPlayerLives(), player.getPlayerScore(), player.getPlayerMaterials());

    //Game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        //Adding and removing walls
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            mapManager.addWalls(window, player.getPlayerMaterials());
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            mapManager.removeWalls(window, player.getPlayerMaterials());

        //Basic map and background draw
        window.clear();
        window.draw(background);
        mapManager.draw(window);

         //Functions responsible for player behavior
         Player::updatePlayer(player, mapManager.walls, coin, ui);

         window.draw(player.getPlayerSprite());

         //All enemies collision, animation, destroying and spawn functions
             //Enemy1 update
             Enemy::enemyUpdate(enemy1, mapManager.walls);
             window.draw(enemy1.getEnemySprite());
             player.playerCollisionWithEnemy(enemy1.getEnemySprite(), enemy1.getEnemyScorePoints(), ui.getTmp(),
                 ui.getTransparency(), ui.getAnimScoreTimer(), enemy1.getEnemyDestroyed(), enemy1.getEnemySpawnTimer());
             if (enemy1.getEnemyDestroyed())
             {
                 enemy1.getEnemySprite().setScale(0.f, 0.f);
             }
             //Enemy2 update
             Enemy::enemyUpdate(enemy2, mapManager.walls);
             window.draw(enemy2.getEnemySprite());
             player.playerCollisionWithEnemy(enemy2.getEnemySprite(), enemy2.getEnemyScorePoints(), ui.getTmp(),
                 ui.getTransparency(), ui.getAnimScoreTimer(), enemy2.getEnemyDestroyed(), enemy2.getEnemySpawnTimer());
             if (enemy2.getEnemyDestroyed())
             {
                 enemy2.getEnemySprite().setScale(0.f, 0.f);
             }
             //Enemy3 update
             Enemy::enemyUpdate(enemy3, mapManager.walls);
             window.draw(enemy3.getEnemySprite());
             player.playerCollisionWithEnemy(enemy3.getEnemySprite(), enemy3.getEnemyScorePoints(), ui.getTmp(),
                 ui.getTransparency(), ui.getAnimScoreTimer(), enemy3.getEnemyDestroyed(), enemy3.getEnemySpawnTimer());
             if (enemy3.getEnemyDestroyed())
             {
                 enemy3.getEnemySprite().setScale(0.f, 0.f);
             }
             //Spawn of enemies in order 1, 2 then 3 
             if (enemy1.getEnemyDestroyed() && enemy1.getEnemySpawnTimer().getElapsedTime().asSeconds() >= 2.f)
             {
                 std::cout << "enemy 1" << std::endl;
                 Enemy::enemySpawn(enemy1);
             }
             else if (enemy2.getEnemyDestroyed() && enemy2.getEnemySpawnTimer().getElapsedTime().asSeconds() >= 2.f &&
                 enemy1.getEnemySpawnTimer().getElapsedTime().asSeconds() >= 2.f)
             {
                 std::cout << "enemy 2" << std::endl;
                 Enemy::enemySpawn(enemy2);
             }
             else if (enemy3.getEnemyDestroyed() && enemy3.getEnemySpawnTimer().getElapsedTime().asSeconds() >= 2.f &&
                 enemy1.getEnemySpawnTimer().getElapsedTime().asSeconds() >= 2.f && enemy2.getEnemySpawnTimer().getElapsedTime().asSeconds() >= 2.f)
             {
                 std::cout << "enemy 3" << std::endl;
                 Enemy::enemySpawn(enemy3);
             }
         
        //Spawn and animate coin
        coin.spawnCoin();
        coin.updateCoinAnim();
        window.draw(coin.getCoinSprite());

        //Animated text when player hit score
        ui.animationOfScorePoints(window, player.getHitScore(), player.getLastScore(), player.getPlayerSize(), player.getPlayerSprite());
        window.draw(ui.animScore);

        //Timer that decrements in game time 
        if (inGameTimer.getElapsedTime().asSeconds() > 1 && inGameTimer.getElapsedTime().asSeconds() <= 1.05)
        {
            lengthOfGame--;
            inGameTimer.restart();
        }

        //Conditions to end the game 
        if (lengthOfGame == 0 || player.getPlayerLives() == 0)
        {
            exit(0);
        }

        //Pause screen
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                inGameTimer.restart();
                window.draw(background);
                ui.drawPauseUI(window);
                window.display();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                {
                    exit(0);
                }
            }
        }

        //Updating ui
        ui.updateUI(player.getPlayerMaterials(), player.getPlayerLives(), player.getPlayerScore(), lengthOfGame);
        ui.drawUI(window);

        window.display();
    }

    return 0;
}