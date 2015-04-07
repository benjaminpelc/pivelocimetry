#include "Disp.hpp"

namespace PivEng {
Disp::Disp()
{
}

Disp::Disp(double u_in, double v_in, bool valid_in) : 
	u(u_in),
	v(v_in),
	valid(valid_in)
{
}

Disp::~Disp() {}

void Disp::set_displacement(double u_in, double v_in, bool valid_in)
{ 
	u = u_in;
	v = v_in;
	valid = valid_in;
}

void Disp::set_valid(bool valid_in)
{
	valid = valid_in;
}

double Disp::get_u() const
{
	return u;
}
double Disp::get_v() const
{
	return v;
}
bool Disp::is_valid() const
{
	return valid;
}
}
