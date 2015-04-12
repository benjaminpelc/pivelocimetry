#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/find_peaks.hpp"

using namespace PivEng;

TEST_CASE( "PivEng::find_ccf_peaks" ) {

	auto max_disp = 7;
	CCF test_ccf(17, 17);	
	Peak::PeaksVec peaks_vector(3);

	test_ccf.setElem(2, 4, 0.998);
	test_ccf.setElem(2, 3, 0.940);
	test_ccf.setElem(2, 5, 0.136);
	test_ccf.setElem(16, 8, 0.805);
	test_ccf.setElem(1, 4, 0.0972);
	test_ccf.setElem(3, 4, 0.082);

	test_ccf.setElem(5, 14, 0.810);
	test_ccf.setElem(13, 9, 0.321);

	find_ccf_peaks(peaks_vector, test_ccf, max_disp);

	// test_ccf.findPeaks(peaks_vector, max_disp);

	Peak p1 = peaks_vector[0];
	Peak p2 = peaks_vector[1];
	Peak p3 = peaks_vector[2];

	SECTION( "First peak should be 0.998" ) {
		CHECK(p1.get_value() == 0.998 );
	}

	SECTION( "First peak should have coords (i, j) = (4, 2)" ) {
		CHECK(p1.get_i() == 4);
		CHECK(p1.get_j() == 2);
	}

	SECTION( "Second peak should be 0.810" ) {
		CHECK(p2.get_value() == 0.810 );
	}

	SECTION( "Second peak should have coords (i, j) = (14, 5)" ) {
		CHECK(p2.get_i() == 14);
		CHECK(p2.get_j() == 5);
	}

	SECTION( "Third peak should be 0.321" ) {
		CHECK(p3.get_value() == 0.321 );
	}

	SECTION( "Third peak should have coords (i, j) = (9, 13)" ) {
		CHECK(p3.get_i() == 9);
		CHECK(p3.get_j() == 13);
	}


	// SECTION( "Second peak should have coords (i, j) = (14, 5)" ) {
	// 	CHECK(p2.get_i() == 14);
	// 	CHECK(p2.get_j() == 5);
	// }
    //

}
