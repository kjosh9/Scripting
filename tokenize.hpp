#ifndef TOKENIZE_HPP
#define TOKENIZE_HPP

<<<<<<< HEAD
#include <string>
#include <queue>
#include <sstream>

//do I actually need a class?
class TokenList{


public:
	TokenList();

	bool createList(std::sstream);

	std::queue returnList();
	

private:

	//the actual token list
	std::queue<std::string> data;
	
};



//Take in the input file string and "Tokenize" to be in the 
// format that we expect. Return true if successful, false if
// the string cannot be tokenized.
=======
//This module should define the C++ types and code 
// required to parse a vtscript program into an AST




>>>>>>> 8a3f56a4452725e8e9899d5e9b3cb6c806b2789b


#endif // TOKENIZE_HPP
