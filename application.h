#ifndef GTKMM_EXAMPLE_DERIVED_DIALOG_H
#define GTKMM_EXAMPLE_DERIVED_DIALOG_H

#include <gtkmm.h>
#include <iostream>
#include "pivoptions.h"
#include "image.h"

class Application : public Gtk::Window
{
	public:
		Application(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
		virtual ~Application();

	protected:
		// Sig hand
		void on_button_save();
		void on_button_image_select_clicked(Image &im);

		Glib::RefPtr<Gtk::Builder> _refGlade;
		
		Gtk::Button	*_pButtonSavePivOptions,
					*_pButtonImage1Select,
					*_pButtonImage2Select;
		
		Gtk::SpinButton *_pWindowHeightSpin,
						*_pWindowWidthSpin,
						*_pOverlapHSpin,
						*_pOverlapVSpin;

		Gtk::Statusbar *_pStatusbar;

		Gtk::Entry *_pEntryImage1FileName,
					*_pEntryImage2FileName;

	private:
		// PIV Settings Holder
		PivOptions _pivOptions;
		Image _image1,
			  _image2;

		void update_image_filname_entry();
};

#endif
