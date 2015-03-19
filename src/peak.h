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
		void set_val(double val);
		void set_isValid(bool torf);

		/* Getters */
		int get_iCoord();
		int get_jCoord();
		double get_val();
		bool get_isValid();
		

	private:
		int _i,
			_j;

		bool _isValid;

		double _val;
		
};

/* Default constructor
 * set all values to -1(.0) and validity to false*/
Peak::Peak() :
	_i(-1),
	_j(-1),
	_val(-1.0),
	_isValid(false)
{}

/* Constructor with coordinates, peak value and validty */
Peak::Peak(int i, int j, double v, bool torf) :
	_i(i),
	_j(j),
	_val(v),
	_isValid(torf)
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

void Peak::set_val(double v)
{
	_val = v;
}

void Peak::set_isValid(bool torf)
{
	_isValid = torf;
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

double Peak::get_val()
{
	return _val;
}

bool Peak::get_isValid()
{
	return _isValid;
}

/* Destructor */
Peak::~Peak() {}

#endif
