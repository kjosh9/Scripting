#include "interpreter.hpp"


Interpreter::Interpreter(){
	syntaxTree = new AST();
}

bool Interpreter::parse(std::istream & expression) noexcept
{
	tokenList = createList(expression);

	return true;
}

Expression Interpreter::eval(){

	
	
	return result;	

}



