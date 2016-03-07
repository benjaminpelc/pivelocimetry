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

  /* Parse command line arguments */
  // const auto clArgs = PivClap(argc, argv);

	CliArgs args(argc, argv);

  /* Check command line args for 'c' flag and a config file path */
  auto cfgFilePath =
      std::string("/home/ben/Dropbox/Development/C++/BPPIV/config/default.cfg");

	// if (clArgs.userConfig())
  //   cfgFilePath = clArgs.configFile();

  /* Load options from config file */
  auto analysisOptions = PivOptions(cfgFilePath);

  // auto im1FilePath =
  //     std::string("/home/ben/Dropbox/Development/C++/BPPIV/img/1.bmp"),
  //      im2FilePath =
  //          std::string("/home/ben/Dropbox/Development/C++/BPPIV/img/2.bmp");

  auto im1FilePath =
  std::string("/home/ben/Dropbox/Development/C++/BPPIV/img/A001a.tif"),
  	   im2FilePath =
  std::string("/home/ben/Dropbox/Development/C++/BPPIV/img/A001b.tif");

  /* Load a raw images and extract pixel intensity maps */
  std::unique_ptr<IntMappable> rawIm1 = std::make_unique<GtkBufImage>(im1FilePath),
                               rawIm2 = std::make_unique<GtkBufImage>(im2FilePath);

  /* Extract pixel intensity maps */
  auto i1 = IntMap(rawIm1);
  auto i2 = IntMap(rawIm2);

  /* Box images in a pair for easy handling */
  IntMap::Pair imPair{&i1, &i2};

  /* Create a grid */
  auto g = PivEng::Grid(analysisOptions, i1);

  /* We have options, images and a grid, now do some PIV */
  auto piv = PivEng::DoPiv(analysisOptions, imPair, g);

  /* Do some post processing */
  if (args.getPostProcessingFlag())
    auto pp = PivEng::DoPost(piv.pointsVector(), g.numX());

  /* Check command line args and print to screen/write to file as necessary */
  if (args.getViewVectorsFlag())
    PivViewGtk pv(piv.pointsVector());
    // PivView pv(piv.pointsVector());

  if (!args.getOutputFilePath().empty())
    piv.write(args.getOutputFilePath());

  if (args.getPrintResultsFlag())
    piv.print();

	delete ggg;
  return 0;
}
