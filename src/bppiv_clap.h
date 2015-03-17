#ifndef BPPIV_COMMAND_LINE_ARGUMENT_PARSER_H
#define BPPIV_COMMAND_LINE_ARGUMENT_PARSER_H

#include "../lib/clap.h"

class PivClap :
	public Clap
{
	public:
		PivClap(int argc, char** argv);

		bool printResults() { return hasFlag("-p"); };

	private:

};

PivClap::PivClap(int argc, char** argv) : 
	Clap(argc, argv)
{
}

#endif

