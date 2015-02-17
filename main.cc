#include "application.h"
#include <iostream>

int main(int argc, char** argv)
{
	Gtk::Main kit(argc, argv);

	// Load Glade file and instantiate widgets
	Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
	refBuilder->add_from_file("application.glade");

	// Get the GtkBuilder-instantiated dialog
	Application* pApplication = 0;
	refBuilder->get_widget_derived("application", pApplication);
	kit.run(*pApplication);

	delete pApplication;

	return 0;
}
