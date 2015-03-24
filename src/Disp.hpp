/* Class: Disp
 * Namespace: PivEng
 *
 * Author: B. Pelc
 * Date: 22/03/2015
 */

#ifndef BPPIV_PIV_ENGINE_DISPLACEMENT_H
#define BPPIV_PIV_ENGINE_DISPLACEMENT_H

#include <vector>

namespace PivEng {

	struct Disp
	{
		using DispVec = std::vector<Disp>;

		Disp() {};
		Disp(double x0, double y0, bool torf) : u(x0), v(y0), valid(torf) {};
		~Disp() {};

		void setDisp(double x0, double y0, bool torf) { u = x0; v = y0; valid = torf; };

		double u, v;
		bool valid;
	};

}

#endif
