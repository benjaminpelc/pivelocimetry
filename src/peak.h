/* Class Peak 
 *
 * Container class for a correlation function peak,
 * Contains two integer correlation function coordinates and 
 * the  correlation function value at those coordinates. 
 * Contains a validity flag which can be switched on/off as 
 * appropriate */

#ifndef PEAK_H
#define PEAK_H

#include <vector>

class Peak
{
	public:
		typedef std::vector<Peak> PeaksVec;

		Peak();
		Peak(int i, int y, double v, bool torf);
		~Peak();

		/* Setters */
		void set_iCoord(int i);
		void set_jCoord(int j);
		void setVal(double val);
		void setValid(bool torf);

		/* Getters */
		int get_iCoord();
		int get_jCoord();
		double val();
		bool valid();
		

	private:
		int _i,
			_j;

		bool _valid;

		double _val;
		
};

/* Default constructor
 * set all values to -1(.0) and validity to false*/
Peak::Peak() :
	_i(-1),
	_j(-1),
	_val(-1.0),
	_valid(false)
{}

/* Constructor with coordinates, peak value and validty */
Peak::Peak(int i, int j, double v, bool torf) :
	_i(i),
	_j(j),
	_val(v),
	_valid(torf)
{}

/* Setter methods */
void Peak::set_iCoord(int i)
{
	_i = i;
}

void Peak::set_jCoord(int j)
{
	_j = j;
}

void Peak::setVal(double v)
{
	_val = v;
}

void Peak::setValid(bool torf)
{
	_valid = torf;
}

/* Getter methods */
int Peak::get_iCoord()
{
	return _i;
}

int Peak::get_jCoord()
{
	return _j;
}

double Peak::val()
{
	return _val;
}

bool Peak::valid()
{
	return _valid;
}

/* Destructor */
Peak::~Peak() {}

#endif
