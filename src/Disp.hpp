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

class Disp
{
	public:
		using DispVec = std::vector<Disp>;

		Disp();
		Disp(double u_in, double v_in, bool valid_in);
		~Disp();

		void set_displacement(double u_in, double v_in, bool valid_in);

		double get_u() const;
		double get_v() const;
		bool is_valid() const;

	// private:
		double u = 0.0, v = 0.0;
		bool valid = false;
};

}

#endif
