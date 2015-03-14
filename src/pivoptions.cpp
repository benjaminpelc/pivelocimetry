#include "pivoptions.h"

// Constructor
PivOptions::PivOptions() {}

/*
 * Constructor for when given a map of key value pairs
 */
PivOptions::PivOptions(std::map<std::string, std::string> optionMap)
{
	/* Check for window size */
	_windowWidth = !optionMap["interrogation_window_x"].empty() ?
		atoi(optionMap["interrogation_window_x"].c_str()) : 16;

	_windowHeight = !optionMap["interrogation_window_y"].empty() ?
		atoi(optionMap["interrogation_window_y"].c_str()) : 16;

	/* Check for overlap */
	_overlapHoriz = !optionMap["window_overlap_x"].empty() ?
		atoi(optionMap["window_overlap_x"].c_str()) : 0;

	_overlapVert = !optionMap["window_overlap_y"].empty() ?
		atoi(optionMap["window_overlap_y"].c_str()) : 0;
	
}

// Destructor
PivOptions::~PivOptions() {}

// Getters
int PivOptions::get_windowWidth()
{
	return _windowWidth;
}

int PivOptions::get_windowHeight()
{
	return _windowHeight;
}

int PivOptions::get_overlapHoriz()
{
	return _overlapHoriz;
}

int PivOptions::get_overlapVert()
{
	return _overlapVert;
}

// Setters
void PivOptions::set_windowWidth(int x)
{
	_windowWidth = x;
}

void PivOptions::set_windowHeight(int x)
{
	_windowHeight = x;
}

void PivOptions::set_overlapHoriz(int x)
{
	_overlapHoriz = x;
}

void PivOptions::set_overlapVert(int x)
{
	_overlapVert = x;
}

void PivOptions::print()
{
	std::cout << "Ix: " << _windowWidth << "\tIy: " << _windowHeight << 
		"\nOx: " << _overlapHoriz << "\tOy: " << _overlapVert << std::endl;
}
