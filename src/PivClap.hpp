#ifndef BPPIV_COMMAND_LINE_ARGUMENT_PARSER_H
#define BPPIV_COMMAND_LINE_ARGUMENT_PARSER_H

#include "../lib/Clap.hpp"

class PivClap :
	public Clap
{
	public:
		PivClap(int argc, char** argv);
		~PivClap();

		bool userConfig();
		bool printResults();
		bool writeResults();
		bool viewVectors();
		bool doPostProc();

		std::string writeFile();
		std::string configFile();

		/* Add method that tells you off if the flag specified 
		 * requires an option */

	private:

};


#endif

