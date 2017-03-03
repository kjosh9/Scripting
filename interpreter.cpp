#include "interpreter.hpp"


Interpreter::Interpreter(){
	env = Environment();

}

//all this does is take to input stream, parse it, and create
// an AST of the data
bool Interpreter::parse(std::istream & expression) noexcept
{
	//test is tokenlist is empty; if not, make it empty
	while(!tokenList.empty())
		tokenList.pop();

	bool success;
	tokenList = createList(expression, success);
	
	if(tokenList.empty())
		std::cout << "problemo" << std::endl;
	
	return success;
}


//take expression from the tree, form a list,
// and evaluate until root is evaluated
Expression Interpreter::eval(){

	//std::cout << "Here" << std::endl;
	syntaxTree = new AST();
	//std::cout << "And now" << std::endl;
	syntaxTree->assembleAST(tokenList);
	//start with the root of the tree
	Node* treeRoot = syntaxTree->getRoot();
	//std::cout << "got root" << std::endl;
	//std::cout << "atom value: " << treeRoot->atomType << std::endl;

	Expression result;
	//test if root has and branches
	if(treeRoot->branches.empty()){
		

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
	
	//this finds a solvable expression
	while(!solvableExpression(nodie, branchNo)){
		
		//if the current node is not evaluatable, go to the branch that
		//is not a leaf and evaluate.	
		nodie = nodie->branches[branchNo];
		std::cout << "evaluate node: " << branchNo <<std::endl;	
			
		result = evaluate(nodie);

		if(result.dataType() == String){
			nodie->symbolValue = result.stringData();
			nodie->atomType = aSymbol;
			std::cout << "string: " << result.stringData() << std::endl;
		}
		else if(result.dataType() == Bool){
			nodie->boolValue = result.boolData();
			nodie->atomType = aBool;
			std::cout << "bool: " << result.boolData() << std::endl;
		}
		else if(result.dataType() == Double){
			nodie->doubleValue = result.doubleData();
			nodie->atomType = aDouble;
			std::cout << "double: " << result.doubleData() << std::endl;
		}
		else if(result.dataType() == None){
			return Expression();
		}
		std::vector<Node*> emptyList;
		nodie->branches = emptyList;
		nodie->isLeaf = true;
		//go back to the upper node
		nodie = nodie->top;
		
	}
	std::vector<Expression*> resultList = formExpression(nodie);		
	result = env.evaluateExpression(resultList);

	return result;
}

std::vector<Expression*> Interpreter::formExpression(Node* currNode){

	std::vector<Expression*> expList;

	//start with the current node	
	Expression* newExp = new Expression(currNode->symbolValue);
	expList.push_back(newExp);
	
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
		

		if(currNode->branches.empty()){
			std::cout << "ERROR: No branches" << std::endl;				
			return true;		
		}		

		for(int i = 0; i < currNode->branches.size(); i++){
			if(currNode->branches[i]->isLeaf == false){
				branchNo = i;	
				std::cout << "branch on " << i << std::endl;				
				return false;
			}	
		}	
		return true;
}














