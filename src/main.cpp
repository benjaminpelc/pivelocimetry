#include "ocv_image.h"
#include "matrix2.h"
#include "int_map.h"
#include "config_file.h"
#include "pivoptions.h"
#include "xcorr2.h"
#include "ccf.h"

int main(int argc, char** argv)
{
	// CLI Args
	// std::cout << "argc: " << argc << std::endl;

	// Load a raw images and extract pixel intensity maps
	IntMappable *rawIm1 = new OCVImage("../img/1.bmp"),
				*rawIm2 = new OCVImage("../img/2.bmp");

	// Extract pixel intensity maps
	IntMap i1 = IntMap(rawIm1),
		   i2 = IntMap(rawIm2);

	/* Load options from config file
	 * Enable select config file from command line, failing that, use
	 * a default config file */
	PivOptions analysisOptions = PivOptions(
				ConfigFile::parse("../config/default.cfg")
			);

	// Initialize a CCF to dump the correlation data in
	CCF c = CCF(analysisOptions.get_windowHeight() + 1, analysisOptions.get_windowWidth() + 1);

	XCorr2::xCorr2n(c, i1, i2, 255, 255, analysisOptions.get_windowWidth(), analysisOptions.get_windowHeight());
	std::cout << c;

	/* ToDo:
	 * 1) Calculate grid
	 * 2) Initialize storage for PIV info
	 * 3) Do cross-correlation
	 * 4) Export results */

	// Do some cleaning before leaving
	delete rawIm1;
	delete rawIm2;

	return 0;
}
