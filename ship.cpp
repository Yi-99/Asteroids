#include "ship.h"

void Ship::draw()
{
	drawShip(point, (angle + 180), thrust);
	thrust = false;
}

void Ship::moveLeft()
{
	angle += ROTATE_AMOUNT;
		
	if (angle > 360)
	{
		angle = fmod(angle, 360);
	}
}

void Ship::reset()
{
	velocity.setDx(0.0);
	velocity.setDy(0.0);
	point.setX(0.0);
	point.setY(0.0);
	alive = true;
}

void Ship::kill()
{
	alive = false;
	reset();
	lives--;
}

void Ship::applyThrust()
{
	float dx = THRUST_AMOUNT * (sin(PI / 180.0 * (angle)));
	float dy = THRUST_AMOUNT * (-cos(PI / 180.0 * (angle)));
	velocity.setDx(velocity.getDx() + dx);
	velocity.setDy(velocity.getDy() + dy);	
	thrust = true;
}

void Ship::moveRight()
{
	angle -= ROTATE_AMOUNT;

	if (angle > 360)
	{
		angle = fmod(angle, 360);
	}
}

/*ADVANCE
*   has the lander advance in the game loop
*************************************************************************************/
void Ship::advance()
{
	if (point.getX() > 200.0 || point.getX() < -200.0)
		point.setX(point.getX() * -1);
	if (point.getY() > 200.0 || point.getY() < -200.0)
		point.setY(point.getY() * -1);
	changePoint(velocity);
	return;
}

void Ship::changePoint(Velocity v)
{
	point.setX(point.getX() + v.getDx());
	point.setY(point.getY() + v.getDy());
}



