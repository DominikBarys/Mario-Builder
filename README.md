# Mario Builder

## Description
Project inspired by the platrofm game "Mario". It is a simple implementation of the game with the addition of mechanics of interfering with the environment by the player by building and destroying blocks. The game was written in C++ language using the SFML graphics library.
##

## Game rules

### Main goal

The goal of the game is to score as many points as possible in 60 seconds, the user can earn points in 2 ways: one of them is to collide with the opponent from his upper edge, then the same as in the original "Mario", the opponent is destroyed and the player scores 500 points, the second way is to collect coins that appear in pseudo-random places on the screen and each of them gives 300 points, the coin after collecting will appear after 2 seconds in another pseudo-random place. When the player collides with an opponent from his left, right or bottom edge, then the player loses one life and reappears, after losing three lives the game is over.

### After starting the program, the user is shown a window with the game:

![App Screenshot](https://github.com/DominikBarys/Mario-Builder/blob/main/Screenshots/Screenshot1.png?raw=true)

* Blue color - The character "Mario" that the player controls.
* Purple color - Coin that a player can collect to earn points.
* Orange color - An example of an element of the environment with which the player collides. These brown blocks can also be placed and destroyed by the player.
* Green color - One of the three opponents in the game, a collision with it results in the loss of one life, while a collision with it from the side of its upper edge removes it and grants the player the appropriate amount of points.
* Red color - User interface during the game that informs him about such things as: the number of points, time left in the game, the number of lives or the amount of current materials.

### Movement and animations:

The player has the ability to move left with the "A" button, move right with the "D" button, jump by pressing "W", and fall faster by pressing "S" while in the air. The player is constantly affected by gravity, which pushes him down the screen until he collides with a block or the edge of the screen. Depending on what the player does, an appropriate animation is triggered for him.

![App Screenshot](https://github.com/DominikBarys/Mario-Builder/blob/main/Screenshots/Screenshot2.png?raw=true)

### Interaction with environment

An element that also distinguishes the "Mario Builder" project from the original is the ability to edit the map during the game. The player starts with 30 materials and after pressing the left mouse button, a new block appears on the screen in the place of the cursor and the amount of the player's materials is reduced by one. Similarly, if we press the right mouse button on an already existing block on the map, it will disappear and the player will be granted one resource of materials.

An example of a map fragment after editing with the mouse:

![App Screenshot](https://github.com/DominikBarys/Mario-Builder/blob/main/Screenshots/Screenshot3.png?raw=true)

### Pause screen

You can stop the game at any time by pressing the "Escape" button. In this case, the game will keep all its states and when the player is ready to continue, press "Space" or exit the game using the "Enter" key

![App Screenshot](https://github.com/DominikBarys/Mario-Builder/blob/main/Screenshots/Screenshot4.png?raw=true)

### Additional features

The map in the project is saved as a .txt file which the program downloads and after data processing is ready to generate blocks in the appropriate places. In the file, the '.' sign means that the block is missing, while the '#' sign means that the block exists in this place on the map. The user can freely edit the map, if any syntax error occurs, the program will inform him about it.

![App Screenshot](https://github.com/DominikBarys/Mario-Builder/blob/main/Screenshots/Screenshot5.png?raw=true)

##

## How to run a game

There are two ways to run a game:

* Run the MarioBuilderFINAL.exe file located in the "Mario Executable" folder
* Go to the "MarioBuilderFINAL" folder and compile the project with g++. Example:

```
g++ *.cpp -std=c++20 -lsfml-graphics -lsfml-window -lsfml-system -o WorkingGame!
```
