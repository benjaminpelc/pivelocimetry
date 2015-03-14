#include <fstream>
#include <iostream>
#include <map>
#include "src/config_file.h"
#include "src/pivoptions.h"

int main(int argc, char** argv)
{
	// std::map<std::string, std::string> settings = ConfigFile::parse("./default.cfg");
	
	PivOptions po2 = PivOptions(
			ConfigFile::parse("./default.cfg")
			);

	po2.print();

	return 0;
}
