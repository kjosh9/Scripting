#ifndef TOKENIZE_HPP
#define TOKENIZE_HPP

#include <string>
#include <queue>
#include <sstream>
#include <vector>

//This module should define the C++ types and code 
// required to parse a vtscript program into an AST

//Take in the input file string and "Tokenize" to be in the 
// format that we expect. Return true if successful, false if
// the string cannot be tokenized.
std::queue<std::string> createList(std::stringstream& input);


typedef struct {
	
	//for now, let's just say the data type is a string	
	std::string data;
	std::vector<Node*> branches;
}Node;


class AST{
	
public:
	
	//default constructor
	AST();

	//default destructor
	~AST();

	//Assemble the AST
	bool assembleAST(std::queue<std::string> tokenList);
	
	//some way of presenting the data

private:
	Node* root;
	
	Node* currNode;		

};


#endif // TOKENIZE_HPP
