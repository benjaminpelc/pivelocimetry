/* Class Peak 
 *
 * Container class for a correlation function peak,
 * Contains two integer correlation function coordinates and 
 * the  correlation function value at those coordinates. 
 * Contains a validity flag which can be switched on/off as 
 * appropriate */

#ifndef BPPIB_PIV_ENGINE_PEAK_H
#define BPPIB_PIV_ENGINE_PEAK_H

#include <vector>

namespace PivEng {

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
			void setPeak(int i, int j, double val, bool torf);

			/* Getters */
			int get_iCoord();
			int get_jCoord();
			double val();
			bool valid();
			

		private:
			int m_i,
				m_j;

			bool m_valid;

			double m_val;
			
	};

	/* Default constructor
 	 * set all values to -1(.0) and validity to false*/
	Peak::Peak() :
		m_i(-1),
		m_j(-1),
		m_val(-1.0),
		m_valid(false)
	{}

	/* Constructor with coordinates, peak value and validty */
	Peak::Peak(int i, int j, double v, bool torf) :
		m_i(i),
		m_j(j),
		m_val(v),
		m_valid(torf)
	{}

	/* Setter methods */
	void Peak::setPeak(int i, int j, double val, bool torf)
	{
		m_i = i;
		m_j = j;
		m_val = val;
		m_valid = torf;
	}

	void Peak::set_iCoord(int i)
	{
		m_i = i;
	}

	void Peak::set_jCoord(int j)
	{
		m_j = j;
	}

	void Peak::setVal(double v)
	{
		m_val = v;
	}

	void Peak::setValid(bool torf)
	{
		m_valid = torf;
	}

	/* Getter methods */
	int Peak::get_iCoord()
	{
		return m_i;
	}

	int Peak::get_jCoord()
	{
		return m_j;
	}

	double Peak::val()
	{
		return m_val;
	}

	bool Peak::valid()
	{
		return m_valid;
	}

	/* Destructor */
	Peak::~Peak() {}
}
#endif
