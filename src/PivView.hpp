#ifndef BPPIV_PIV_VIEW_H
#define BPPIV_PIV_VIEW_H

#include <SFML/Graphics.hpp>
#include <algorithm>
#include "PivPoint.hpp"
#include "../lib/bpu.hpp"

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
		sf::Vector2f  mouse;
		sf::Vector2i axis_bottom_left, axis_top_right;
		sf::Font font;
		sf::Text header_text;
		std::vector<sf::Text> status_bar_texts;
		
		void get_piv_vectors_and_maximum_velocity();
		void make_graphics();
		void make_status_bar_texts();
		void make_header_texts();
		void update_crosshairs(const sf::Vector2f& mouse);
		void update_status_bar(const sf::Vector2f& mouse);
		void render_frame(sf::RenderWindow& window) const;
		void event_handler(sf::RenderWindow& window, const sf::Event& event);
		sf::Color vector_color(const double vel_magnitude, const double max_vel_magnitude) const;
		sf::VertexArray make_vector_graphic(PivEng::PivVector& piv_vector);
		sf::VertexArray make_axis_box(const int i_min, const int j_min, const int i_max, const int j_max) const;
		sf::VertexArray make_crosshairs(const int i_min, const int j_min, const int i_max, const int j_max) const;
		sf::Text make_status_bar_label(const int x_position, std::string&& words);
		std::vector<double> get_unique_grid_values();
				
};


#endif
