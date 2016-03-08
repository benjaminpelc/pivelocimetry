// main.cpp
// Entry point for Particle Image Velocimetry.
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created: 

#include "DoPiv.hpp"
#include "DoPost.hpp"
#include "Grid.hpp"
#include "GtkImage.hpp"
#include "IntMap.hpp"
#include "PivOptions.hpp"
#include "PivViewGtk.hpp"
#include "cli_args.hpp"

#include <gtkmm.h>
#include <cmath>
#include <memory>

int main(int argc, char **argv) {

	auto ggg = new Gtk::Main(0,0,false);

  // Parse command line arguments
	CliArgs args(argc, argv);

  // If a custom config file is specified, load it. If not, use the default
  // configuration
  auto cfgFilePath =
      std::string("../config/default.cfg");

  if (!args.getConfigFilePath().empty())
    cfgFilePath = args.getConfigFilePath();

  // Load options from config file
  auto analysisOptions = PivOptions(cfgFilePath);

  auto im1FilePath = std::string("../img/1.bmp"),
       im2FilePath = std::string("../img/2.bmp");

  // auto im1FilePath = std::string("../img/A001a.tif"),
  // 	  im2FilePath = std::string("../img/A001b.tif");


  // Load a raw images and extract pixel intensity maps
  std::unique_ptr<IntMappable> rawIm1 = std::make_unique<GtkBufImage>(im1FilePath),
                               rawIm2 = std::make_unique<GtkBufImage>(im2FilePath);

  // Extract pixel intensity maps
  auto i1 = IntMap(rawIm1);
  auto i2 = IntMap(rawIm2);

  // Box images in a pair for easy handling
  IntMap::Pair imPair{&i1, &i2};

  // Create a grid of image coordinates where vectors will be calculated
  auto g = PivEng::Grid(analysisOptions, i1);

  // We have options, images and a grid, now do some PIV
  auto piv = PivEng::DoPiv(analysisOptions, imPair, g);

  // Do some post processing
  if (args.getPostProcessingFlag())
    auto pp = PivEng::DoPost(piv.pointsVector(), g.numX());

  // Check command line args and print to screen/write to file as necessary
  if (args.getViewVectorsFlag())
    PivViewGtk pv(piv.pointsVector());
    // PivView pv(piv.pointsVector());

  // Save vectors to file if an output file is specified
  if (!args.getOutputFilePath().empty())
    piv.write(args.getOutputFilePath());

  // Print results to STDOUT if print flag is selected
  if (args.getPrintResultsFlag())
    piv.print();

  // Clean up
	delete ggg;

  return 0;
}
