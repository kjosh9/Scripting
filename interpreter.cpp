#include "interpreter.hpp"


Interpreter::Interpreter(){
	env = Environment();

}

Interpreter::~Interpreter(){

	delete syntaxTree;
	syntaxTree = nullptr;

	
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
	
	if(tokenList.empty()){}
		//std::cout << "problemo" << std::endl;
	
	return success;
}


//take expression from the tree, form a list,
// and evaluate until root is evaluated
Expression Interpreter::eval(){

	syntaxTree = new AST();
	syntaxTree->assembleAST(tokenList);

	//start with the root of the tree
	Node* treeRoot = syntaxTree->getRoot();

	Expression result;

	//test if root has and branches
	if(treeRoot->branches.empty()){
		
		if(treeRoot->atomType == aBool)
			result = Expression((bool)treeRoot->boolValue);

		if(treeRoot->atomType == aSymbol){
			bool success;
			Expression temp = env.fetchExp((std::string)treeRoot->symbolValue, success);
			if(success == true)
				result = temp;
			else	
				result = Expression((std::string)treeRoot->symbolValue);
			
		}
		if(treeRoot->atomType == aDouble)
			result = Expression((double)treeRoot->doubleValue);
	}
	else
		result = evaluate(treeRoot);		
	
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
		//std::cout << "evaluate node: " << branchNo <<std::endl;	
			
		result = evaluate(nodie);

		if(result.dataType() == String){
			nodie->symbolValue = result.stringData();
			nodie->atomType = aSymbol;
			//std::cout << "string: " << result.stringData() << std::endl;
		}
		else if(result.dataType() == Bool){
			nodie->boolValue = result.boolData();
			nodie->atomType = aBool;
			//std::cout << "bool: " << result.boolData() << std::endl;
		}
		else if(result.dataType() == Double){
			nodie->doubleValue = result.doubleData();
			nodie->atomType = aDouble;
			//std::cout << "double: " << result.doubleData() << std::endl;
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
	
	//try to evaluate the expression in the environment, if not catch the error
	try{		
		result = env.evaluateExpression(resultList);
	}	
	catch(InterpreterSemanticError const& ex){
		throw;
	}
	
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
			expList.push_back(nextExp);
		}	
	}

	return expList;
}

//determine if the expression is solvable if the branches of 
//that node are all leaves
bool Interpreter::solvableExpression(Node* currNode, int& branchNo){
		
		//if the branch is a leaf for some reason, return true
		if(currNode->branches.empty()){
			std::cout << "ERROR: No branches" << std::endl;	
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














