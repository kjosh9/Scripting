#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "split.hpp"
#include <string>
#include <iostream>

TEST_CASE("Test split simple string", "[split]"){

	std::string testString = "this is a test string";
	std::string testString2 = "This( is another)test String";
	std::string outputString;

	REQUIRE(split(testString, outputString) == true);	
	REQUIRE(outputString.compare("this") == 0);

	split(testString, outputString);
	REQUIRE(outputString.compare("is") == 0);

	split(testString, outputString);
	REQUIRE(outputString.compare("a") == 0);

	split(testString, outputString);	
	REQUIRE(outputString.compare("test") == 0);

	split(testString, outputString);	
	REQUIRE(testString.compare("string") == 0);
}

TEST_CASE("Test split complex string", "[split]"){

	std::string testString = "This( is another)test String";
	std::string outputString;

	REQUIRE(split(testString, outputString) == true);	
	split(testString, outputString);
	REQUIRE(outputString.compare("This") == 0);

	split(testString, outputString);
	REQUIRE(outputString.compare("is") == 0);

	split(testString, outputString);
	REQUIRE(outputString.compare("another") == 0);

	split(testString, outputString);	
	REQUIRE(outputString.compare("test") == 0);

	split(testString, outputString);	
	REQUIRE(testString.compare("String") == 0);

}

TEST_CASE("Test split with a typical Expression", "[split]"){

	std::string testString = "(a + 1)";
	std::string outputString;

	REQUIRE(split(testString, outputString) == true);	
	split(testString, outputString);
	REQUIRE(outputString.compare("a") == 0);

	split(testString, outputString);
	REQUIRE(outputString.compare("+") == 0);

	split(testString, outputString);
	REQUIRE(outputString.compare("1") == 0);

}






