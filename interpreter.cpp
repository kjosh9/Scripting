#include "interpreter.hpp"


Interpreter::Interpreter(){
	syntaxTree = new AST();
	env = Environment();

}


//all this does is take to input stream, parse it, and create
// an AST of the data
bool Interpreter::parse(std::istream & expression) noexcept
{
	bool success;
	tokenList = createList(expression, success);

	return success;
}


//take expression from the tree, form a list,
// and evaluate until root is evaluated
Expression Interpreter::eval(){

	syntaxTree->assembleAST(tokenList);

	//start with the root of the tree
	Node* treeRoot = syntaxTree->getRoot();

	//std::cout << "atom value: " << treeRoot->atomType << std::endl;

	Expression result;
	
	//test if root has and branches
	if(treeRoot->branches.empty()){
		//std::cout << "empty tree ";
		if(treeRoot->atomType == aBool){
			result = Expression((bool)treeRoot->boolValue);
			//std::cout << "Return Expression: " << result.dataType() << std::endl;
		}
		if(treeRoot->atomType == aSymbol){						
			bool success;
			Expression temp = env.fetchExp((std::string)treeRoot->symbolValue, success);
			if(success == true)
				result = temp;
			else	
				result = Expression((std::string)treeRoot->symbolValue);
			
		}
		if(treeRoot->atomType == aDouble){
			result = Expression((double)treeRoot->doubleValue);
		}	
	}
	else{
		//std::cout << "non-empty tree ";
		result = evaluate(treeRoot);		
	}
	
	//std::cout << "Return Expression: " << result.dataType() << std::endl;
	return result;	

}


//recursive function to traverse tree
Expression Interpreter::evaluate(Node* nodie){

	Expression result;
	int branchNo = 0;
	
	while(!solvableExpression(nodie, branchNo)){
			
		nodie = nodie->branches[branchNo];
		std::cout << "evaluate node: " << branchNo <<std::endl;	
			
		result = evaluate(nodie);

	}
	std::vector<Expression*> resultList = formExpression(nodie);		
	result = env.evaluateExpression(resultList);

	if(result.dataType() == String){
		nodie->symbolValue = result.stringData();
		nodie->atomType = aSymbol;
	}
	else if(result.dataType() == Bool){
		nodie->boolValue = result.boolData();
		nodie->atomType = aBool;
	}
	else if(result.dataType() == Double){
		nodie->doubleValue = result.doubleData();
		nodie->atomType = aDouble;
	}
	else if(result.dataType() == None){
		return Expression();
	}
	std::vector<Node*> emptyList;
	nodie->branches = emptyList;
	nodie->isLeaf = true;
	nodie = nodie->top;

	return result;
}

std::vector<Expression*> Interpreter::formExpression(Node* currNode){

	std::vector<Expression*> expList;

	//start with the current node	
	Expression* newExp = new Expression(currNode->symbolValue);
	expList.push_back(newExp);
	//std::cout << "Q" << std::endl;
	
	for(int i = 0; i < currNode->branches.size(); i++){
		
		//std::cout << i << std::endl;
		if(currNode->branches[i]->atomType == aBool){
			Expression* nextExp = new Expression(currNode->branches[i]->boolValue);
			expList.push_back(nextExp);
		}
		else if(currNode->branches[i]->atomType == aSymbol){
			Expression* nextExp = new Expression(currNode->branches[i]->symbolValue);
			expList.push_back(nextExp);
		}
		else if(currNode->branches[i]->atomType == aDouble){
			Expression* nextExp = new Expression(currNode->branches[i]->doubleValue);
			//std::cout << "data: "<< nextExp->doubleData();
			expList.push_back(nextExp);
		}	
	}
	//std::cout << "return list ";
	return expList;
}

bool Interpreter::solvableExpression(Node* currNode, int& branchNo){
		

		branchNo = 0;		
		if(currNode->branches.empty()){
			//std::cout << "ERROR: No branches" << std::endl;				
			return true;		
		}		

		for(int i = 0; i < currNode->branches.size(); i++){
			if(currNode->branches[i]->isLeaf == false){
				branchNo = i;					
				return false;
			}	
		}	
		return true;
}














