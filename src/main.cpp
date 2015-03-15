// #include <iostream>
#include <memory>

#include "ocv_image.h"
#include "int_map.h"
#include "config_file.h"
#include "pivoptions.h"
#include "xcorr2.h"
#include "ccf.h"
#include "grid.h"

int main(int argc, char** argv)
{
	// CLI Args
	// std::cout << "argc: " << argc << std::endl;

	// Load a raw images and extract pixel intensity maps
	std::shared_ptr<IntMappable> rawIm1 = std::make_shared<OCVImage>("../img/1.bmp"),
								 rawIm2 = std::make_shared<OCVImage>("../img/2.bmp");

	// Extract pixel intensity maps
	std::shared_ptr<IntMap> i1 = std::make_shared<IntMap>(rawIm1),
		                    i2 = std::make_shared<IntMap>(rawIm2);

	/* Load options from config file
	 * Enable select config file from command line, failing that, use
	 * a default config file */
	// PivOptions analysisOptions = PivOptions(
	// 			ConfigFile::parse("../config/default.cfg")
	// 		);
	std::shared_ptr<PivOptions> analysisOptions = std::make_shared<PivOptions>(
				ConfigFile::parse("../config/default.cfg")
			);	

	// std::shared_ptr<Grid> grid;
	std::shared_ptr<Grid> grid = std::make_shared<Grid>(analysisOptions, i1);

	// Initialize a CCF to dump the correlation data in
	std::shared_ptr<CCF> c = std::make_shared<CCF>(
				analysisOptions->get_windowHeight() + 1, analysisOptions->get_windowWidth() + 1
			);
    //
	XCorr2::xCorr2n(c, i1, i2, 255, 255,
				analysisOptions->get_windowWidth(), analysisOptions->get_windowHeight()
			);

	std::cout << *c;

	/* ToDo:
	 * 1) Calculate grid
	 * 2) Initialize storage for PIV info
	 * 3) Do cross-correlation
	 * 4) Find peaks in correlation function
	 * 5) Calculate sub-pixel displacements for peaks
	 * 6) Export results */

	return 0;
}
