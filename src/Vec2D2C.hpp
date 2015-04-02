#ifndef BPPIV_VECTOR_2D_2C_H
#define BPPIV_VECTOR_2D_2C_H

#include <cmath>

class dv {
	public: 
		dv();
		dv(double x0, double y0, double u0, double v0);
		~dv();

		double mag();

		double x, y, u, v;
};

#endif
