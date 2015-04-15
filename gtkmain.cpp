#include <gtkmm.h>
#include <iostream>

int main(int argc, char** argv)
{
	
	Glib::RefPtr<Gtk::Application> vector_viewer = Gtk::Application::create();

	// GLADE
	Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
	refBuilder->add_from_file("./gui/a_gui.glade");

	// Get the GtkBuilder-instantiated window:
	Gtk::Window* pWindow = nullptr;
	refBuilder->get_widget("window1", pWindow);

	vector_viewer->run(*pWindow);

	delete pWindow;

	return 0;
}
