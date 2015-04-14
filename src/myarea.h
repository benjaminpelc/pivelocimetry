#ifndef GTKMM_EXAMPLE_MYAREA_H
#define GTKMM_EXAMPLE_MYAREA_H

#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>

#include "PivPoint.hpp"
#include "../lib/bpu.hpp"

struct AxisScale {
	double x{1.0};
	double y{1.0};
};

class MyArea : public Gtk::DrawingArea
{
  using VecPivVector = std::vector<PivEng::PivVector>;
	public:
		MyArea(PivEng::PivPoint::PivPointVec &vs);
		virtual ~MyArea();

	protected:
		// Override default signal handler:
		virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
		void add_vector_graphic(Cairo::RefPtr<Cairo::Context> cr, double x, double y, double u, double v, const double vector_scale_factor);
		void add_vector_graphic(Cairo::RefPtr<Cairo::Context> cr, PivEng::PivVector& p, const double vector_scale_factor);

	private:
		PivEng::PivPoint::PivPointVec &m_pivPointVec;
		VecPivVector piv_vectors;
		std::vector<double> x_grid, y_grid;
		double dx, dy;
		// double x_min;
		double x_min, max_x_coord, y_min, max_y_coord;

		double max_velocity_magnitude;
		int num_vectors;

		void get_piv_vectors_and_maximum_velocity();

		std::vector<double> get_unique_grid_values_x() {
  		auto get_x = [](auto &pv) { return pv.get_x(); };
  		return bpu::collect_unique(piv_vectors, get_x);
		};

		std::vector<double> get_unique_grid_values_y() {
  		auto get_y = [](auto &pv) { return pv.get_y(); };
  		return bpu::collect_unique(piv_vectors, get_y);
		};


		double const axis_padding_x = 0.05;
		double const axis_padding_y = 0.05;

		double const axis_relative_width = 1.0 - 2 * axis_padding_x;
		double const axis_relative_height = 1.0 - 2 * axis_padding_y;

		AxisScale axis_scale;
		
};

#endif
