#define CATCH_CONFIG_MAIN
#include "../tests/catch.hpp"

#include <string>
#include "Clap.hpp"

TEST_CASE( "Clap test", "Check constructor"){
	
	SECTION( "No command line arguments") {
		/* Some input data pretending to be some args. Simulate case with
	 	 * no arguments. The only element in argv is program name */
		int argc_mock = 1;
		char *argv_mock[] = {"clap_test"};

		Clap test_clap(argc_mock, argv_mock);

		SECTION( "Number of arguments should be equal to 1") {
			CHECK(test_clap.numArgs() == 1);
		}

		SECTION( "Program name should equal 'clap_test'") {
			CHECK(test_clap.progName() == "clap_test");
		}
	}
// -Wno-write-strings
	SECTION( "Single flag argument" ) {
		int argc_mock = 2;
		char *argv_mock[] = {"clap_test", "-p"};

		Clap test_clap(argc_mock, argv_mock);

		SECTION( "Number of args should equal 2" ) {
			CHECK(test_clap.numArgs() == 2);
		}	

		SECTION( "Has flag '-p' should equal true" ) {
			CHECK(test_Clap.hppasFlag("-p") == true);
		}

		SECTION( "Flags set should have length 1" ) {
			CHECK(test_clap.flagSet().size() == 1);
		}

		SECTION( "First element of flagSet should be '-p'" ) {
			CHECK(test_clap.flagSet().find("-p") != test_clap.flagSet().end());
		}
	}

	SECTION( "Two flag argument" ) {
		int argc_mock = 3;
		char *argv_mock[] = {"clap_test", "-p", "-o"};

		Clap test_clap(argc_mock, argv_mock);

		SECTION( "Number of args should equal 3" ) {
			CHECK(test_clap.numArgs() == 3);
		}	

		SECTION( "Has flag '-o' should equal true" ) {
			CHECK(test_Clap.hppasFlag("-o") == true);
		}

		SECTION( "Flags set should have length 2" ) {
			CHECK(test_clap.flagSet().size() == 2);
		}

		SECTION( "flagSet should contain '-o'" ) {
			CHECK(test_clap.flagSet().find("-o") != test_clap.flagSet().end());
		}
	}

	SECTION( "Flag with option" ) {
		int argc_mock = 8;
		char *argv_mock[] = {"clap_test", "-q", "-o", "file1.dat", "file2.xx", "file3.ff", "-f", "mofo"};

		Clap test_clap(argc_mock, argv_mock);

		SECTION( "Number of args should equal 6" ) {
			CHECK(test_clap.numArgs() == 8);
		}	

		SECTION( "Has flag '-o' should equal true" ) {
			CHECK(test_Clap.hppasFlag("-o") == true);
		}

		SECTION( "Flags set should have length 2" ) {
			CHECK(test_clap.flagSet().size() == 3);
		}

		SECTION( "flagSet should contain '-o'" ) {
			CHECK(test_clap.flagSet().find("-o") != test_clap.flagSet().end());
		}

		SECTION( "flagSet should contain '-f'" ) {
			CHECK(test_clap.flagSet().find("-f") != test_clap.flagSet().end());
		}

		SECTION( "Flag options should have size 1" ) {
			CHECK(test_Clap.hppasParam("-o"));
		}

		SECTION( "Options should have length 3" ) {
			CHECK(test_clap.flagArgs("-o").size() == 3);
		}
		SECTION( "Options should have length 1" ) {
			CHECK(test_clap.flagArgs("-f").size() == 1);
		}

		SECTION( "First -o option should be 'file1.dat'" ) {
			CHECK(test_clap.flagArgs("-o")[0] == "file1.dat");
		}

		SECTION( "First -o option should be 'file3.dat'" ) {
			CHECK(test_clap.flagArgs("-o")[2] == "file3.ff");
		}

		SECTION( "-f option should have 'mofo' as option" ) {
			CHECK(!test_clap.flagArgs("-f").empty());
		}
		
		
		SECTION( "-f option should be 'mofo'" ) {
			CHECK(test_clap.flagArgs("-f")[0] == "mofo");
		}

		SECTION( "-f should have parms" ) {
			CHECK(test_Clap.hppasParam("-f"));
		}

		SECTION( "First -o option should be 'file2.dat'" ) {
			CHECK(test_clap.getFlagsWithArgs()["-o"][1] == "file2.xx");
		}

		SECTION( "First -o option should be 'file2.dat'" ) {
			CHECK(test_clap.getFlagsWithArgs()["-f"][0] == "mofo");
		}

		SECTION( "First -o option should be 'file2.dat'" ) {
			CHECK(test_clap.getFlagsWithArgs()["-q"].empty());
		}
	}
}
