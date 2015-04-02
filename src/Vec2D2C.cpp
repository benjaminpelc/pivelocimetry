#include "Vec2D2C.hpp"

dv::dv() :
	x(0.0), y(0.0), u(0.0), v(0.0)
{
}

dv::dv(double x0, double y0, double u0, double v0) :
	x(x0), y(y0), u(u0), v(v0) 
{
}

double dv::mag()
{
	return sqrt(pow(u, 2) + pow(v, 2));
}

dv::~dv() {}
