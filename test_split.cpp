#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "split.hpp"
#include <string>

TEST_CASE("Test split", "[split]"){

	std::string testString = "this is a test string";
	std::string testString2 = "This( is another)test String";
	std::string outputString;
	
	split(testString, outputString);	
	REQUIRE(outputString.compare("this") == 0);

	split(testString, outputString);	
	REQUIRE(outputString.compare("is") == 0);

	split(testString, outputString);	
	REQUIRE(outputString.compare("a") == 0);

	split(testString, outputString);	
	REQUIRE(outputString.compare("test") == 0);

	split(testString, outputString);	
	REQUIRE(outputString.compare("string") == 0);
}

