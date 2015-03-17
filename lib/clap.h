#ifndef COMMAND_LINE_ARGUMENT_PARSER_H
#define COMMAND_LINE_ARGUMENT_PARSER_H

#include <iostream>
#include <algorithm>

class Clap
{
	public:
		Clap(int argc, char** argv);
		~Clap() {};

		char** begin() { return &_argv[1]; };
		char** end() { return &_argv[_argc]; };
	
		bool hasFlag(const std::string flagString);
		bool hasParam(const std::string flagString);

	private:
		int _argc;
		char** _argv;
};

Clap::Clap(int argc, char** argv) :
	_argc(argc),
	_argv(argv)
{
	// std::cout << "Hello, in Clap" << std::endl;
	// std::for_each(begin(), end(), [](auto &a){ std::cout << a << std::endl; }  );
}

bool Clap::hasFlag(const std::string flagString)
{
	/* Returns true if args contain charFlag */
	return std::find(begin(), end(), flagString) != end();
}

bool Clap::hasParam(const std::string flagString)
{
	return std::adjacent_find(begin(), end(), [&flagString](auto &s1, auto &s2) {
				return s1 == flagString && s2[0] != '-';
			}) != end();
}



#endif
