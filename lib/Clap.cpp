#include "Clap.hpp"

Clap::Clap(int argc, char** argv) :
	m_flags(),
	m_argc(argc),
	m_argv(argv),
	m_flagArgsMap()
{
	getFlags();
	std::for_each(m_flags.begin(), m_flags.end(), [&](auto &s) {
				this->m_flagArgsMap[s] = this->flagArgs(s);
			});	
}

char** Clap::begin()
{
	return &m_argv[0];
};

char** Clap::end()
{
	return &m_argv[m_argc];
};

std::set<std::string>& Clap::flagSet()
{
	return m_flags;
}

Clap::FlagArgsMap& Clap::getFlagsWithArgs()
{
	return m_flagArgsMap;
}

int Clap::numArgs()
{
	return m_argc;
};

std::string Clap::progName()
{
	return m_argv[0];
};

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

bool Clap::isFlag(const std::string a)
{
	return a[0] == '-';
}
