#ifndef GTKMM_EXAMPLE_MYAREA_H
#define GTKMM_EXAMPLE_MYAREA_H

#include <gtkmm/drawingarea.h>

struct AxisScale {
	double x{1.0};
	double y{1.0};
};

class MyArea : public Gtk::DrawingArea
{
	public:
		MyArea();
		virtual ~MyArea();

	protected:
		// Override default signal handler:
		virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
		void add_vector_graphic(Cairo::RefPtr<Cairo::Context> cr, double x, double y, double u, double v, const double vector_scale_factor);

	private:
		double const axis_padding_x = 0.05;
		double const axis_padding_y = 0.05;

		double const axis_relative_width = 1.0 - 2 * axis_padding_x;
		double const axis_relative_height = 1.0 - 2 * axis_padding_y;

		double const max_x_coord = 512;
		double const max_y_coord = 512;

		double const axis_x_scale = axis_relative_width / (max_x_coord);
		double const axis_y_scale = axis_relative_height / (max_y_coord);

		AxisScale const axis_scale{axis_x_scale, axis_y_scale};
		
};

#endif
