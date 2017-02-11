#ifndef TOKENIZE_HPP
#define TOKENIZE_HPP

#include <string>
#include <queue>
#include <sstream>

//This module should define the C++ types and code 
// required to parse a vtscript program into an AST

//Take in the input file string and "Tokenize" to be in the 
// format that we expect. Return true if successful, false if
// the string cannot be tokenized.
std::queue<std::string> createList(std::stringstream& input);


typedef struct {
	 

}Node;


class AST{
	
public:
	
	//default constructor
	AST();

	//

private:
	Node root;		

};


#endif // TOKENIZE_HPP
