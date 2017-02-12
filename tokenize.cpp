#include "tokenize.hpp"


// (+ a ( - 4 ))
// "(", "+", "a", "(", "-", "4", ")", ")"
std::queue<std::string> createList(std::stringstream& input){
	
	char c;
	std::queue<std::string> data;
	while(!input.eof()){
		std::string token;
		input.get(c);	
		
		if(c != ' '){
			token = c;	
			data.push(token);
		}
		//test here if c is a number
	}
	return data;
}


AST::AST(){}

AST::~AST(){}

bool AST::assembleAST(std::queue<std::string> tokenList){
	
	//while(!tokenList.empty()){
	//	if(		

	//}
}




