#ifndef BPPIV_COMMAND_LINE_ARGUMENT_PARSER_H
#define BPPIV_COMMAND_LINE_ARGUMENT_PARSER_H

#include "../lib/Clap.hpp"

class PivClap :
	public Clap
{
	public:
		PivClap(int argc, char** argv);

		bool userConfig()   { return hasParam("-c"); };
		bool printResults() { return hasFlag("-p"); };
		bool writeResults() { return hasParam("-o"); };

		std::string writeFile()  { return getParam("-o"); }
		std::string configFile() { return getParam("-c"); }

		/* Add method that tells you off if the flag specified 
		 * requires an option */

	private:

};

PivClap::PivClap(int argc, char** argv) : Clap(argc, argv) {}

#endif

