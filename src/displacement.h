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

		void set_displacementX(double x);
		void set_displacementY(double y);
		void set_isValid(bool torf);

		double get_displacementX();
		double get_displacementY();
		bool get_isValid();

	private:
		double _displacementX,
			   _displacementY;
		bool _isValid;
};

Displacement::Displacement(double x, double y, bool torf) : _displacementX(x), _displacementY(y), _isValid(torf) {}

Displacement::~Displacement() {}

void Displacement::set_displacementX(double x)
{
	_displacementX = x;
}

void Displacement::set_displacementY(double y)
{
	_displacementY = y;
}

void Displacement::set_isValid(bool torf)
{
	_isValid = torf;
}

bool Displacement::get_isValid()
{
	return _isValid;
}

double Displacement::get_displacementX()
{
	return _displacementX;
}

double Displacement::get_displacementY()
{
	return _displacementY;
}
#endif
