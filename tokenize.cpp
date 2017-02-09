#include "tokenize.hpp"



// (+ a ( - 4 ))
// "(", "+", "a", "(", "-", "4", ")", ")"

bool TokenList::createList(std::sstream input){

	while(!input.eof()){
		input >> std::skipws >> ;
	}
}


