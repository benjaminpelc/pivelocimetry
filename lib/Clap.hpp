#ifndef COMMAND_LINE_ARGUMENT_PARSER_H
#define COMMAND_LINE_ARGUMENT_PARSER_H

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <set>
#include <string>

class Clap
{
	public:
		typedef std::unordered_map<std::string, std::vector<std::string> > FlagArgsMap;
		
		Clap(int argc, char** argv);
		~Clap() {};

		char** begin() const;
		char** end() const;
	
		bool hasFlag(const std::string flag) const;
		bool hasParam(const std::string flag) const;

		int numArgs() const;
		std::string progName() const;

		std::string getParam(const std::string flag) const;

		std::set<std::string>& flagSet();
		std::vector<std::string> flagArgs(const std::string flag) const;

		FlagArgsMap& getFlagsWithArgs();
		std::set<std::string> m_flags;

	private:
		int m_argc;
		char** m_argv;

		void getFlags();
		static bool isFlag(const std::string a);

		FlagArgsMap m_flagArgsMap;

};

#endif
