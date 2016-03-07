#include "myarea.h"

MyArea::MyArea(PivEng::PivPoint::PivPointVec &vs) :
	m_pivPointVec(vs),
	piv_vectors(vs.size())
{
	set_size_request(600,600);
	get_piv_vectors_and_maximum_velocity();
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
	cr->fill();
	cr->stroke();

	cr->set_line_width(0.001);

	for(auto& p : piv_vectors)
		add_vector_graphic(cr, p, vector_scale_factor);

	return true;
}

void MyArea::get_piv_vectors_and_maximum_velocity() {
  auto vector_magnitude = 0.0;
  auto counter = 0;
  for (auto &piv_point : m_pivPointVec) {
    auto piv_vector = piv_point.get_piv_vector();
    if (piv_vector) {
      vector_magnitude = piv_vector->get_magnitude();
      piv_vectors[counter++] = *piv_vector;
      if (vector_magnitude > max_velocity_magnitude)
        max_velocity_magnitude = vector_magnitude;
    }
  }
  piv_vectors.resize(counter);
  num_vectors = counter;
}

void MyArea::add_vector_graphic(Cairo::RefPtr<Cairo::Context> cr, PivEng::PivVector& p, const double vector_scale_factor) {
	
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
