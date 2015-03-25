#include "DoPiv.hpp"
#include "Grid.hpp"
#include "IntMap.hpp"
#include "OcvImage.hpp"
#include "PivClap.hpp"
#include "PivOptions.hpp"
#include <cmath>
#include <memory>
#include <SFML/Graphics.hpp>

int main(int argc, char** argv)
{


	/* Parse command line arguments */ 
	auto clArgs = PivClap(argc, argv);

	/* Load options from config file */
	auto analysisOptions = std::make_unique<PivOptions>("../config/default.cfg");

	/* Load a raw images and extract pixel intensity maps */
	std::unique_ptr<IntMappable> rawIm1 = std::make_unique<OCVImage>("../img/1.bmp"),
								 rawIm2 = std::make_unique<OCVImage>("../img/2.bmp");

	/* Extract pixel intensity maps */
	IntMap::Uptr i1 = std::make_unique<IntMap>(rawIm1),
	             i2 = std::make_unique<IntMap>(rawIm2);

	/* Box images in a pair for easy handling */
	IntMap::Pair imPair{i1, i2};

	/* Create a grid */
	PivEng::Grid::Uptr g = std::make_unique<PivEng::Grid>(*analysisOptions, *i1);

	/* We have options, images and a grid, now do some PIV */
	auto piv = PivEng::DoPiv(*analysisOptions, imPair, *g);

	/* PivView pv(piv.pointsVector()); */
	
	/* Check command line args and print to screen/write to file as necessary */
	if (clArgs.hasParam("-o")) piv.write(clArgs.getParam("-o"));
	if (clArgs.printResults()) piv.print();

	return 0;
}
