#ifndef TOKENIZE_HPP
#define TOKENIZE_HPP

#include <string>
#include <queue>
#include <sstream>
#include <vector>
#include <iostream>

//This module should define the C++ types and code 
// required to parse a vtscript program into an AST

//Take in the input file string and "Tokenize" to be in the 
// format that we expect. Return true if successful, false if
// the string cannot be tokenized.
std::queue<std::string> createList(std::istream& input);


typedef struct Node{
	
	//for now, let's just say the data type is a string	
	std::string data;
	
	//will have any number of branches
	std::vector<Node*> branches;

	//point back up to make it easy on me
	Node* top;
	
}Node;


class AST{
	
public:
	
	//default constructor
	AST();

	//default destructor
	~AST();

	//Assemble the AST
	bool assembleAST(std::queue<std::string> tokenList);
	
	//some ways of presenting the data
	bool empty();

private:
	Node* root;
	
	Node* currNode;		

};


#endif // TOKENIZE_HPP
