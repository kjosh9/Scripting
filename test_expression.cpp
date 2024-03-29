#include "catch.hpp"
#include "expression.hpp"


TEST_CASE("Test Expression Constructor", "[Expression]"){

	Expression exp;

}

TEST_CASE("Test equality" , "[Expression]"){
	
	Expression exp0 = Expression((std::string)"else");
	Expression exp1 = Expression((std::string)"something");
	Expression exp2 = Expression((std::string)"something");
	Expression exp3 = Expression(10.);
	Expression exp4 = Expression((double)11);
	Expression exp5 = Expression((double)10);
	Expression exp6 = Expression((bool)false);
	Expression exp7 = Expression((bool)false);
	Expression exp8 = Expression((bool)true);
	Expression exp9 = Expression(true);
	
	//cases where we expect the same expression
	REQUIRE(exp1 == exp2);
	REQUIRE(exp3 == exp5);
	REQUIRE(exp6 == exp7);

	//cases where the case are the same, but different values
	REQUIRE(!(exp0 == exp1));
	REQUIRE(!(exp3 == exp4));
	REQUIRE(!(exp7 == exp8));

	//cases where the case are different
	REQUIRE(!(exp0 == exp3));
	REQUIRE(!(exp3 == exp6));
	REQUIRE(!(exp8 == exp0));

	REQUIRE(exp9 == Expression(true));
}
