#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include "expression.hpp"
#include <iostream>
#include <math.h>
#include <map>
#include <vector>

//This module should define the C++ types and code
// required to implement the vtscript environment mapping

class Environment{

public:

	Environment();

	bool addToSymbolMap(std::string symbol, Expression exp);

	Expression evaluateExpression(std::vector<Expression*> &expList);

	Expression fetchExp(std::string symbol, bool& success);

private:

	std::map<std::string, Expression> symbolMap;

};


#endif //ENVIRONMENT_HPP
