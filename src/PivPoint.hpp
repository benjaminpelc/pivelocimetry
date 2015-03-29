/* Class PivPoint
 * 
 * Here we will store all the wonderful things that each PIV 
 * point must have. This is more a container class with setters 
 * and getters rather than any functionality of its own
 *
 * Currently, each point has:
 * 1) A CCF 
 * 2) A vector of peak objects 
 * 3) A vector of displacement objects 
 * 4) A pair of pixel coordinates */

#ifndef PIV_POINT_H
#define PIV_POINT_H

#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "PivOptions.hpp"
#include "Ccf.hpp"
#include "IntMap.hpp"
#include "Peak.hpp"
#include "Disp.hpp"
#include "Grid.hpp"

namespace PivEng {

	struct dv {
		using PivVec = std::vector<dv>;
		dv() {};
		dv(double x0, double y0, double u0, double v0) : x(x0), y(y0), u(u0), v(v0) {};
		~dv() {};
		double x, y, u, v;
	};

	class PivPoint
	{
		public:
			using PivPointVec = std::vector<PivPoint>;

			PivPoint(int xCoord, int yCoord, PivOptions& options);
			~PivPoint();

			CCF* get_ccf();
			Peak::PeaksVec& peaks();
			Disp::DispVec& dispsVec();


			void set_xCoord(int x);
			void set_yCoord(int y);
			void set_coords(Grid::CoordPair& coords);

			int x();
			int y();
			
			dv getDv();
			
			Disp& primaryDisp();
			void printToOfstream(std::ofstream& file);
			void printPeaks();
			void printDisps();
			

		private:
			CCF::Sptr m_ccf;
			Peak::PeaksVec m_peaksVector;
			Disp::DispVec m_dispsVec;
			int m_i, m_j;
	};

}

#endif
