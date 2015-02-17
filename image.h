#ifndef BPPIV_IMAGE_H
#define BPPIV_IMAGE_H

#include <iostream>

class Image
{
	public:
		// Constructor
		Image();
		// Destructor
		~Image();

		// Setters 
		void set_filename(std::string fn);

		// Getters
		std::string get_filename();

	private:
		std::string _filename;
};

#endif
