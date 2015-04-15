#include "PivViewGtk.hpp"

PivViewGtk::PivViewGtk(PivEng::PivPoint::PivPointVec &vs)
    : m_pivPointVec(vs), piv_vectors(vs.size()),
		pWindow(nullptr),
		pMyArea(nullptr),
		pNumVectorsLabel(nullptr),
		pMaxVelLabel(nullptr)
{
	// Greate an application
	Glib::RefPtr<Gtk::Application> vector_viewer = Gtk::Application::create();
		
	// Get just the piv (x,y,u,v) vectors and the maximum velocity 
	get_piv_vectors_and_maximum_velocity();

	// GLADE
	Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
	refBuilder->add_from_file("../gui/vec_viewer.glade");

	// Get the GtkBuilder-instantiated window:
	refBuilder->get_widget("window1", pWindow);

	// Get the GtkBuilder-instantiated drawingarea:
	refBuilder->get_widget_derived("drawingarea1", pMyArea);
	pMyArea->init(piv_vectors, max_velocity_magnitude);

	// Label for number of vectors 
	refBuilder->get_widget("label_num_vectors_number", pNumVectorsLabel);
	pNumVectorsLabel->set_text(std::to_string(piv_vectors.size()));

	refBuilder->get_widget("label_max_vel_number", pMaxVelLabel);
	pMaxVelLabel->set_text(std::to_string(max_velocity_magnitude) + "px");

	vector_viewer->run(*pWindow);
}

PivViewGtk::~PivViewGtk()
{
	delete pMaxVelLabel;
	delete pNumVectorsLabel;
	delete pMyArea;
	delete pWindow;
}

void PivViewGtk::get_piv_vectors_and_maximum_velocity() {
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
