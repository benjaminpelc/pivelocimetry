#include "PivViewGtk.hpp"

PivViewGtk::PivViewGtk(PivEng::PivPoint::PivPointVec &vs)
    : m_pivPointVec(vs), piv_vectors(vs.size()) {

	Glib::RefPtr<Gtk::Application> vector_viewer = Gtk::Application::create();

	Gtk::Window window;
	window.set_default_size(800, 600);
	window.set_title("Drawing Area");
	std::cout << m_pivPointVec.size() << std::endl;

	// MyArea area;
	// window.add(area);
	// area.show();

	vector_viewer->run(window);
}

PivViewGtk::~PivViewGtk() {}
