#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "expression.hpp"


TEST_CASE("Test Constructor", "[Expression]"){

	Expression exp;

}

TEST_CASE("Test equality" , "[Expression]"){
	
	Expression* exp0 = new Expression("else");
	Expression* exp1 = new Expression("something");
	Expression* exp2 = new Expression("something");
	Expression* exp3 = new Expression((double)10);
	Expression* exp4 = new Expression((double)11);
	Expression* exp5 = new Expression((double)10);
	Expression* exp6 = new Expression((bool)false);
	Expression* exp7 = new Expression((bool)false);
	Expression* exp8 = new Expression((bool)true);
	
	//cases where we expect the same expression
	REQUIRE(exp1 == exp2);
	REQUIRE(exp3 == exp5);
	REQUIRE(exp6 == exp7);

	//cases where the case are the same, but different values
	REQUIRE((exp0 == exp1) == false);
	REQUIRE((exp3 == exp4) == false);
	REQUIRE((exp7 == exp8) == false);

	//cases where the case are different
	REQUIRE((exp0 == exp3) == false);
	REQUIRE((exp3 == exp6) == false);
	REQUIRE((exp8 == exp0) == false);
}
