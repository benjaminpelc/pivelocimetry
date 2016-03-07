// #include <gtkmm.h>
#include "myarea.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>


int main()
{
	Glib::RefPtr<Gtk::Application> vector_viewer = Gtk::Application::create();

	Gtk::Window window;
	window.set_default_size(800, 600);
	window.set_title("Drawing Area");

	MyArea area;
	window.add(area);
	area.show();

	return vector_viewer->run(window);
}
