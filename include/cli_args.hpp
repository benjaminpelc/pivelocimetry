#ifndef CLI_ARGS_H
#define CLI_ARGS_H

#include <tclap/CmdLine.h>

class CliArgs {
  public:
    CliArgs(int argc, char **argv);
    ~CliArgs();

    // Return the state of the print results flag.
    //  -- true : print results to console
    //  -- false : no output to console.
    bool getPrintResultsFlag() const;

    // Return the value of postProcessingFlag
    //  -- true : do post processing
    //  -- false : do no post processing
    bool getPostProcessingFlag() const;

    // Return the value of postProcessingFlag
    //  -- true : show final calculated vectors
    //  -- false : do not show any vectors
    bool getViewVectorsFlag() const;

    // Return the filename if an output file is selected
    std::string getOutputFilePath() const;

    // Return the filename if a custom config file is selected
    std::string getConfigFilePath() const;

  private:
    TCLAP::CmdLine cli;
    bool printResultsFlag;
    bool postProcessingFlag;
    bool viewVectorsFlag;
    std::string outputFilePath;
    std::string configFilePath;

};

#endif
