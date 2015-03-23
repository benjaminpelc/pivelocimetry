#ifndef BPPIV_COMMAND_LINE_ARGUMENT_PARSER_H
#define BPPIV_COMMAND_LINE_ARGUMENT_PARSER_H

#include "../lib/Clap.hpp"

class PivClap :
	public Clap
{
	public:
		PivClap(int argc, char** argv);

		bool printResults() { return hasFlag("-p"); };

		/* Want a method that tells you off if the flag specified 
		 * requires an option */
		

	private:

};

PivClap::PivClap(int argc, char** argv) : Clap(argc, argv)
{
}

#endif

