// MyAreaD.cpp
// Implementation of MyAreaD class. This is the Gtk drawing area on which
// velocity vectors are plotted.
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

#include "MyAreaD.h"

MyAreaD::MyAreaD(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : Gtk::DrawingArea(cobject),
	m_refGlade(refGlade)
	// m_pivPointVec(nullptr)
{
}

MyAreaD::~MyAreaD() {
	// delete m_pivPointVec;
}

void MyAreaD::init(VecPivVector pv, double const max_vel)
{
	piv_vectors = pv;
	max_velocity_magnitude = max_vel;
	// m_pivPointVec = pv;
	// piv_vectors.resize(m_pivPointVec->size());
	// m_dx = dx;
	// std::cout << m_pivPointVec->size() << std::endl;

	set_size_request(800,600);
	// get_piv_vectors_and_maximum_velocity();
	x_grid = get_unique_grid_values_x();
	y_grid = get_unique_grid_values_y();

	// Spatial resolution of vectors
	dx = x_grid[1] - x_grid[0];
	dy = y_grid[1] - y_grid[0];

	// Take minimum and maximum for plot area as min and
	// max x/y coords plus one dx/dy
	x_min = x_grid.front() - dx;
	y_min = y_grid.front() - dy;
	max_x_coord = x_grid.back() + dx;
	max_y_coord = y_grid.back() + dy;

	axis_scale.x = axis_relative_width / (max_x_coord);
	axis_scale.y = axis_relative_height / (max_y_coord);

	std::cout << "Max velocity magnitude:\t" << max_velocity_magnitude << std::endl;
}

bool MyAreaD::on_draw(const CContextRptr& cr) {

	Gtk::Allocation allocation = get_allocation();

	auto const width = allocation.get_width();
	auto const height = allocation.get_height();

	auto const vector_scale_factor = 3.5;

	// Scale to unit square and translate (0,0) to be (0.5, 0.5), i.e.
	// the centre of the window
	cr->scale(width, height);
	cr->translate(axis_padding_x, axis_padding_y);

	// Draw axis box
	plot_area_box(cr);

	cr->set_line_width(0.001);

	for(auto& p : piv_vectors)
		add_vector_graphic(cr, p, vector_scale_factor);

	return true;
}

void MyAreaD::plot_area_box(CContextRptr cr) {
	cr->set_line_width(0.001);
	cr->set_source_rgb(0.0, 0.0, 0.0);
	cr->rectangle(0.0, 0.0, 1.0 - 2.0 * axis_padding_x, 1.0 - 2.0 * axis_padding_y);
	cr->fill();
	cr->stroke();
}

void MyAreaD::add_vector_graphic(CContextRptr cr, PivEng::PivVector& p, const double vector_scale_factor) {

	auto const x = p.get_x();
	auto const y = p.get_y();
	auto const u = p.get_u();
	auto const v = p.get_v();

	auto magnitude_ratio = p.get_magnitude() / max_velocity_magnitude;

	cr->set_source_rgb(1.0 - magnitude_ratio, 0.0, magnitude_ratio);
	cr->move_to(x * axis_scale.x, y * axis_scale.y);
	cr->line_to( (x + vector_scale_factor * u) * axis_scale.x,
							 (y + vector_scale_factor * v) * axis_scale.y);
	cr->stroke();
}
