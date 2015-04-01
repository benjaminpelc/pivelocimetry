#include "PivOptions.hpp"

// Constructor
PivOptions::PivOptions() :
		m_noPeaks(3),
		m_overlap(0,0),
		m_winSize(16,16),
		m_maxDisp(7,7)
{
}

/*
 * Constructor for when given a map of key value pairs
 */
PivOptions::PivOptions(std::unordered_map<std::string, std::string> optionMap)
{
	/* Check for window size */
	m_winSize.first  = keyExistsToInt(optionMap, "interrogation_window_x", 16);
	m_winSize.second = keyExistsToInt(optionMap, "interrogation_window_y", 16);

	/* Check for overlap */
	m_overlap.first   = keyExistsToInt(optionMap, "window_overlap_x", 0);
	m_overlap.second  = keyExistsToInt(optionMap, "window_overlap_y", 0);

	/* Check for number of correlation peaks to find */
	m_noPeaks = keyExistsToInt(optionMap, "num_ccf_peaks", 3);

	/* Max displacements */
	m_maxDisp.first  = keyExistsToInt(optionMap, "max_displacement_x", floor(m_winSize.first / 2) - 1);
	m_maxDisp.second = keyExistsToInt(optionMap, "max_displacement_y", floor(m_winSize.second / 2) - 1);
}


PivOptions::PivOptions(std::string fn)
{
	std::ifstream configFile(fn);
	std::string line, k, v;
	std::unordered_map<std::string, std::string> optionMap;

	while (std::getline(configFile, line)) {
		// Ignore blank lines and comments, make sure there is a colon in the string
		int splitPoint = findColon(line);
		if ( !line.empty() && line[0] != '#' && splitPoint) {
			// Now place the key:values in the map
			k = line.substr(0, splitPoint);
			v = line.substr(splitPoint + 1, line.length());
			optionMap[k] = v;
		}
	}
	configFile.close();
	/* Check for window size */
	m_winSize.first  = keyExistsToInt(optionMap, "interrogation_window_x", 16);
	m_winSize.second = keyExistsToInt(optionMap, "interrogation_window_y", 16);

	/* Check for overlap */
	m_overlap.first   = keyExistsToInt(optionMap, "window_overlap_x", 0);
	m_overlap.second  = keyExistsToInt(optionMap, "window_overlap_y", 0);

	/* Check for number of correlation peaks to find */
	m_noPeaks = keyExistsToInt(optionMap, "num_ccf_peaks", 3);

	/* Max displacements */
	m_maxDisp.first  = keyExistsToInt(optionMap, "max_displacement_x", floor(m_winSize.first / 2) - 1);
	m_maxDisp.second = keyExistsToInt(optionMap, "max_displacement_y", floor(m_winSize.second / 2) - 1);
}

int PivOptions::findColon(const std::string& str)
{
	/* 	findColon
 	 *	returns the location of the first colon in the string */
	int colon = str.find_first_of(":");
	return colon > 0 ? colon : 0;
}

int PivOptions::keyExistsToInt(std::unordered_map<std::string, std::string>& optMap, std::string key, int defaultVal)
{
	/* If the value of the map with key key is an empty string then 
	 * return a default integer otherwise convert the string to an 
	 * integer.
	 *
	 * todo:
	 * 1) Add some checking, if string conversion is unsuccessful return 
	 * 	  the default integer. */
	std::string &entry = optMap[key];
	return !entry.empty() ? std::stoi(entry) : defaultVal;
}

// Destructor
PivOptions::~PivOptions()
{
}

// Getters
int PivOptions::winWidth()
{
	return m_winSize.first;
}

int PivOptions::winHeight()
{
	return m_winSize.second;
}

int PivOptions::olvpHoriz()
{
	return m_overlap.first;
}

int PivOptions::olvpVert()
{
	return m_overlap.second;
}

int PivOptions::numPeaks()
{
	return m_noPeaks;
}

int PivOptions::maxDispX()
{
	return m_maxDisp.first;
}

int PivOptions::maxDispY()
{
	return m_maxDisp.second;
}

std::pair<int, int>& PivOptions::winSize()
{
	return m_winSize;
}

// Setters
void PivOptions::setWinWidth(int x)
{
	m_winSize.first = x;
}

void PivOptions::setWinHeight(int x)
{
	m_winSize.second = x;
}

void PivOptions::setOvlpHoriz(int x)
{
	m_overlap.first = x;
}

void PivOptions::setOvlpVert(int x)
{
	m_overlap.second = x;
}

void PivOptions::setNumPeaks(int n)
{
	m_noPeaks = n;
}

void PivOptions::print()
{
	std::cout << "Ix: " << winWidth() << "\tIy: " << winHeight() << 
		"\nOx: " << olvpHoriz()<< "\tOy: " << olvpVert() << 
		"\nxMax: " << maxDispX() << "\tyMax: " << maxDispY() <<
		"\nNo peaks: " << m_noPeaks << std::endl;
}
