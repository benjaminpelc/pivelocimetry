#include "Vec2D2C.hpp"

namespace PivEng {
PivVector::PivVector() :
	x(0.0), y(0.0), velocities()
{
}

PivVector::PivVector(const double x0, const double y0, const double u0, const double v0) :
	x(x0), y(y0), velocities(u0, v0, true)
{
}

PivVector::PivVector(const double x0, const double y0, const Disp& disp_in) :
	x(x0), y(y0), velocities(disp_in)
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
	return velocities.get_u();	
}

double PivVector::get_v() const
{
	return velocities.get_v();
}

double PivVector::get_magnitude()
{
	return velocities.get_magnitude();
}

PivVector::~PivVector() {}
}
