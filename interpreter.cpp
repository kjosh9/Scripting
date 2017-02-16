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

	//test if root has and branches
	if(treeRoot->branches.empty()){
		std::cout << "empty tree";
		Expression result;
		if(treeRoot->atomType == aBool){
			result = Expression(treeRoot->boolValue);
		}
		if(treeRoot->atomType == aSymbol){
			result = Expression((std::string)treeRoot->symbolValue);
		}
		if(treeRoot->atomType == aDouble){
			result = Expression(treeRoot->doubleValue);
		}	
	}
	else{
		Expression result = this->evaluate(treeRoot);		
		std::cout << "non-empty tree";
	}

	return result;	

}


//recursive function to traverse tree
Expression Interpreter::evaluate(Node* nodie){

	int branchNo = 0;

	//look to see if all the branches of the currNode are leaves
	if(this->solvableExpression(nodie, &branchNo)){

		//if it is solvable, lets simplify this expression
		
		//first, lets form the expression from atoms
		std::vector<Expression*> resultList = this->formExpression(nodie);
		Expression result = env.evaluateExpression(resultList);
	}
	else{
		//if it is not solvable, let's go to the part that needs
		// simplifying
		nodie = nodie->branches[branchNo];	
		this->evaluate(nodie);	

		//after its branches are simplified, then simplifiy 
		std::vector<Expression*> resultList = this->formExpression(nodie);
		Expression result = env.evaluateExpression(resultList);
	}
}

std::vector<Expression*> Interpreter::formExpression(Node* currNode){

	std::vector<Expression*> expList;	

	//start with the current node	
	Expression* newExp = new Expression(currNode->symbolValue);
	expList.push_back(newExp);
	
	for(int i = 0; i < currNode->branches.size(); i++){
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

bool Interpreter::solvableExpression(Node* currNode, int* branchNo){

		if(currNode->branches.empty()){
			std::cout << "ERROR: No branches" << std::endl;				
			return false;		
		}		

		for(int i = 0; i < currNode->branches.size(); i++){
			if(currNode->branches[i]->isLeaf == false){
				return false;
			}	
		}	
		return true;
}














