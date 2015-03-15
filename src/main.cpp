// #include <iostream>
#include <memory>

#include "ocv_image.h"
#include "int_map.h"
#include "config_file.h"
#include "pivoptions.h"
#include "xcorr2.h"
#include "ccf.h"
#include "grid.h"
#include "piv_point.h"

int main(int argc, char** argv)
{
	// CLI Args
	// std::cout << "argc: " << argc << std::endl;

	// Load a raw images and extract pixel intensity maps
	std::unique_ptr<IntMappable> rawIm1(new OCVImage("../img/1.bmp")),
								 rawIm2(new OCVImage("../img/2.bmp"));

	// Extract pixel intensity maps
	std::unique_ptr<IntMap> i1(new IntMap(rawIm1)),
		                    i2(new IntMap(rawIm2));

	/* Load options from config file
	 * Enable select config file from command line, failing that, use
	 * a default config file */
	std::unique_ptr<PivOptions> analysisOptions(new PivOptions(
				ConfigFile::parse("../config/default.cfg")
			));	

	// Create a grid
	std::unique_ptr<Grid> grid( new Grid(analysisOptions, i1));

	/* Create a PIV point at a grid point */
	PIVPoint p = PIVPoint(255, 255, analysisOptions);

	std::cout << *p.get_ccf() << std::endl;	

	// Initialize a CCF to dump the correlation data in
	// std::unique_ptr<CCF> c(new CCF(
	// 			analysisOptions->get_windowHeight() + 1, analysisOptions->get_windowWidth() + 1
	// 		));
    //
	XCorr2::xCorr2n(p.get_ccf(), i1, i2, 255, 255,
				analysisOptions->get_windowWidth(), analysisOptions->get_windowHeight()
			);
    //
	// std::cout << *c;
	std::cout << *p.get_ccf() << std::endl;

	/* ToDo:
	 * 1) Calculate grid
	 * 2) Initialize storage for PIV info
	 * 3) Do cross-correlation
	 * 4) Find peaks in correlation function
	 * 5) Calculate sub-pixel displacements for peaks
	 * 6) Export results */

	return 0;
}
