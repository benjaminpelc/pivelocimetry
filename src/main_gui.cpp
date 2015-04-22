#include <iostream>

#include <gtkmm/actiongroup.h>
#include <gtkmm/application.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/filechooserbutton.h>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>
#include <gtkmm/hvbox.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/scale.h>
#include <gtkmm/label.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/statusbar.h>
#include <gtkmm/window.h>

#include <gdkmm/pixbuf.h>
#include <gdkmm/general.h>

#include <cairomm/context.h>

#include "PivOptions.hpp"

class ImageArea : public Gtk::DrawingArea {
	public:
		ImageArea() :
			m_im_no(0)
		{
			load_image_1("./img/A001a.tif");
			load_image_2("./img/A001b.tif");
		};
		~ImageArea() override {};

		void load_image_1(const std::string fn) {
			try {
				m_image_1 = Gdk::Pixbuf::create_from_file(fn);
			} catch (...) {
				std::cerr << "Bugger: Can't read image" << std::endl;
			};

			if(m_image_1)
				set_size_request(m_image_1->get_width() / 2, m_image_1->get_height() / 2 );
		};

		void load_image_2(const std::string fn) {
			try {
				m_image_2 = Gdk::Pixbuf::create_from_file(fn);
			} catch (...) {
				std::cerr << "Bugger: Can't read image" << std::endl;
			};

			if(m_image_2)
				set_size_request(m_image_2->get_width() / 2, m_image_2->get_height() / 2 );
		};

		void set_selected_image(const int im_no) { m_im_no = im_no;
			queue_draw(); };

	protected:
		bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override {
			if (!m_image_1)
				return false;

			Gtk::Allocation allocation = get_allocation();
			const int width = allocation.get_width();
			const int height = allocation.get_height();

			// Draw image in middle of the drawing area, or (if the image is larger than
			// the drawing area) draw the middle part of the image
			if (m_im_no == 0)
				Gdk::Cairo::set_source_pixbuf(cr, m_image_1->scale_simple(width, height, Gdk::INTERP_BILINEAR), 0, 0);
			else if (m_im_no == 1)
				Gdk::Cairo::set_source_pixbuf(cr, m_image_2->scale_simple(width, height, Gdk::INTERP_BILINEAR), 0, 0);

			cr->paint();

			return true;
		};
		
		Glib::RefPtr<Gdk::Pixbuf> m_image_1, m_image_2;

	private:
		int m_im_no;

};

class ImageViewer : public Gtk::VBox {
	public:
		ImageViewer() :
			m_image_area(),
			m_adjustment(Gtk::Adjustment::create(0, 0, 1, 1, 2)),
			m_image_select_scale(m_adjustment, Gtk::ORIENTATION_HORIZONTAL)
		{
			pack_start(m_image_area);

			m_image_select_scale.set_digits(0);
			pack_start(m_image_select_scale);
		
			m_image_select_scale.signal_value_changed().connect([this]{on_image_slider_change(); });
		};

		~ImageViewer() {};

		void load_image_1(const std::string fn) { m_image_area.load_image_1(fn); };
		void load_image_2(const std::string fn) { m_image_area.load_image_2(fn); };
		void change_displayed_image();

		void on_image_slider_change()
		{
			auto im_no = static_cast<int>(m_image_select_scale.get_value());
			m_image_area.set_selected_image(im_no);
		};


	protected:
		ImageArea m_image_area;
		Glib::RefPtr<Gtk::Adjustment> m_adjustment;
		Gtk::Scale m_image_select_scale;

};

class ImageFileChooser : public Gtk::Frame {
	public:
		ImageFileChooser(ImageViewer& image_area) :
			m_image_filenames(),
			m_image_area(image_area),
			m_grid(),
			m_label_image1("Image 1:", Gtk::ALIGN_START), m_label_image2("Image 2:", Gtk::ALIGN_START),
			m_image1_chooser_button(), m_image2_chooser_button()
		{
			set_label("Image Options");
			set_label_align(Gtk::ALIGN_END);

			add(m_grid);
			m_grid.attach(m_label_image1, 0, 0, 1, 1);
			m_grid.attach(m_image1_chooser_button, 1, 0, 1, 1);
			m_grid.attach(m_label_image2, 0, 1, 1, 1);
			m_grid.attach(m_image2_chooser_button, 1, 1, 1, 1);
			m_grid.set_border_width(5);
			m_grid.set_row_spacing(5);
			m_grid.set_column_spacing(5);

			m_image1_chooser_button.signal_file_set().connect([this]{ on_image_1_select(); });
			m_image2_chooser_button.signal_file_set().connect([this]{ on_image_2_select(); });
		};
		~ImageFileChooser() {};

		std::string get_image_1_filename() const { return m_image1_chooser_button.get_filename(); };
		std::string get_image_2_filename() const { return m_image2_chooser_button.get_filename(); };

		std::pair<std::string, std::string>& get_image_filenames() { return m_image_filenames; }; 

	protected:
		std::pair<std::string, std::string> m_image_filenames;
		ImageViewer& m_image_area;
		Gtk::Grid m_grid;
		Gtk::Label m_label_image1, m_label_image2;
		Gtk::FileChooserButton m_image1_chooser_button, m_image2_chooser_button;

	private:
		void on_image_1_select()
		{
			m_image_area.load_image_1(m_image1_chooser_button.get_filename());
		}
		void on_image_2_select()
		{
			m_image_area.load_image_2(m_image2_chooser_button.get_filename());
		}
};

class WindowSizeOptions : public Gtk::Frame {
	public:
		WindowSizeOptions(PivOptions& piv_options) :
			m_piv_options(piv_options),
			m_grid(),
			m_x_label("x:", Gtk::ALIGN_START),
			m_y_label("y:", Gtk::ALIGN_START),
			m_x_window_size_adjust(Gtk::Adjustment::create(16, 2, 256, 2, 2, 0)),
			m_y_window_size_adjust(Gtk::Adjustment::create(16, 2, 256, 2, 2, 0)),
			m_x_window_size_spin(m_x_window_size_adjust),
			m_y_window_size_spin(m_y_window_size_adjust)
		{
			set_label("Interrogation Window Size");
			set_label_align(Gtk::ALIGN_START);

			add(m_grid);
			m_grid.set_border_width(5);
			m_grid.set_row_spacing(5);
			
			m_grid.attach(m_x_label, 0, 2, 1, 1);
			m_grid.attach(m_x_window_size_spin, 1, 2, 1, 1);
			
			m_grid.attach(m_y_label, 0, 3, 1, 1);
			m_grid.attach(m_y_window_size_spin, 1, 3, 1, 1);

			m_x_window_size_spin.signal_value_changed().connect([this]{ on_x_changed(); });
			m_y_window_size_spin.signal_value_changed().connect([this]{ on_y_changed(); });
	};

		~WindowSizeOptions() {};

	protected:
		PivOptions& m_piv_options;
		
		Gtk::Grid m_grid;
		Gtk::Label m_x_label, m_y_label;
		Glib::RefPtr<Gtk::Adjustment> m_x_window_size_adjust;
		Glib::RefPtr<Gtk::Adjustment> m_y_window_size_adjust;
		Gtk::SpinButton m_x_window_size_spin, m_y_window_size_spin;

	private:
		void on_x_changed()
		{
			const auto x = m_x_window_size_spin.get_value_as_int();
			m_piv_options.setWinWidth(x);
		};

		void on_y_changed()
		{
			const auto y = m_y_window_size_spin.get_value_as_int();
			m_piv_options.setWinHeight(y);
		};
};

class OverlapOptions : public Gtk::Frame {
	public:
		OverlapOptions(PivOptions& piv_options) :
			m_piv_options(piv_options),
			m_grid(),
			m_x_label("x:", Gtk::ALIGN_START),
			m_y_label("y:", Gtk::ALIGN_START),
			m_x_overlap_adjust(Gtk::Adjustment::create(16, 2, 256, 2, 2, 0)),
			m_y_overlap_adjust(Gtk::Adjustment::create(16, 2, 256, 2, 2, 0)),
			m_x_overlap_spin(m_x_overlap_adjust),
			m_y_overlap_spin(m_y_overlap_adjust)
		{
			set_label("Window Overlap");
			set_label_align(Gtk::ALIGN_START);

			add(m_grid);
			m_grid.set_border_width(5);
			m_grid.set_row_spacing(5);
			
			m_grid.attach(m_x_label, 0, 2, 1, 1);
			m_grid.attach(m_x_overlap_spin, 1, 2, 1, 1);
			
			m_grid.attach(m_y_label, 0, 3, 1, 1);
			m_grid.attach(m_y_overlap_spin, 1, 3, 1, 1);

			m_x_overlap_spin.signal_value_changed().connect([this]{ on_x_changed(); });
			m_y_overlap_spin.signal_value_changed().connect([this]{ on_y_changed(); });
	};

		~OverlapOptions() {};

	protected:
		PivOptions& m_piv_options;
		
		Gtk::Grid m_grid;
		Gtk::Label m_x_label, m_y_label;
		Glib::RefPtr<Gtk::Adjustment> m_x_overlap_adjust;
		Glib::RefPtr<Gtk::Adjustment> m_y_overlap_adjust;
		Gtk::SpinButton m_x_overlap_spin, m_y_overlap_spin;

	private:
		void on_x_changed()
		{
			auto x = m_x_overlap_spin.get_value_as_int();
			m_piv_options.setOvlpHoriz(x);
		};

		void on_y_changed()
		{
			auto y = m_y_overlap_spin.get_value_as_int();
			m_piv_options.setOvlpVert(y);
		};
};

class AnalysisOptions : public Gtk::Frame {
	public:
		AnalysisOptions() :
			m_piv_options(),
			m_grid(),
			m_load_cfg_label("Load config file:"),
			m_cfg_chooser_button(),
			m_window_size_options(m_piv_options),
			m_overlap_options(m_piv_options),
			m_press_me("Press Me!")
		{
			set_label("Analysis Options");
			set_label_align(Gtk::ALIGN_END);

			m_grid.set_column_homogeneous(TRUE);
			add(m_grid);
			m_grid.set_border_width(5);
			m_grid.set_row_spacing(5);
			m_grid.set_column_spacing(5);
			
			m_grid.attach(m_load_cfg_label, 0, 0, 1, 1);
			m_grid.attach(m_cfg_chooser_button, 1, 0, 1, 1);
			
			m_grid.attach(m_window_size_options, 0, 1, 1, 1);
			m_grid.attach(m_overlap_options, 1, 1, 1, 1);

			m_grid.attach(m_press_me, 0, 5, 2, 1);

			m_press_me.signal_clicked().connect([this]{ m_piv_options.print(); });

			m_cfg_chooser_button.set_border_width(10);
		};
		~AnalysisOptions() {};

		PivOptions& getPivOptions() { return m_piv_options; };

	protected:
		PivOptions m_piv_options;

		Gtk::Grid m_grid;
		Gtk::Label m_load_cfg_label;
		Gtk::FileChooserButton m_cfg_chooser_button;
		WindowSizeOptions m_window_size_options;
		OverlapOptions m_overlap_options;
		Gtk::Button m_press_me;
};

class LeftPanelMain : public Gtk::VBox {
	public:
		LeftPanelMain(ImageViewer& image_area) : m_image_file_chooser(image_area),
			m_analysis_options()
		{
			set_spacing(10);
			pack_start(m_image_file_chooser, Gtk::PACK_SHRINK);
			pack_start(m_analysis_options);
		};
		~LeftPanelMain() {};

		PivOptions& getPivOptions() { return m_analysis_options.getPivOptions(); };

		std::pair<std::string, std::string>& get_image_filenames()
		{
			return m_image_file_chooser.get_image_filenames();
		};

	protected:
		ImageFileChooser m_image_file_chooser;
		AnalysisOptions m_analysis_options;
};

class Application : public Gtk::Window {
	public:
		Application() : 
			m_left_main_panel(m_image_area),
			m_main_hbox(),
			m_main_box(),
			m_statusbar(),
			m_image_area()
	{
			set_title("PIV");
			set_default_size(1600, 900);
			set_border_width(10);

			add(m_main_box);

			m_main_box.pack_start(m_main_hbox, Gtk::PACK_EXPAND_WIDGET);
			m_main_box.pack_start(m_statusbar, Gtk::PACK_SHRINK);

			m_main_hbox.pack_start(m_left_main_panel, Gtk::PACK_SHRINK);
			m_main_hbox.pack_start(m_image_area, Gtk::PACK_EXPAND_WIDGET);

			m_main_hbox.set_spacing(10);

			m_statusbar.push("PIV: Image loaded");

			show_all();
		};

		~Application() override {};

	protected:
		LeftPanelMain m_left_main_panel;
		Gtk::HBox m_main_hbox;
		Gtk::VBox m_main_box;
		Gtk::Statusbar m_statusbar;
		ImageViewer m_image_area;
	
	private:
		PivOptions& getPivOptions()
		{
			return m_left_main_panel.getPivOptions();
		};

		std::pair<std::string, std::string>& get_image_filenames()
		{
			return m_left_main_panel.get_image_filenames();
		};

};

int main(int argc, char** argv)
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "piv.front");
	Application main_window;

	return app->run(main_window);
}
