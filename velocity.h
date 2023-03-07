#ifndef velocity_H
#define velocity_H

#include "point.h"

class Velocity
{
private:
	float Dx, Dy;

public:
	Velocity() : Dx(0.0), Dy(0.0) {}
	Velocity(float Dx, float Dy)
	{
		this->Dx = Dx;
		this->Dy = Dy;
	}
	float getDx() const
	{
		return Dx;
	}
	float getDy() const
	{
		return Dy;
	}
	void setDx(float x);
	void setDy(float y);

};


#endif /* velocity_h */
