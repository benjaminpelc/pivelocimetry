#include "cli_args.hpp"

CliArgs::CliArgs(int argc, char** argv) : cli("PIVelocimetry", ' ', "0.1") {

    // Print results on screen flag
    TCLAP::SwitchArg printResults(
        "p", "print-results",
        "Print the vector results to the console.",
        false);

    // Do post processing flag
    TCLAP::SwitchArg postProcessing(
        "s", "post-processing",
        "Remove spurious vectors and replace with interpolated vectors.",
        false);

    // Display vectors graphically
    TCLAP::SwitchArg viewVectors(
        "v", "view-vectors",
        "Display the calculated vectors graphically.",
        false);

    // Output file CLI flag
    TCLAP::ValueArg<std::string> outFile(
        "o", "output-file",
        "File to save PIV vectors to. If this flag is not specified the results are not saved.",
        false, "", "string");

    // Specify a configuration file
    TCLAP::ValueArg<std::string> configFile(
        "c", "config-file",
        "Specify the configuration file. If no file is specified default configuration is used.",
        false, "", "string");

    cli.add(printResults);
    cli.add(postProcessing);
    cli.add(viewVectors);
    cli.add(outFile);
    cli.add(configFile);

    // Parse the actual command line arguments.
    cli.parse(argc, argv);

    // Collect the values of all the command line arguments and set class
    // member variables to these.
    printResultsFlag = printResults.getValue();
    postProcessingFlag = postProcessing.getValue();
    viewVectorsFlag = viewVectors.getValue();
    outputFilePath = outFile.getValue();
    configFilePath = configFile.getValue();
}

CliArgs::~CliArgs() {}

bool CliArgs::getPrintResultsFlag() const {
  return printResultsFlag;
}

bool CliArgs::getPostProcessingFlag() const {
  return postProcessingFlag;
}

bool CliArgs::getViewVectorsFlag() const {
  return viewVectorsFlag;
}

std::string CliArgs::getOutputFilePath() const {
  return outputFilePath;
}

std::string CliArgs::getConfigFilePath() const {
  return configFilePath;
}
