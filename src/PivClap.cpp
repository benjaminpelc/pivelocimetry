#include "PivClap.hpp"

PivClap::PivClap(int argc, char **argv) : Clap(argc, argv) {}

bool PivClap::userConfig() const { return hasParam("-c"); }

bool PivClap::printResults() const { return hasFlag("-p"); }

bool PivClap::doPostProc() const { return hasFlag("-s"); }

bool PivClap::writeResults() const { return hasParam("-o"); }

bool PivClap::viewVectors() const { return hasFlag("-v"); }

std::string PivClap::writeFile() const { return getParam("-o"); }

std::string PivClap::configFile() const { return getParam("-c"); }

PivClap::~PivClap() {}
