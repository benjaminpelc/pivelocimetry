#ifndef BPPIV_PIV_VIEW_H
#define BPPIV_PIV_VIEW_H

#include <SFML/Graphics.hpp>
#include <algorithm>
#include "PivPoint.hpp"

class PivView
{
	using VecPivVector = std::vector<PivEng::PivVector>;

	public:
		PivView(PivEng::PivPoint::PivPointVec& vs);
		~PivView();

	private:
		PivEng::PivPoint::PivPointVec& m_pivPointVec;
		VecPivVector piv_vectors;
		double max_velocity_magnitude;
		int num_vectors;
		
		void get_piv_vectors_and_maximum_velocity();
		sf::Color vector_color(const double vel_magnitude, const double max_vel_magnitude) const;
		sf::VertexArray make_vector_graphic(PivEng::PivVector& piv_vector);
		sf::VertexArray make_axis_box(const int i_min, const int j_min, const int i_max, const int j_max) const;
				
};


#endif
