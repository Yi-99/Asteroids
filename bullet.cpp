#include "bullet.h"

void Bullet::fire(const Point & point, float angle, Velocity v)
{
	this->point.setX(point.getX());
	this->point.setY(point.getY());
	velocity.setDx(BULLET_SPEED * (sin(PI / 180.0 * (angle))) + v.getDx());
	velocity.setDy(BULLET_SPEED * (-cos(PI / 180.0 * (angle))) + v.getDy());
}

/*CHANGE POINT
*	Input:
*		v: velocity to change point by
*************************************************************************************/
void Bullet::changePoint(Velocity v)
{
	point.setX(point.getX() + v.getDx());
	point.setY(point.getY() + v.getDy());
}

/*ADVANCE
*   has the lander advance in the game loop
*************************************************************************************/
void Bullet::advance()
{
	if (point.getX() > 200.0 || point.getX() < -200.0)
		point.setX(point.getX() * -1);
	if (point.getY() > 200.0 || point.getY() < -200.0)
		point.setY(point.getY() * -1);
	changePoint(velocity);
	
	life--;
	if (life <= 0)
		kill();
	return;
}

void Bullet::applyShipSpeed(Velocity v)
{
	velocity.setDx(velocity.getDx() + v.getDx());
	velocity.setDy(velocity.getDy() + v.getDy());
	return;
}

/*DRAW
*   draws the lander onto the screen
*************************************************************************************/
void Bullet::draw()
{
	drawDot(point);
}
