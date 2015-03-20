#include "config_file.h"
#include "do_piv.h"
#include "grid.h"
#include "int_map.h"
#include "ocv_image.h"
#include "pivoptions.h"
#include "peak.h"
#include "bppiv_clap.h"
#include <memory>

int main(int argc, char** argv)
{
	/* Arguments 
	 * Do all parsing up front and raise exceptions if something is wrong
	 * and end the program.
	 *
	 * No point doing any PIV if say write output to file is selected but no
	 * filename is provided */
	PivClap clArgs(argc, argv);

	// return 0;

	/* Load a raw images and extract pixel intensity maps */
	// std::unique_ptr<IntMappable> rawIm1(new OCVImage("../img/1.bmp")),
	// 							 rawIm2(new OCVImage("../img/2.bmp"));
	std::unique_ptr<IntMappable> rawIm1 = std::make_unique<OCVImage>("../img/1.bmp"),
								 rawIm2 = std::make_unique<OCVImage>("../img/2.bmp");

	// Extract pixel intensity maps
	// std::unique_ptr<IntMap> i1(new IntMap(rawIm1)),
	IntMap::Uptr i1 = std::make_unique<IntMap>(rawIm1),
	             i2 = std::make_unique<IntMap>(rawIm2);

	/* Let us try and box the images into a pair
	 * In effect, a pair of memory addresses to the two images?? */
	IntMap::Pair imPair{i1, i2};

	/* Load options from config file
	 * Enable select config file from command line, failing that, use
	 * a default config file 
	 * ---
	 *  Clean this up so analysisOptions takes just a filename as argument */
	PivOptions::Uptr analysisOptions = std::make_unique<PivOptions>(
				ConfigFile::parse("../config/default.cfg")
			);	

	// analysisOptions->print();

	/* Create a grid */
	Grid::Uptr g = std::make_unique<Grid>(*analysisOptions, *i1);
	
	// std::cout << g->coordsVec().begin()->first << std::endl;
	// std::cout << g->coordsVec().begin()->second<< std::endl;

	/* We have options, images and a grid, now do some PIV */
	DoPiv p = DoPiv(*analysisOptions, imPair, g);
	
	/* if -o flag is supplied with a filename, write to it */
	if (clArgs.hasParam("-o")) p.write(clArgs.getParam("-o"));
	// p.write("../my_shiny_vectors.txt");

	/* if -p is passed at command line print vector results to screen when 
	 * all is done */
	if (clArgs.printResults()) p.print();

	return 0;
}
