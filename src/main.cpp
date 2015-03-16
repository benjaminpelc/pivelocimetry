#include "config_file.h"
#include "do_piv.h"
#include "grid.h"
#include "int_map.h"
#include "ocv_image.h"
#include "pivoptions.h"
#include "peak.h"
#include <memory>

int main(int argc, char** argv)
{
	// CLI Args
	// std::cout << "argc: " << argc << std::endl;

	/* Load a raw images and extract pixel intensity maps
	 * ToDo:
	 * 1) Create object containing a pair of IntMaps instantiated with a pair of filename
	 *    arguments. */
	std::unique_ptr<IntMappable> rawIm1(new OCVImage("../img/1.bmp")),
								 rawIm2(new OCVImage("../img/2.bmp"));

	// Extract pixel intensity maps
	// std::unique_ptr<IntMap> i1(new IntMap(rawIm1)),
	IntMap::Uptr i1(new IntMap(rawIm1)),
	             i2(new IntMap(rawIm2));

	/* Let us try and box the images into a pair
	 * In effect, a pair of memory addresses to the two images?? */
	std::pair<IntMap::Uptr&, IntMap::Uptr&> imagePair{i1, i2};

	/* Load options from config file
	 * Enable select config file from command line, failing that, use
	 * a default config file 
	 * ---
	 *  Clean this up so analysisOptions takes just a filename as argument */
	PivOptions::Uptr analysisOptions(new PivOptions(
				ConfigFile::parse("../config/default.cfg")
			));	

	/* Create a grid */
	Grid::Uptr g( new Grid(analysisOptions, i1));
	
	// std::cout << g->get_coordPairsVector().begin()->first << std::endl;
	// std::cout << g->get_coordPairsVector().begin()->second<< std::endl;

	/* We have options, images and a grid, now do some PIV */
	DoPiv p = DoPiv(analysisOptions, i1, i2, g);

	/* ToDo:
	 * 4) Find peaks in correlation function
	 * 5) Calculate sub-pixel displacements for peaks
	 * 6) Export results */

	return 0;
}
