#ifndef BPPIV_VECTOR_2D_2C_H
#define BPPIV_VECTOR_2D_2C_H

#include <cmath>

class PivVector {
	public: 
		PivVector();
		PivVector(const double x0, const double y0, const double u0, const double v0);
		~PivVector();


		double get_x() const;
		double get_y() const;
		double get_u() const;
		double get_v() const;

		double get_magnitude();

	private:
		double x, y, u, v;
};

#endif
