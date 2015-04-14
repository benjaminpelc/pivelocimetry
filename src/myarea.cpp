#include "myarea.h"
#include <cairomm/context.h>

MyArea::MyArea() {}

MyArea::~MyArea() {}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {

	Gtk::Allocation allocation = get_allocation();

	auto const width = allocation.get_width();
	auto const height = allocation.get_height();

	auto const vector_scale_factor = 3.5;

	// Scale to unit square and translate (0,0) to be (0.5, 0.5), i.e.
	// the centre of the window
	cr->scale(width, height);
	cr->translate(axis_padding_x, axis_padding_y);

	// Draw axis box
	cr->set_line_width(0.001);
	cr->set_source_rgb(0.0, 0.0, 0.0);
	cr->rectangle(0.0, 0.0, 0.9, 0.9);
	cr->stroke();

	auto x = 7.0;
	auto y = 7.0;
	auto u = 1.1758;
	auto v = -1.2634;

	cr->set_line_width(0.001);

	add_vector_graphic(cr, x, y, u, v, vector_scale_factor);
	add_vector_graphic(cr, 151, 319, -2.64234, -3.86374, vector_scale_factor);
	add_vector_graphic(cr, 256, 256, -5, -5, vector_scale_factor);

	return true;
}

void MyArea::add_vector_graphic(Cairo::RefPtr<Cairo::Context> cr, double x, double y, double u, double v, const double vector_scale_factor) {
	cr->set_source_rgb(0.8, 0.0, 0.0);
	cr->move_to(x * axis_scale.x, y * axis_scale.y);
	cr->line_to( (x + vector_scale_factor * u) * axis_scale.x, 
							 (y + vector_scale_factor * v) * axis_scale.y);
	cr->stroke();
}
