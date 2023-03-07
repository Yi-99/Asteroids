#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10



#include "flyingObject.h"
#include <cmath>

class Rock : public FlyingObject
{
public:
	bool alive;
	Velocity velocity;
	Point point;
	int angle = random(0, 180);
	int size;

	virtual int hit() = 0;
	void changePoint(Velocity v);
	Point getPoint() const { return this->point; }
	float getAngle() const { return this->angle; }
	Velocity getVelocity() const { return this->velocity; }

	void advance();
	virtual void draw() = 0;
	virtual int getSize() = 0;
};

class BigRock : public Rock
{
public:
	int lives;
	int size = 16;
	int getSize() { return size; }
	BigRock();
	BigRock(Point p);
	~BigRock() {}
	int hit()
	{
		kill();
		return 3;
	}
	void draw();
};

class MediumRock : public Rock
{
public:
	MediumRock();
	MediumRock(Point p);
	~MediumRock() {}
	int size = 10;
	int getSize() { return size; }
	int hit()
	{
		kill();
		return 2;
	}
	void draw();
};

class SmallRock : public Rock
{
public:
	SmallRock();
	SmallRock(Point p);
	~SmallRock() {}
	int size = 6;
	int getSize() { return size; }
	int hit()
	{
		kill();
		return 1;
	}
	void draw();
};


#endif /* rocks_h */
