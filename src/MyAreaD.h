#ifndef GTKMM_EXAMPLE_MYAREA_D_H
#define GTKMM_EXAMPLE_MYAREA_D_H

#include <gtkmm/builder.h>
#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>

#include "PivPoint.hpp"
#include "../lib/bpu.hpp"

struct AxisScale {
	double x{1.0};
	double y{1.0};
};

class MyAreaD : public Gtk::DrawingArea
{
  using VecPivVector = std::vector<PivEng::PivVector>;
  using CContextRptr = Cairo::RefPtr<Cairo::Context>;

	public:
		MyAreaD(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
		~MyAreaD() override;

		void init(VecPivVector pv, double const max_velocity_magnitude);

	protected:
		Glib::RefPtr<Gtk::Builder> m_refGlade;

	private:

		// MEMBERS 
		VecPivVector piv_vectors;

		std::vector<double> x_grid, y_grid;

		double dx, dy;
		double x_min, max_x_coord, y_min, max_y_coord;
		double max_velocity_magnitude;

		double const axis_padding_x = 0.025;
		double const axis_padding_y = 0.025;

		double const axis_relative_width = 1.0 - 2 * axis_padding_x;
		double const axis_relative_height = 1.0 - 2 * axis_padding_y;

		AxisScale axis_scale;

		// PRIVATE MEMBER FUNCTIONS 
		// Override default signal handler:
		bool on_draw(const CContextRptr& cr) override;
		void plot_area_box(CContextRptr cr);
		void add_vector_graphic(CContextRptr cr, PivEng::PivVector& p, const double vector_scale_factor);

		std::vector<double> get_unique_grid_values_x() {
  		auto get_x = [](auto &pv) { return pv.get_x(); };
  		return bpu::collect_unique(piv_vectors, get_x);
		};

		std::vector<double> get_unique_grid_values_y() {
  		auto get_y = [](auto &pv) { return pv.get_y(); };
  		return bpu::collect_unique(piv_vectors, get_y);
		};

};

#endif

