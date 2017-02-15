#include "tokenize.hpp"


// (+ a ( - 4 ))
// "(", "+", "a", "(", "-", "4", ")", ")"

//split string on spaces, "(", and ")"
std::queue<std::string> createList(std::istream& input){

	std::string token;
	std::string segment;	

	std::queue<std::string> data;

	input >> segment;

	if(segment[0] == '(' && segment.size() == 1){
		data.push(segment);
	}
	else if(segment[0] == '(' && segment.size() > 1){
		
		token = segment.substr(0,1);	
		data.push(token);
		
		//assume the rest is a valid token
		token = segment.substr(1,segment.size()-1);
		data.push(token);	
	
	}	
	else{
		//error situation
	}		

	while(!input.eof()){
		
		input >> segment;
		
		if(!input.eof()){
			if(segment.size() == 1)	{	
				data.push(segment);
			}
			/*else if(segment.find("(") != string::npos){
				//continue this
		
			}
			else if(segment.find(")" != string::npos){
				//continue this

			}*/
		}
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


//take each token out of the token list and atomize it before 
// placing it into the AST
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

			//detect if the token is a number
			if(isdigit(tokenList.front()[0])){
				newNode->doubleValue = std::stod(tokenList.front());
				newNode->atomType = Double;
			}
			//detect if the token is a true boolean value
			else if(tokenList.front().compare("true") == 0){
				newNode->boolValue = true;
				newNode->atomType = Bool;
			}
			//detect if the token is a false boolean value
			else if(tokenList.front().compare("false") == 0){
				newNode->boolValue = false;
				newNode->atomType = Bool;
			}
			//else it should be a string
			else{
				newNode->symbolValue = tokenList.front();
				newNode->atomType = Symbol;
			}
				
			newNode->top = nullptr;
			root = newNode;
			currNode = root;
		
			tokenList.pop();
			
		}
		else if(tokenList.front() == "("){
			//the next entry needs to be a child
			tokenList.pop();		
			
			Node* newNode = new Node();

			//detect if the token is a number
			if(isdigit(tokenList.front()[0])){
				newNode->doubleValue = std::stod(tokenList.front());
				newNode->atomType = Double;
			}
			//detect if the token is a true boolean value
			else if(tokenList.front().compare("true") == 0){
				newNode->boolValue = true;
				newNode->atomType = Bool;
			}
			//detect if the token is a false boolean value
			else if(tokenList.front().compare("false") == 0){
				newNode->boolValue = false;
				newNode->atomType = Bool;
			}
			//else it should be a string
			else{
				newNode->symbolValue = tokenList.front();
				newNode->atomType = Symbol;
			}

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

			//detect if the token is a number
			if(isdigit(tokenList.front()[0])){
				newNode->doubleValue = std::stod(tokenList.front());
				newNode->atomType = Double;
			}
			//detect if the token is a true boolean value
			else if(tokenList.front().compare("true") == 0){
				newNode->boolValue = true;
				newNode->atomType = Bool;
			}
			//detect if the token is a false boolean value
			else if(tokenList.front().compare("false") == 0){
				newNode->boolValue = false;
				newNode->atomType = Bool;
			}
			//else it should be a string
			else{
				newNode->symbolValue = tokenList.front();
				newNode->atomType = Symbol;
			}


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

Node* AST::getRoot(){
	
	return root; 
}



