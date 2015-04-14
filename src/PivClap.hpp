#ifndef BPPIV_COMMAND_LINE_ARGUMENT_PARSER_H
#define BPPIV_COMMAND_LINE_ARGUMENT_PARSER_H

#include "../lib/Clap.hpp"

class PivClap : public Clap {
public:
  PivClap(int argc, char **argv);
  ~PivClap();

  bool userConfig() const;
  bool printResults() const;
  bool writeResults() const;
  bool viewVectors() const;
  bool doPostProc() const;

  std::string writeFile() const;
  std::string configFile() const;

  /* Add method that tells you off if the flag specified
   * requires an option */

private:
};

#endif
