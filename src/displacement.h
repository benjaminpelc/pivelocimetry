/* Class: Disp
 * Namespace: PivEng
 *
 * Author: B. Pelc
 * Date: 22/03/2015
 *
 * Disp class, seems a little surplus. Perhaps include as a struct in PivPoint. *
 */

#ifndef BPPIV_PIV_ENGINE_DISPLACEMENT_H
#define BPPIV_PIV_ENGINE_DISPLACEMENT_H

#include <vector>

namespace PivEng {

	class Disp
	{
		public:
			typedef std::vector<Disp> DispVec;

			Disp() {};
			Disp(double x, double y, bool torf);
			~Disp();

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

	Disp::Disp(double x, double y, bool torf) : m_x(x), m_y(y), m_valid(torf) {}

	Disp::~Disp() {}

	void Disp::setX(double x)
	{
		m_x = x;
	}

	void Disp::setY(double y)
	{
		m_y = y;
	}

	void Disp::setValid(bool torf)
	{
		m_valid = torf;
	}

	void Disp::setDisp(double x, double y, bool torf)
	{
		m_x = x;
		m_y = y;
		m_valid = torf;
	}

	bool Disp::valid()
	{
		return m_valid;
	}

	double Disp::x()
	{
		return m_x;
	}

	double Disp::y()
	{
		return m_y;
	}

}

#endif
