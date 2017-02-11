#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "tokenize.hpp"
#include <string>
#include <sstream>
#include <queue>

TEST_CASE("Test Constructor", "[tokenize]"){
	
	//TokenList* list = new TokenList();

	//REQUIRE(list->empty());

}


TEST_CASE("Test createList w/ only spaces", "[tokenize]"){
	
	std::stringstream sim;
	sim << "( " << "+ " << "a " << "( " << "- " << "4 " << ") " << ") ";

	std::queue<std::string> reList = createList(sim);;

	REQUIRE(reList.front() == "(");
	reList.pop();
	REQUIRE(reList.front() == "+");
	reList.pop();	
	REQUIRE(reList.front() == "a");
	reList.pop();
	REQUIRE(reList.front() == "(");
	reList.pop();
	REQUIRE(reList.front() == "-");
	reList.pop();
	REQUIRE(reList.front() == "4");
	reList.pop();
	REQUIRE(reList.front() == ")");
	reList.pop();
	REQUIRE(reList.front() == ")");
}

TEST_CASE("Test createList w/ no spaces", "[tokenize]"){

	std::stringstream sim;
	sim << "(" << "+ " << "a" << "( " << "- " << "4 " << ")" << ")";

	std::queue<std::string> reList = createList(sim);

	REQUIRE(reList.front() == "(");
	reList.pop();
	REQUIRE(reList.front() == "+");
	reList.pop();	
	REQUIRE(reList.front() == "a");
	reList.pop();
	REQUIRE(reList.front() == "(");
	reList.pop();
	REQUIRE(reList.front() == "-");
	reList.pop();
	REQUIRE(reList.front() == "4");
	reList.pop();
	REQUIRE(reList.front() == ")");
	reList.pop();
	REQUIRE(reList.front() == ")");

}
