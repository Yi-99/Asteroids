#include "rocks.h"

/*CHANGE POINT
*	Input:
*		v: velocity to change point by
*************************************************************************************/
void Rock::changePoint(Velocity v)
{
	point.setX(point.getX() + v.getDx());
	point.setY(point.getY() + v.getDy());
}


/*ADVANCE
*   has the lander advance in the game loop
*************************************************************************************/
void Rock::advance()
{
	if (point.getX() > 200.0 || point.getX() < -200.0)
		point.setX(point.getX() *-1);
	if (point.getY() > 200.0 || point.getY() < -200.0)
		point.setY(point.getY() * -1);
	changePoint(velocity);
}

/*DRAW
*   draws the bird onto the screen
*************************************************************************************/

BigRock::BigRock()
{
	point.setY(random(-199, 199));
	int rand = random(0, 1);
	if (rand)
		point.setX(200);
	else
		point.setX(-200);
	alive = true;
	lives = 3;
	if (point.getY() < 0)
	{
		velocity.setDx(random(2, 4));
		velocity.setDy(3);
	}
	else
	{
		velocity.setDx(random(2, 4));
		velocity.setDy(-1);
	}
}

BigRock::BigRock(Point p)
{
	point.setY(p.getY());
	point.setX(p.getX());
	alive = true;
	velocity.setDx(random(1, 6));
	velocity.setDy(random(1, 6));
}

void BigRock::draw()
{
	angle += BIG_ROCK_SPIN;
	drawLargeAsteroid(point, angle);
}

MediumRock::MediumRock()
{
	point.setY(random(-199, 199));
	int rand = random(0, 1);
	if (rand)
		point.setX(200);
	else
		point.setX(-200);
	alive = true;
	if (point.getY() < 0)
	{
		velocity.setDx(random(3, 6));
		velocity.setDy(3);
	}
	else
	{
		velocity.setDx(random(3, 6));
		velocity.setDy(-1);
	}
}

MediumRock::MediumRock(Point p)
{
	point.setY(p.getY());
	point.setX(p.getX());
	alive = true;
	velocity.setDx(random(1, 6));
	velocity.setDy(random(1, 6));
}

void MediumRock::draw()
{
	angle += MEDIUM_ROCK_SPIN;
	drawMediumAsteroid(point, angle);
}

SmallRock::SmallRock()
{
	point.setY(random(-199, 199));
	int rand = random(0, 1);
	if (rand)
		point.setX(200);
	else
		point.setX(-200);
	alive = true;
	if (point.getY() < 0)
	{
		velocity.setDx(random(3, 6));
		velocity.setDy(3);
	}
	else
	{
		velocity.setDx(random(3, 6));
		velocity.setDy(-1);
	}
}

SmallRock::SmallRock(Point p)
{
	point.setY(p.getY());
	point.setX(p.getX());
	alive = true;
	velocity.setDx(random(1, 6));
	velocity.setDy(random(1, 6));
}

void SmallRock::draw()
{
	angle += SMALL_ROCK_SPIN;
	drawSmallAsteroid(point, angle);
}

