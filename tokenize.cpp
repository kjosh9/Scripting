#include "tokenize.hpp"


// (+ a ( - 4 ))
// "(", "+", "a", "(", "-", "4", ")", ")"
std::queue<std::string> createList(std::istream& input){
	
	//current limitations: two digit numbers.

	char c;
	std::queue<std::string> data;
	while(!input.eof()){
		std::string token;
		input.get(c);	
		
		if(c != ' ' && c != '\n' && c != '\a'){
			token = c;	
			data.push(token);
		}
		//test here if c is a number
	}
	return data;
}


AST::AST(){
	root = nullptr;
	currNode = nullptr;
}

AST::~AST(){
	//make sure to properly destroy this tree later
}

bool AST::assembleAST(std::queue<std::string> tokenList){

	//assuming the tokenList is syntactically correct
	while(!tokenList.empty()){
		
		//debugging help
		//std::cout << tokenList.front() << std::endl;
		
		if(tokenList.front() == "(" && root == nullptr){
			//the next entry needs to be the root			
			tokenList.pop();

			//create new node and make it root
			Node* newNode = new Node();
			newNode->data = tokenList.front();
			newNode->top = nullptr;
			root = newNode;
			currNode = root;
		
			tokenList.pop();
			
		}
		else if(tokenList.front() == "("){
			//the next entry needs to be a child
			tokenList.pop();		
			
			Node* newNode = new Node();
			newNode->data = tokenList.front();
			newNode->top = currNode;

			currNode->branches.push_back(newNode);
			currNode = newNode;

			tokenList.pop();		   
		}
		else if(tokenList.front() == ")"){
		
			//go up one node
			tokenList.pop();
			currNode = currNode->top;

			if(currNode == root){
				//break;
			}
		}
		else{
			
			//assign current token as a branch
			Node* newNode = new Node();
			newNode->data = tokenList.front();
			newNode->top = currNode;

			currNode->branches.push_back(newNode);
			tokenList.pop();
		}
	}
}

bool AST::empty(){

	if(root == nullptr)
		return true;
	else	
		return false;
}



