#include "lib/jsoncpp/json/json.h"
#include <fstream>
#include <iostream>
#include <map>

/*
 *	findColon
 *	returns the location of the first colon in the string
 */
int findColon(const std::string& str)
{
	int colon = str.find_first_of(":");
	return colon > 0 ? colon : 0;
}

std::map<std::string, std::string> parseConfigFile(const std::string fn)
{
	std::ifstream configFile(fn);
	std::string line, k, v;
	std::map<std::string, std::string> keyValues;

	while (std::getline(configFile, line))
	{
		// Ignore blank lines and comments, make sure there is a colon in the string
		int splitPoint = findColon(line);
		if ( !line.empty() && line[0] != '#' && splitPoint)
		{
			// Now place the key:values in the map
			k = line.substr(0, splitPoint);
			v = line.substr(splitPoint + 1, line.length());
			keyValues[k] = v;
		}
	}
	configFile.close();
	return keyValues;
}

int main(int argc, char** argv)
{
	std::map<std::string, std::string> settings = parseConfigFile("./default.cfg");
	if ( !settings["window_overlap_x"].empty() )
	{
		std::cout << "overlapX: " << settings["window_overlap_x"] << std::endl;
	}

	return 0;
}
