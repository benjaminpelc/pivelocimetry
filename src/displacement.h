#ifndef DISPLACEMENT_H
#define DISPLACEMENT_H

#include <vector>

namespace PivEng {

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
		double m_x,
			   m_y;
		bool m_valid;
};

Displacement::Displacement(double x, double y, bool torf) : m_x(x), m_y(y), m_valid(torf) {}

Displacement::~Displacement() {}

void Displacement::setX(double x)
{
	m_x = x;
}

void Displacement::setY(double y)
{
	m_y = y;
}

void Displacement::setValid(bool torf)
{
	m_valid = torf;
}

void Displacement::setDisp(double x, double y, bool torf)
{
	m_x = x;
	m_y = y;
	m_valid = torf;
}

bool Displacement::valid()
{
	return m_valid;
}

double Displacement::x()
{
	return m_x;
}

double Displacement::y()
{
	return m_y;
}

}

#endif
