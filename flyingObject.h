#ifndef flyingObject_h
#define flyingObject_h


#include "point.h"
#include "velocity.h"
#include "uiDraw.h"

#define PI atan(1)*4

class FlyingObject
{
protected:
	Point point;
	Velocity velocity;
	float dx, dy;
	bool alive;
public:
	FlyingObject() : alive(true) {}
	Velocity getVelocity() const
	{
		return velocity;
	}
	void setPoint(Point & point)
	{
		this->point = point;
	}
	Point getPoint()
	{
		return point;
	}
	bool isAlive() const
	{
		return alive;
	}
	void setAlive(bool tf)
	{
		alive = tf;
	}
	void kill()
	{
		alive = false;
	}
	virtual void advance() = 0;
	virtual void draw() = 0;
};

#endif /* flyingObject_h */
