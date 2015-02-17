#include "application.h"

Application::Application(
			BaseObjectType* cobject,
			const Glib::RefPtr<Gtk::Builder>& refGlade
		)
	: Gtk::Window(cobject),
	_refGlade(refGlade),
	_pStatusbar(0),
	_pButtonSavePivOptions(0),
	_pButtonImage1Select(0),
	_pEntryImage1FileName(0),
	_pWindowHeightSpin(0),
	_pWindowWidthSpin(0),
	_pOverlapHSpin(0),
	_pOverlapVSpin(0)
{

	// Dialog Title
	set_title("PIV Options");

	// Hook up the statusbar
	_refGlade->get_widget("statusbar", _pStatusbar);

	// Hook up the save button
	_refGlade->get_widget("piv_options_button_save", _pButtonSavePivOptions);
	if(_pButtonSavePivOptions)
	{
		_pButtonSavePivOptions->signal_clicked().connect(
				sigc::mem_fun(*this, &Application::on_button_save)
				);
	}

	// Hook up spin buttons
	_refGlade->get_widget("spin_window_x", _pWindowHeightSpin);
	_refGlade->get_widget("spin_window_y", _pWindowWidthSpin);
	_refGlade->get_widget("spin_overlap_x", _pOverlapHSpin);
	_refGlade->get_widget("spin_overlap_y", _pOverlapVSpin);

	// Image Select buttons
	_refGlade->get_widget("image_1_select_button", _pButtonImage1Select);
	if(_pButtonImage1Select)
	{
		_pButtonImage1Select->signal_clicked().connect(
				sigc::mem_fun(*this, &Application::on_button_image_1_select_clicked)
				);
	}

	// File Name Text Display
	_refGlade->get_widget("image_1_filename_entry", _pEntryImage1FileName);
}

Application::~Application() {}

// Save button function
void Application::on_button_save()
{
	// Retrieve values from spin boxes and update PIV settings. 
	_pivOptions.set_windowHeight(
			_pWindowHeightSpin->get_value_as_int()
			);

	_pivOptions.set_windowWidth(
			_pWindowWidthSpin->get_value_as_int()
			);

	_pivOptions.set_overlapHoriz(
			_pOverlapHSpin->get_value_as_int()
			);

	_pivOptions.set_overlapVert(
			_pOverlapVSpin->get_value_as_int()
			);

	// Let statusbar show options were saved
	_pStatusbar->push("PIV Options Saved", 0);

	// Print out the updated values to the console for debugging.
	std::cout << "PIV Options saved" << std::endl;
	_pivOptions.print();
}

void Application::on_button_image_1_select_clicked()
{
	Gtk::FileChooserDialog dialog("Select image", Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.set_transient_for(*this);

	// Add response buttons
	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Open", Gtk::RESPONSE_OK);

	// Add type filters
	Glib::RefPtr<Gtk::FileFilter> filter_tiff = Gtk::FileFilter::create();
	filter_tiff->set_name("TIFF");
	filter_tiff->add_mime_type("image/x-tiff");
	filter_tiff->add_mime_type("image/tiff");

	// Add the filter
	dialog.add_filter(filter_tiff);

	// Show Dialog and await response
	int result = dialog.run();

	// Handle the response 
	switch(result)
	{
		case(Gtk::RESPONSE_OK):
			{
				std::cout << "Open clicked." << std::endl;
				// filename is a standard string
				_image1.set_filename(
						dialog.get_filename()
						);

				std::cout << "Image 1 selected: " << _image1.get_filename() << std::endl;

				_pEntryImage1FileName->set_text(
						_image1.get_filename()	
						);
				break;
			}
		case(Gtk::RESPONSE_CANCEL):
			{
				std::cout << "Cancel clicked" << std::endl;
				break;
			}
		default:
			{
				std::cout << "Unexpected response" << std::endl;
				break;
			}
	}

}
