#ifndef PIV_OPTIONS_H
#define PIV_OPTIONS_H

class PivOptions
{
	public:
		PivOptions();
		~PivOptions();

		// Getters
		int get_windowWidth();
		int get_windowHeight();
		int get_overlapHoriz();
		int get_overlapVert();

		// Setters
		void set_windowWidth(int x);
		void set_windowHeight(int x);
		void set_overlapHoriz(int x);
		void set_overlapVert(int x);

		// Print in console
		void print();

	private:
		// Properties
		int _windowWidth,
			_windowHeight,
			_overlapHoriz,
			_overlapVert;
};

#endif
