#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 5
#define BULLET_LIFE 40

#include "flyingObject.h"
#include <cmath>

class Bullet : public FlyingObject
{
private:
	bool alive;
	Velocity velocity;
	Point point;
	float angle;
	int life;
	static int wins;

public:
	Bullet() : alive(true), life(BULLET_LIFE) {}
	~Bullet() {}

	void fire(const Point & point, float angle, Velocity v);
	void applyShipSpeed(Velocity v);
	Point getPoint() const
	{
		return this->point;
	}

	void changePoint(Velocity v);

	virtual void advance();
	virtual void draw();
};

// Put your Bullet class here




#endif /* bullet_h */
