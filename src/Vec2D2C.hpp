#ifndef BPPIV_VECTOR_2D_2C_H
#define BPPIV_VECTOR_2D_2C_H

#include <cmath>
#include "Disp.hpp"

namespace PivEng {

class PivVector {
	public: 
		PivVector();
		PivVector(const double x0, const double y0, const double u0, const double v0);
		PivVector(const double x0, const double y0, const Disp& disp_in); 
		~PivVector();

		double get_x() const;
		double get_y() const;
		double get_u() const;
		double get_v() const;

		double get_magnitude();

	private:
		double x, y;
		Disp velocities;

};
}
#endif
