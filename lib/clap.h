#ifndef COMMAND_LINE_ARGUMENT_PARSER_H
#define COMMAND_LINE_ARGUMENT_PARSER_H

#include <iostream>
#include <algorithm>
#include <string>
#include <set>

class Clap
{
	public:
		typedef std::map<std::string, std::vector<std::string> > FlagArgsMap;
		
		Clap(int argc, char** argv);
		~Clap() {};

		char** begin() { return &m_argv[0]; };
		char** end() { return &m_argv[m_argc]; };
	
		bool hasFlag(const std::string flag);
		bool hasParam(const std::string flag);

		int numArgs() { return m_argc; };
		std::string progName() { return m_argv[0]; };

		std::string getParam(const std::string flag);

		std::set<std::string>& flagSet();
		std::vector<std::string> flagArgs(const std::string flag);

		FlagArgsMap& getFlagsWithArgs();
		std::set<std::string> m_flags;

	private:
		int m_argc;
		char** m_argv;

		void getFlags();
		static bool isFlag(const std::string a) { return a[0] == '-'; };

		FlagArgsMap m_flagArgsMap;

};

Clap::Clap(int argc, char** argv) :
	m_argc(argc),
	m_argv(argv),
	m_flags(),
	m_flagArgsMap()
{
	getFlags();
	std::for_each(m_flags.begin(), m_flags.end(), [&](auto &s) {
				this->m_flagArgsMap[s] = this->flagArgs(s);
			});	
}

std::set<std::string>& Clap::flagSet()
{
	return m_flags;
}

Clap::FlagArgsMap& Clap::getFlagsWithArgs()
{
	return m_flagArgsMap;
}

std::vector<std::string> Clap::flagArgs(const std::string flag)
{
	std::vector<std::string> flagArgsVec;
	
	auto ittr = std::find(begin(), end(), flag) + 1;

	std::find_if(ittr, end(), [&flagArgsVec](auto s) { 
			if (isFlag(s)) return true; 
			else flagArgsVec.push_back(s); 
			return false; 
		});
	
	return flagArgsVec;
}

void Clap::getFlags() {
	std::for_each(begin(), end(), [&](auto &a) {
				if (isFlag(a)) m_flags.insert(a);
			});
}

bool Clap::hasFlag(const std::string flag)
{
	/* Returns true if args contain charFlag */
	return std::find(begin(), end(), flag) != end();
}

bool Clap::hasParam(const std::string flag)
{
	return std::adjacent_find(begin(), end(), [&flag](auto &s1, auto &s2) {
				return s1 == flag && s2[0] != '-';
			}) != end();
}

std::string Clap::getParam(const std::string flag)
{
	/* adjacent_find returns a pointer to the first of two elements that meet 
	 * the condition given by the lambda, in this case that the second string 
	 * does not have '-' as its first character. 
	 *
	 * To return the second of the adjacent elements, advance the pointer
	 * by one 
	 *
	 * Of course, we first need to check if the flag is present with an 
	 * accompanying param. If no, return empty string */
	if (hasParam(flag)) {
		return *(std::adjacent_find(begin(), end(), [&flag](auto &s1, auto &s2) {
						return s1 == flag && s2[0] != '-';
					}) + 1);
	}
	return "";
}



#endif
