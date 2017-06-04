
#include "environment.hpp"

Environment::Environment(){
	
	Expression* PI = new Expression((double)atan2(0,-1));
	
	addToSymbolMap("pi", PI);
	delete PI;

	operatorList.push_back("begin");
	operatorList.push_back("if");
	operatorList.push_back("define");
	operatorList.push_back("not");
	operatorList.push_back("and");
	operatorList.push_back("or");
	operatorList.push_back("<");
	operatorList.push_back("<=");
	operatorList.push_back(">");
	operatorList.push_back(">=");
	operatorList.push_back("=");
	operatorList.push_back("+");
	operatorList.push_back("-");
	operatorList.push_back("*");
	operatorList.push_back("/");

}

Environment::~Environment(){

	symbolMap.clear();
	

}

bool Environment::isOp(std::string symbol){

	for(int i = 0; i < operatorList.size(); i++){
		if(operatorList[i].compare(symbol) == 0)
			return true;
	}
	return false;
}


bool Environment::addToSymbolMap(std::string symbol, Expression* exp){

	Expression mapExp = *exp;
	if(symbolMap.find(symbol) == symbolMap.end()){
		symbolMap.insert(std::pair<std::string,Expression>(symbol, mapExp));		
		return true;	
	}	
	else{
		throw InterpreterSemanticError("ERROR: Symbol already mapped");
		return false;
	}
}

Expression Environment::fetchExp(std::string symbol, bool& success){

	Expression lookup;
	if(symbolMap.find(symbol) == symbolMap.end()){
		success = false;
	}
	else{
		lookup = symbolMap[symbol];
		success = true;
	}

	return lookup;
}

Expression Environment::evaluateExpression(std::vector<Expression*> &expList){
	
	Expression result;

	//check to make sure the first type is correct
	if(expList[0]->dataType() != String){
		std::cout << "Error: not the correct starting expression: ";	
		//std::cout << expList[0]->dataType() << std::endl;
	}	

	//detect if any of the expressions are symbols that need mapping
	// then replace with new expressions
	if(expList[0]->stringData().compare("define") != 0){
		for(int i = 1; i < expList.size(); i++){
			if(expList[i]->dataType() == String && !isOp(expList[i]->stringData())){
				bool lookSucc;
				Expression temExp = fetchExp(expList[i]->stringData(), lookSucc);
			
				if(lookSucc){
					*expList[i] = temExp;
				}
				//else 
				//	std::cout << "not in map" << std::endl;			
			}
		}
	}
	
	if(expList.size() == 1 && expList[0]->dataType() == String){
		Expression temExp = symbolMap[expList[0]->stringData()];
		return temExp;
	}


	if(expList[0]->stringData().compare("begin") == 0){
		Expression begExp = *expList[expList.size()-1];
		return 	begExp;
	}


/*------------------------------------------------------------------------------*/
	else if(expList[0]->stringData().compare("define") == 0){	

		if(expList.size() > 3){
			//std::cout << "Error: too many arguments for define";
			throw InterpreterSemanticError("ERROR: too many arguments for define");
			return Expression();
		}
		

		if(expList[2]->dataType() == String && !isOp(expList[2]->stringData())){
			bool lookSucc;
			Expression temExp = fetchExp(expList[2]->stringData(), lookSucc);
			if(lookSucc)
				expList[2] = &temExp;	
		}

		if(isOp(expList[1]->stringData())){
			//std::cout << "Error: Cannot redefine special form or operator" << std::endl;			
			throw InterpreterSemanticError("Error: Cannot redefine special form or operator");
			return Expression();
		}

		if(addToSymbolMap(expList[1]->stringData(), expList[2])){
			Expression defExp = *expList[2];
			return defExp;
		}
		else{
			std::cout << "error in define" << std::endl;
			return Expression();
		}
	}

/*------------------------------------------------------------------------------*/
	else if(expList[0]->stringData().compare("if") == 0){
	
		if(expList.size() != 4){
			throw InterpreterSemanticError("Error: incorrect number of arguments for if");
			return Expression();
		}
		if(expList[1]->boolData()){
			return *expList[2];
		}
		else{
			return *expList[3];
		}				
	}

/*------------------------------------------------------------------------------*/
	else if(expList[0]->stringData().compare("not") == 0){

		Expression NotExp;
		if(expList.size() > 2){
			throw InterpreterSemanticError("ERROR: too many arguments for not");
		}
		
		if(expList[1]->dataType() == Bool){
			NotExp = Expression((bool)!expList[1]->boolData());
			return NotExp;
		}
		else if(expList[1]->dataType() == Double){
			NotExp = Expression((double)-1*expList[1]->doubleData());
			return NotExp;
		}
		else{	
			std::cout << "this is maybe an error in not" << std::endl;
			return Expression();
		}
				
	}


/*------------------------------------------------------------------------------*/
	else if(expList[0]->stringData().compare("and") == 0){
		
		bool answer = true;		
	
		for(int i = 1; i < expList.size(); i++){
			answer = answer && expList[i]->boolData();
		}
		return Expression((bool)answer);
	}


/*------------------------------------------------------------------------------*/
	else if(expList[0]->stringData().compare("or") == 0){

		bool answer = false;
		for(int i = 1; i < expList.size(); i++){
			answer = answer || expList[i]->boolData();
		}		
		return Expression(answer);
	}


/*------------------------------------------------------------------------------*/
	else if(expList[0]->stringData().compare("<") == 0){
		
		if(expList.size() > 3){
			std::cout << "Error: too many arguments for <" << std::endl;
		}
		return Expression(expList[1]->doubleData() < expList[2]->doubleData());
	}


/*------------------------------------------------------------------------------*/
	else if(expList[0]->stringData().compare("<=") == 0){
		if(expList.size() > 3)
			throw InterpreterSemanticError("Error: too many arguments for <=");
		return Expression(expList[1]->doubleData() <= expList[2]->doubleData());
	}

/*------------------------------------------------------------------------------*/
	else if(expList[0]->stringData().compare(">") == 0){
		if(expList.size() > 3)
			throw InterpreterSemanticError("Error: too many arguments for >");
		return Expression(expList[1]->doubleData() > expList[2]->doubleData());
	}
/*------------------------------------------------------------------------------*/
	else if(expList[0]->stringData().compare(">=") == 0){
		if(expList.size() > 3)
			throw InterpreterSemanticError("Error: too many arguments for >=");
		return Expression(expList[1]->doubleData() >= expList[2]->doubleData());
	}


/*------------------------------------------------------------------------------*/
	else if(expList[0]->stringData().compare("=") == 0){
		if(expList.size() > 3)
			throw InterpreterSemanticError("Error: too many arguments for =");
		return Expression(expList[1]->doubleData() == expList[2]->doubleData());
	}

/*------------------------------------------------------------------------------*/
	else if(expList[0]->stringData().compare("+") == 0){
		double sum = 0;
		for(int i = 1; i < expList.size(); i++){
			sum = sum + expList[i]->doubleData();
		}
		return Expression((double)sum);
	}

/*------------------------------------------------------------------------------*/
	else if(expList[0]->stringData().compare("-") == 0){
		if(expList.size() == 2){
			return Expression(-1*expList[1]->doubleData());
		}
		else if(expList.size() == 3){
			return Expression(expList[1]->doubleData() - expList[2]->doubleData());
		}
		else{
			throw  InterpreterSemanticError("Error: Too many arguments for -");
			return Expression();
		}
	}


/*------------------------------------------------------------------------------*/
	else if(expList[0]->stringData().compare("*") == 0){
		double product = 1;
		for(int i = 1; i < expList.size(); i++){
			product = product * expList[i]->doubleData();
		}
		return Expression(product);
	}


/*------------------------------------------------------------------------------*/
	else if(expList[0]->stringData().compare("/") == 0){
		
		if(expList.size() > 3){
			//std::cout << "Too many arguments for /" << std::endl;	
			return Expression();
		}
		return Expression(expList[1]->doubleData() / expList[2]->doubleData());
	}
	else{
		//std::cout << "Invalid Procedure" << std::endl;
		throw InterpreterSemanticError("Error: Invalied Procedure");
		return Expression();
	}
}


