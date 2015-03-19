#ifndef DISPLACEMENT_H
#define DISPLACEMENT_H

#include <vector>

class Displacement
{
	public:
		typedef std::vector<Displacement> DispVec;

		Displacement() {};
		Displacement(double x, double y, bool torf);
		~Displacement();

		void setX(double x);
		void setY(double y);
		void setValid(bool torf);
		void setDisp(double x, double y, bool torf);

		double x();
		double y();
		bool valid();

	private:
		double _x,
			   _y;
		bool _valid;
};

Displacement::Displacement(double x, double y, bool torf) : _x(x), _y(y), _valid(torf) {}

Displacement::~Displacement() {}

void Displacement::setX(double x)
{
	_x = x;
}

void Displacement::setY(double y)
{
	_y = y;
}

void Displacement::setValid(bool torf)
{
	_valid = torf;
}

void Displacement::setDisp(double x, double y, bool torf)
{
	_x = x;
	_y = y;
	_valid = torf;
}

bool Displacement::valid()
{
	return _valid;
}

double Displacement::x()
{
	return _x;
}

double Displacement::y()
{
	return _y;
}
#endif
