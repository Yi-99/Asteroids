/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include <vector>

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "velocity.h"
#include "flyingObject.h"
#include "ship.h"
#include "bullet.h"
#include "rocks.h"
#include <limits>
#include <algorithm>
#include <cmath>


#define CLOSE_ENOUGH 15
#define MAX_ASTEROID_AMOUNT 3


 /*****************************************
 * GAME
 * The main game class containing all the state
 *****************************************/
class Game
{
public:
	/*********************************************
	* Constructor
	* Initializes the game
	*********************************************/
	Game(Point tl, Point br);
	~Game();

	/*********************************************
	* Function: handleInput
	* Description: Takes actions according to whatever
	*  keys the user has pressed.
	*********************************************/
	void handleInput(const Interface & ui);

	/*********************************************
	* Function: advance
	* Description: Move everything forward one
	*  step in time.
	*********************************************/
	void advance();

	/*********************************************
	* Function: draw
	* Description: draws everything for the game.
	*********************************************/
	void draw(const Interface & ui);

private:
	// The coordinates of the screen
	Point topLeft;
	Point bottomRight;

	int score;
	bool newGame;

	Ship ship;
	std::vector<Bullet> bullets;
	std::vector<Rock *> rocks;

	/*************************************************
	* Private methods to help with the game logic.
	*************************************************/
	bool isOnScreen(const Point & point);
	void advanceBullets();
	void advanceRocks();
	Rock* createRock();
	float getClosestDistance(FlyingObject &obj1, FlyingObject &obj2) const;

	void handleCollisions();
	void cleanUpZombies();
	void displayHighScores();
};


#endif /* GAME_H */
