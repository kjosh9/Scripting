#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "expression.hpp"
#include "environment.hpp"
#include <string>
#include <vector>


TEST_CASE("Test Constructor", "[Environment]"){

	//Environment env;	

}

TEST_CASE("Test evaluation", "[Environment]"){
	
	Environment env;

	Expression* exp0 = new Expression((std::string)"*");
	Expression* exp1 = new Expression((std::string)"+");
	Expression* exp2 = new Expression((double)2);
	Expression* exp3 = new Expression((double)2.2);

	std::vector<Expression*> expressionList;

	expressionList.push_back(exp1);
	expressionList.push_back(exp2);
	expressionList.push_back(exp3);
	
	Expression* exp4 = env.evaluateExpression(expressionList);
	
	REQUIRE(exp4->doubleData() == 4.2);

	expressionList[0] = exp0;

	exp4 = env.evaluateExpression(expressionList);

	REQUIRE(exp4->doubleData() == 4.4);

}
