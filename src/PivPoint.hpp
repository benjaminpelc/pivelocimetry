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
#include "Vec2D2C.hpp"

namespace PivEng {


	class PivPoint
	{
		public:
			using PivPointVec = std::vector<PivPoint>;

			PivPoint(int xCoord, int yCoord, PivOptions& options);
			~PivPoint();

			// CCF* get_ccf();
			Peak::PeaksVec& peaks();
			Disp::DispVec& dispsVec();


			void set_xCoord(int x);
			void set_yCoord(int y);
			void set_coords(Grid::CoordPair coords);

			int x();
			int y();
			
			std::unique_ptr<dv> getDv();
			
			Disp& primaryDisp();
			void printToOfstream(std::ofstream& file);
			void printPeaks();
			void printDisps();
			

		private:
			// CCF::Sptr m_ccf;
			Peak::PeaksVec m_peaksVector;
			Disp::DispVec m_dispsVec;
			int m_i, m_j;
	};

}

#endif
