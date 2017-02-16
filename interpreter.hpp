#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "interpreter_semantic_error.hpp"
#include "expression.hpp"
#include "tokenize.hpp"
#include "environment.hpp"

#include <string>
#include <queue>
#include <istream>
#include <vector>
#include <math.h>

class Interpreter{

public:

	// Default construct an Interpreter with the default environment and an empty AST
	Interpreter();

	// Given a vtscript program as a std::istream, attempt to parse into an internal AST
	// return true on success, false on failure
	bool parse(std::istream & expression) noexcept;

	// Evaluate the current AST and return the resulting Expression
	// throws InterpreterSemanticError if a semantic error is encountered
	// the exception message string should document the nature of the semantic error
	Expression eval();

	//recursive function to be used with eval()
	Expression evaluate(Node* nodie);

	//worker function to form expressions
	std::vector<Expression*> formExpression(Node* currNode);

	//this will tell me if all the children of a node are leaves
	bool solvableExpression(Node* currNode, int* branchNo);

private:

	AST* syntaxTree;

	//will I need this?
	std::queue<std::string> tokenList;

	Expression result;

	Environment env;
};


#endif // INTERPRETER_HPP
