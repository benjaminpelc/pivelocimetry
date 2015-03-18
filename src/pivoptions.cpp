#include "pivoptions.h"

// Constructor
PivOptions::PivOptions() :
		_windowWidth(16),
		_windowHeight(16),
		_overlapHoriz(8),
		_overlapVert(8),
		_noPeaks(3),
		_windowSize(16,16)
{
}

/*
 * Constructor for when given a map of key value pairs
 */
PivOptions::PivOptions(std::map<std::string, std::string> optionMap)
{
	/* Check for window size */
	_windowWidth  = keyExistsToInt(optionMap, "interrogation_window_x", 16);
	_windowHeight = keyExistsToInt(optionMap, "interrogation_window_y", 16);;

	/* Check for overlap */
	_overlapHoriz = keyExistsToInt(optionMap, "window_overlap_x", 0);
	_overlapVert  = keyExistsToInt(optionMap, "window_overlap_y", 0);

	/* Check for number of correlation peaks to find */
	_noPeaks = keyExistsToInt(optionMap, "num_ccf_peaks", 3);

	/* Put window dimensions in a pair */
	_windowSize.first  = _windowWidth;
	_windowSize.second = _windowHeight;
}

int PivOptions::keyExistsToInt(std::map<std::string, std::string>& optMap, std::string key, int defaultVal)
{
	/* If the value of the map with key key is an empty string then 
	 * return a default integer otherwise convert the string to an 
	 * integer.
	 *
	 * todo:
	 * 1) Add some checking, if string conversion is unsuccessful return 
	 * 	  the default integer. */
	return !optMap[key].empty() ? atoi(optMap[key].c_str()) : defaultVal;
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

int PivOptions::get_noPeaks()
{
	return _noPeaks;
}

std::pair<int, int>& PivOptions::get_windowSize()
{
	return _windowSize;
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

void PivOptions::set_noPeaks(int n)
{
	_noPeaks = n;
}

void PivOptions::print()
{
	std::cout << "Ix: " << _windowWidth << "\tIy: " << _windowHeight << 
		"\nOx: " << _overlapHoriz << "\tOy: " << _overlapVert << 
		"\nNo peaks: " << _noPeaks << std::endl;
}
