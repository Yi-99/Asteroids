/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"
using namespace std;

#define OFF_SCREEN_BORDER_AMOUNT 5

// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/

float Game :: getClosestDistance(FlyingObject &obj1, FlyingObject &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}



/***************************************
* GAME CONSTRUCTOR
***************************************/
Game::Game(Point tl, Point br)
	: topLeft(tl), bottomRight(br), ship()
{
	// Set up the initial conditions of the game
	score = 0;
	newGame = false;
}

/****************************************
* GAME DESTRUCTOR
****************************************/
Game :: ~Game()
{
}

/***************************************
* GAME :: ADVANCE
* advance the game one unit of time
***************************************/
void Game::advance()
{
	if (ship.isAlive() && ship.getLives() != 0)
	{
		ship.setAlive(true);
		advanceBullets();
		advanceRocks();
		ship.advance();
	}
	else if (!ship.isAlive() && ship.getLives() != 0)
	{
		newGame = true;
		ship.loseLife();
		Point p(-100,0);
		drawText(p, "You've Been Hit! Press down to continue");
	}
	else
	{
		newGame = true;
		Point p(-100, 100);
		drawText(p, "No More Lives!");

	}
	handleCollisions();
	cleanUpZombies();
}

/***************************************
* GAME :: ADVANCE BULLETS
* Go through each bullet and advance it.
***************************************/
void Game::advanceBullets()
{
	// Move each of the bullets forward if it is alive
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			// this bullet is alive, so tell it to move forward
			bullets[i].advance();

			if (!isOnScreen(bullets[i].getPoint()))
			{
				// the bullet has left the screen
				int x = bullets[i].getPoint().getX();
				int y = bullets[i].getPoint().getY();
				if (x > 200)
				{
					x = 0;
				}
				if (y > 200)
				{
					y = 0;
				}
				else if (y < 0)
				{
					y = 200;
				}
				Point point(x, y);
				bullets[i].setPoint(point);
			}

		}
	}
}

/**************************************************************************
* GAME :: ADVANCE Rock
*
* 1. If there is no rocks, create one with some probability
* 2. If there is a rocks, and it's alive, advance it
* 3. Check if the rocks has gone of the screen, and if so, "kill" it
**************************************************************************/
void Game::advanceRocks()
{


	if (rocks.size() == 0)
	{
		while (rocks.size() < 5)
		{
			rocks.push_back(new BigRock());
		}
	}
	for (int i = 0; i < rocks.size(); i++)
	{
		if (rocks[i]->isAlive())
		{
			// this bullet is alive, so tell it to move forward
			rocks[i]->advance();
		}
	}
}

/**************************************************************************
* GAME :: CREATE Rock
* Create a rocks of a random type according to the rules of the game.
**************************************************************************/
Rock* Game::createRock()
{
	Rock* newRock = NULL;

	// TODO: Fill this in
	int choice = random(0, 3);
	switch (choice)
	{
		case 0:
			newRock = new BigRock();
			break;
		case 1:
			newRock = new MediumRock();
			break;
		case 2:
			newRock = new SmallRock();
			break;
		default:
			break;
	}
	return newRock;
}

/**************************************************************************
* GAME :: IS ON SCREEN
* Determines if a given point is on the screen.
**************************************************************************/
bool Game::isOnScreen(const Point & point)
{
	return (point.getX() >= topLeft.getX()
		&& point.getX() <= bottomRight.getX()
		&& point.getY() >= bottomRight.getY()
		&& point.getY() <= topLeft.getY());
}

/**************************************************************************
* GAME :: HANDLE COLLISIONS
* Check for a collision between a rocks and a bullet.
**************************************************************************/
void Game::handleCollisions()
{
	// now check for a hit (if it is close enough to any live bullets)
	for (int i = 0; i < bullets.size(); i++)
	{
		for (int j = 0; j < rocks.size(); j++)
		{
			if (bullets[i].isAlive())
			{
				// BTW, this logic could be more sophisiticated, but this will
				// get the job done for now...
				if (fabs(bullets[i].getPoint().getX() - rocks[j]->getPoint().getX()) < rocks[j]->getSize()
					&& fabs(bullets[i].getPoint().getY() - rocks[j]->getPoint().getY()) < rocks[j]->getSize())
				{
					//we have a hit!
					// hit the rocks
					int points = rocks[j]->hit();
					score += points;
					// the bullet is dead as well
					bullets[i].kill();

					switch (points)
					{
					case 2:
						rocks.push_back(new SmallRock(rocks[j]->getPoint()));
						rocks.push_back(new SmallRock(rocks[j]->getPoint()));
						break;
					case 3:
						rocks.push_back(new MediumRock(rocks[j]->getPoint()));
						rocks.push_back(new MediumRock(rocks[j]->getPoint()));
						rocks.push_back(new SmallRock(rocks[j]->getPoint()));
						break;
					default:
						break;
					}
				}
			}
		}
	} // for bullets

	for (int j = 0; j < rocks.size(); j++)
	{
		// BTW, this logic could be more sophisiticated, but this will
		// get the job done for now...
		if (fabs(ship.getPoint().getX() - rocks[j]->getPoint().getX()) < rocks[j]->getSize()
			&& fabs(ship.getPoint().getY() - rocks[j]->getPoint().getY()) < rocks[j]->getSize() && ship.isAlive())
		{
			//we have a hit!
			int points = rocks[j]->hit();
			score += points;
			// the ship is dead
			ship.kill();
		}
	}
}

/**************************************************************************
* GAME :: CLEAN UP ZOMBIES
* Remove any dead objects (take bullets out of the list, deallocate rocks)
**************************************************************************/
void Game::cleanUpZombies()
{
	// check for dead rocks
	vector<Rock *>::iterator rockIT = rocks.begin();
	while (rockIT != rocks.end())
	{
		// Asteroids Hint:
		// If we had a list of pointers, we would need this line instead:
		//Bullet* pBullet = *bulletIt;

		if (!(*rockIT)->isAlive())
		{
			// If we had a list of pointers, we would need to delete the memory here...


			// remove from list and advance
			rockIT = rocks.erase(rockIT);
		}
		else
		{
			rockIT++; // advance
		}
	}

	// Look for dead bullets
	vector<Bullet>::iterator bulletIt = bullets.begin();
	while (bulletIt != bullets.end())
	{
		Bullet bullet = *bulletIt;
		// Asteroids Hint:
		// If we had a list of pointers, we would need this line instead:
		//Bullet* pBullet = *bulletIt;

		if (!bullet.isAlive())
		{
			// If we had a list of pointers, we would need to delete the memory here...


			// remove from list and advance
			bulletIt = bullets.erase(bulletIt);
		}
		else
		{
			bulletIt++; // advance
		}
	}

}

void Game::displayHighScores()
{
}

/***************************************
* GAME :: HANDLE INPUT
* accept input from the user
***************************************/
void Game::handleInput(const Interface & ui)
{
	// Change the direction of the rifle
	if (ui.isLeft())
	{
		ship.moveLeft();
	}

	if (ui.isRight())
	{
		ship.moveRight();
	}

	if (ui.isUp())
	{
		ship.applyThrust();

	}

	if (ui.isDown() && newGame)
	{
		ship.setAlive(true);
		newGame = false;
	}

	// Check for "Spacebar
	if (ui.isSpace())
	{
		Bullet newBullet;
		newBullet.fire(ship.getPoint(), ship.getAngle(), ship.getVelocity());

		bullets.push_back(newBullet);
	}
}

/*********************************************
* GAME :: DRAW
* Draw everything on the screen
*********************************************/
void Game::draw(const Interface & ui)
{
	for (int i = 0; i < rocks.size(); i++)
	{
		if (rocks[i]->isAlive())
		{
			rocks[i]->draw();
		}
	}

	// draw the ship
	if (ship.isAlive())
		ship.draw();

	// draw the bullets, if they are alive
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			bullets[i].draw();
		}
	}
	

	// Put the score on the screen
	Point scoreLocation;
	scoreLocation.setX(topLeft.getX() + 5);
	scoreLocation.setY(topLeft.getY() - 5);

	drawNumber(scoreLocation, score);

}