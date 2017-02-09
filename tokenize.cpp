#include "tokenize.hpp"


//default constructor
TokenList::TokenList(){}

std::queue<std::string> TokenList::returnList(){
	return data;
}

bool TokenList::empty(){
	if(data.empty())
		return true;
	else 
		return false;
}


// (+ a ( - 4 ))
// "(", "+", "a", "(", "-", "4", ")", ")"
bool TokenList::createList(std::stringstream& input){
	
	char c;
	while(!input.eof()){
		std::string token;
		input.get(c);	
		
		if(c != ' '){
			token = c;	
			data.push(token);
		}
		//test here if c is a number
	}
	return true;
}


