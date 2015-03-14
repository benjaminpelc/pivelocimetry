#include "pivoptions.h"

// Constructor
PivOptions::PivOptions() {}

/*
 * Constructor for when given a map of key value pairs
 */
PivOptions::PivOptions(std::map<std::string, std::string> optionMap)
{
	/* Check for window size */
	if (!optionMap["interrogation_window_x"].empty())
	{
		set_windowWidth(atoi(optionMap["interrogation_window_x"].c_str()));
	}
	if (!optionMap["interrogation_window_y"].empty())
	{
		set_windowHeight(atoi(optionMap["interrogation_window_y"].c_str()));
	}

	/* Check for overlap */
	if (!optionMap["window_overlap_x"].empty())
	{
		set_overlapHoriz(atoi(optionMap["window_overlap_x"].c_str()));
	}
	if (!optionMap["window_overlap_y"].empty())
	{
		set_overlapVert(atoi(optionMap["window_overlap_y"].c_str()));
	}
	
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
