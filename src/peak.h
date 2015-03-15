#ifndef PEAK_H
#define PEAK_H

#include <vector>

class Peak
{
	public:
		typedef std::vector<Peak> PeaksVec;

		Peak();
		Peak(int i, int y, double v);
		~Peak();

		/* Setters */
		void set_iCoord(int i);
		void set_jCoord(int j);
		void set_val(double val);

		/* Getters */
		int get_iCoord();
		int get_jCoord();
		double get_val();
		

	private:
		int _i,
			_j;

		double _val;
		
};

/* Default constructor
 * set all values to -1(.0) */
Peak::Peak() :
	_i(-1),
	_j(-1),
	_val(-1.0)
{}

Peak::Peak(int i, int j, double v) :
	_i(i),
	_j(j),
	_val(v)
{}

void Peak::set_iCoord(int i)
{
	_i = i;
}

void Peak::set_jCoord(int j)
{
	_j = j;
}

void Peak::set_val(double v)
{
	_val = v;
}

int Peak::get_iCoord()
{
	return _i;
}

int Peak::get_jCoord()
{
	return _j;
}

double Peak::get_val()
{
	return _val;
}

/* Destructor */
Peak::~Peak() {}

#endif
