#ifndef ship_h
#define ship_h


#include "flyingObject.h"
#include <cassert>
#include <cmath>


#define SHIP_SIZE 10
#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.25

class Ship : public FlyingObject
{
private:
	Point point;
	Velocity velocity;
	float angle;
	bool thrust;
	int lives;	

public:
	Ship() : point(), velocity(), angle(0), lives(3) {}
	Ship(const Point & point) : point(point), velocity() { angle = 0; }

	/****************
	* Basic Getters
	****************/
	float getAngle() const { return angle; }
	Point getPoint() const { return point; }
	Velocity getVelocity() const { return velocity;  }
	int getLives() const { return lives; }


	/*****************
	* Drawing
	*****************/
	void draw();
	void advance();
	void kill();
	void changePoint(Velocity v);
	void loseLife() { lives--; };

	/*****************
	* Movement
	*****************/
	void applyThrust();
	void moveRight();
	void moveLeft();
	void reset();

};


#endif /* ship_h */
