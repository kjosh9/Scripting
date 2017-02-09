#ifndef TOKENIZE_HPP
#define TOKENIZE_HPP

#include <string>
#include <queue>
#include <sstream>

//do I actually need a class?
class TokenList{


public:
	TokenList();

	bool createList(std::stringstream& input);

	std::queue<std::string> returnList();
	
	bool empty();

private:

	//the actual token list
	std::queue<std::string> data;
	
};



//Take in the input file string and "Tokenize" to be in the 
// format that we expect. Return true if successful, false if
// the string cannot be tokenized.

//This module should define the C++ types and code 
// required to parse a vtscript program into an AST



#endif // TOKENIZE_HPP
