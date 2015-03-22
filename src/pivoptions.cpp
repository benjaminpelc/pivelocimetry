#include "pivoptions.h"

// Constructor
PivOptions::PivOptions() :
		// _winWidth(16),
		// _winHeight(16),
		_ovlpHoriz(8),
		_ovlpVert(8),
		_noPeaks(3),
		_winSize(16,16),
		_maxDisp(0,0)
{
}

/*
 * Constructor for when given a map of key value pairs
 */
PivOptions::PivOptions(std::map<std::string, std::string> optionMap)
{
	/* Check for window size */
	_winSize.first  = keyExistsToInt(optionMap, "interrogation_window_x", 16);
	_winSize.second = keyExistsToInt(optionMap, "interrogation_window_y", 16);

	/* Check for overlap */
	_ovlpHoriz = keyExistsToInt(optionMap, "window_overlap_x", 0);
	_ovlpVert  = keyExistsToInt(optionMap, "window_overlap_y", 0);

	/* Check for number of correlation peaks to find */
	_noPeaks = keyExistsToInt(optionMap, "num_ccf_peaks", 3);

	/* Max displacements */
	_maxDisp.first = keyExistsToInt(optionMap, "max_displacement_x", floor(_winHeight / 2) - 1);
	_maxDisp.second = keyExistsToInt(optionMap, "max_displacement_y", floor(_winWidth / 2) - 1);
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
int PivOptions::winWidth()
{
	return _winSize.first;
}

int PivOptions::winHeight()
{
	return _winSize.second;
}

int PivOptions::olvpHoriz()
{
	return _ovlpHoriz;
}

int PivOptions::olvpVert()
{
	return _ovlpVert;
}

int PivOptions::numPeaks()
{
	return _noPeaks;
}

int PivOptions::maxDispX()
{
	return _maxDisp.first;
}

int PivOptions::maxDispY()
{
	return _maxDisp.second;
}

std::pair<int, int>& PivOptions::winSize()
{
	return _winSize;
}

// Setters
void PivOptions::setWinWidth(int x)
{
	_winSize.first = x;
}

void PivOptions::setWinHeight(int x)
{
	_winSize.second = x;
}

void PivOptions::setOvlpHoriz(int x)
{
	_ovlpHoriz = x;
}

void PivOptions::setOvlpVert(int x)
{
	_ovlpVert = x;
}

void PivOptions::setNumPeaks(int n)
{
	_noPeaks = n;
}

void PivOptions::print()
{
	std::cout << "Ix: " << winWidth() << "\tIy: " << winHeight() << 
		"\nOx: " << _ovlpHoriz << "\tOy: " << _ovlpVert << 
		"\nxMax: " << maxDispX() << "\tyMax: " << maxDispY() <<
		"\nNo peaks: " << _noPeaks << std::endl;
}
