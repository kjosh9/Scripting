#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "tokenize.hpp"
#include <string>
#include <istream>
#include <queue>
#include <iostream>

TEST_CASE("Test Constructor", "[AST]"){

	AST* tree = new AST();
	REQUIRE(tree->empty());

}


TEST_CASE("Test createList w/ only spaces", "[tokenize]"){
	
	std::ifstream sim ("test.vts");

	bool success;
	std::queue<std::string> reList = createList(sim, success);	

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
	reList.pop();
	REQUIRE(reList.empty());

	//REQUIRE(success == true);
}

TEST_CASE("Test createList w/ different input", "[tokenize]"){

	std::istringstream sim;
	
	sim.str("(+ 1 2)");
	
	bool success;
	std::queue<std::string> reList = createList(sim, success);

	REQUIRE(reList.front() == "(");
	reList.pop();
	REQUIRE(reList.front() == "+");
	reList.pop();	
	REQUIRE(reList.front() == "1");
	reList.pop();
	REQUIRE(reList.front() == "2");
	reList.pop();
	REQUIRE(reList.front() == ")");
	reList.pop();
	/*REQUIRE(reList.front() == "4");
	reList.pop();
	REQUIRE(reList.front() == ")");
	reList.pop();
	REQUIRE(reList.front() == ")");
	reList.pop();*/
	REQUIRE(reList.empty());

	REQUIRE(success == true);
}

TEST_CASE("Test createList w/ just pi", "[tokenize]"){

	AST* tree = new AST();
	std::istringstream sim;
	
	sim.str("(pi)");
	
	bool success;
	std::queue<std::string> reList = createList(sim, success);

	REQUIRE(reList.front() == "(");
	reList.pop();
	REQUIRE(reList.front() == "pi");
	reList.pop();
	REQUIRE(reList.front() == ")");
	reList.pop();
	REQUIRE(reList.empty());

	REQUIRE(success == true);

	tree->assembleAST(reList);
	
	Node* checkRoot = tree->getRoot();

	REQUIRE(checkRoot->atomType == aSymbol);
	REQUIRE(checkRoot->symbolValue.compare("pi") == 0);
	
}

TEST_CASE("Test createList w/ just True", "[tokenize]"){

	AST* tree = new AST();
	std::istringstream sim;
	
	sim.str("(True)");
	
	bool success;
	std::queue<std::string> reList = createList(sim, success);

	REQUIRE(reList.front() == "(");
	reList.pop();
	REQUIRE(reList.front() == "True");
	reList.pop();
	REQUIRE(reList.front() == ")");
	reList.pop();
	REQUIRE(reList.empty());

	REQUIRE(success == true);

	tree->assembleAST(reList);
	
	Node* checkRoot = tree->getRoot();

	REQUIRE(checkRoot->atomType == aSymbol);
	REQUIRE(checkRoot->symbolValue.compare("True") == 0);
	
}

TEST_CASE("Test assembleAST", "[AST]"){

	AST* tree = new AST();
	
	std::ifstream sim ("test.vts");

	bool success;

	std::queue<std::string> reList = createList(sim, success);	
	tree->assembleAST(reList);

	REQUIRE(tree->empty() == false);
	
	Node* checkRoot = tree->getRoot();

	REQUIRE(checkRoot->atomType == aSymbol);
	REQUIRE(checkRoot->symbolValue.compare("+") == 0);
}
















