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
		std::vector<sf::VertexArray> vel_vector_graphics;
		sf::VertexArray crosshairs;
		sf::VertexArray axis_box;
		sf::Vector2i  mouse;
		
		void get_piv_vectors_and_maximum_velocity();
		void update_crosshairs(const sf::Vector2i& mouse);
		void render_frame(sf::RenderWindow& window) const;
		void event_handler(sf::RenderWindow& window, const sf::Event& event);
		sf::Color vector_color(const double vel_magnitude, const double max_vel_magnitude) const;
		sf::VertexArray make_vector_graphic(PivEng::PivVector& piv_vector);
		sf::VertexArray make_axis_box(const int i_min, const int j_min, const int i_max, const int j_max) const;
		sf::VertexArray make_crosshairs(const int i_min, const int j_min, const int i_max, const int j_max) const;
				
};


#endif
