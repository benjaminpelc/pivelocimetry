#include "Vec2D2C.hpp"

PivVector::PivVector() :
	x(0.0), y(0.0), u(0.0), v(0.0)
{
}

PivVector::PivVector(const double x0, const double y0, const double u0, const double v0) :
	x(x0), y(y0), u(u0), v(v0) 
{
}

double PivVector::get_x() const
{
	return x;
}

double PivVector::get_y() const
{
	return y;
}

double PivVector::get_u() const
{
	return u;	
}

double PivVector::get_v() const
{
	return v;
}

double PivVector::get_magnitude()
{
	return sqrt(pow(u, 2) + pow(v, 2));
}

PivVector::~PivVector() {}
