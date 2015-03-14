#include "pivoptions.h"
#include <iostream>

// Constructor
PivOptions::PivOptions() {}

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
