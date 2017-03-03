#include "catch.hpp"
#include "expression.hpp"
#include "environment.hpp"
#include <string>
#include <vector>
#include <math.h>


TEST_CASE("Test Environment Constructor", "[Environment]"){

	//Environment env;	

}

TEST_CASE("Test evaluation", "[Environment]"){
	
	Environment env;

	Expression* exp0 = new Expression((std::string)"*");
	Expression* exp1 = new Expression((std::string)"+");
	Expression* exp2 = new Expression((double)2);
	Expression* exp3 = new Expression((double)2.2);
	Expression* exp4 = new Expression((std::string)"pi");

	Expression* exp5 = new Expression((bool)false);
	Expression* exp6 = new Expression((bool)true);

	Expression* exp7 = new Expression((std::string)"define");
	Expression* exp8 = new Expression((std::string)"a");
	

	std::vector<Expression*> expressionList;

	expressionList.push_back(exp1);
	expressionList.push_back(exp2);
	expressionList.push_back(exp3);

	std::vector<Expression*> expressionList1;
	
	expressionList1.push_back(exp1);
	expressionList1.push_back(exp2);
	expressionList1.push_back(exp4);
	
	Expression expResult1 = env.evaluateExpression(expressionList);
	
	REQUIRE(expResult1.doubleData() == 4.2);

	expressionList[0] = exp0;

	expResult1 = env.evaluateExpression(expressionList);

	REQUIRE(expResult1.doubleData() == 4.4);

	Expression result = env.evaluateExpression(expressionList1);
	
	REQUIRE(result.doubleData() == (2+atan2(0,-1)));


	std::vector<Expression*> expressionList2;
	
	expressionList2.push_back(exp7);
	expressionList2.push_back(exp8);
	expressionList2.push_back(exp3);

	Expression result2 = env.evaluateExpression(expressionList2);

	REQUIRE(result2.doubleData() == 2.2);	

	std::vector<Expression*> expressionList3;
	
	expressionList3.push_back(exp1);
	expressionList3.push_back(exp8);
	expressionList3.push_back(exp2);
	expressionList3.push_back(exp3);

	Expression result3 = env.evaluateExpression(expressionList3);

	REQUIRE(result3.doubleData() == 2.2+2+2.2);
}







