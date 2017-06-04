#include "tokenize.hpp"

//split string on spaces, "(", and ")"
std::queue<std::string> createList(std::istream& input, bool &success){

	success = true;
	std::string token;
	std::string segment;

	std::queue<std::string> data;

	int open = 0;
	int close = 0;

	while(input >> segment){

		if(open < close)
			success = false;	

		//split this string up based on '(' and ')'
		int last = 0;
		bool nothingSpecial = true;
		char lastPar;
		int i = 0;
		if(segment[0] == ';'){
			std::getline(input, segment);
			//std::cout << segment << std::endl;	
		}
		else{
			for(i = 0; i < segment.size(); i++){
				if(segment[i] == '('){
					if(last == i){
						data.push(segment.substr(last, 1));
						last++;
						lastPar = '(';
					}
					else{
						std::string newStr = segment.substr(last, i-last); 
						if(isdigit(newStr[0]) && (!isdigit(newStr[1]) || newStr[1] == '.'))
							success = false;					
						data.push(newStr);
						last = i;
						data.push(segment.substr(i, 1));
						lastPar = '(';
					}	
					open++;	
					nothingSpecial = false;	
				}
				else if(segment[i] == ')'){
					if(last == i){
						data.push(segment.substr(last, 1));
						if(lastPar == '(')
							success = false;
						last++;
						lastPar = ')';
					}
					else{
						std::string newStr = segment.substr(last, i-last); 
						if((newStr.size()>1)&&(isdigit(newStr[0]) && (!isdigit(newStr[1]) && newStr[1] != '.'))){
							success = false;					
							//std::cout <<"bleh" <<std::endl;
						}
						data.push(newStr);
						last = i;
						data.push(segment.substr(i, 1));
						lastPar = ')';
					}		
					close++;
					nothingSpecial = false;
				}
			
			}
			if(nothingSpecial){
				if((segment.size() > 1) && (isdigit(segment[0]) && !isdigit(segment[1]))){
					success=false;		
					std::cout << "incorrect digit string" << std::endl;		
				}	
				data.push(segment);
				lastPar = '-';
			}
			else if(last!=segment.size()){

				std::string newStr = segment.substr(last, i-last);
			
				if(newStr.compare(")")!=0 && newStr.compare("(")!=0){
					if((newStr.size() > 1) && (isdigit(newStr[0])) && (!isdigit(newStr[1]  && newStr[1] != '.'))){
						success=false;		
						//std::cout << "incorrect digit string" << std::endl;		
					}	
					data.push(newStr);
					lastPar = '-';
				}
			}
		}
	}
	if(data.front().compare("(") != 0){
		success = false;
		//std::cout << "Incorrect first character" << std::endl;
	}
	if(open != close){
		success = false;
		//std::cout << "Incorrect parenth" << std::endl;
	}

	if(data.empty())
		success = false;

	return data;
}

AST::AST(){
	root = nullptr;
	currNode = nullptr;
}

AST::~AST(){

}


//take each token out of the token list and atomize it before 
// placing it into the AST
bool AST::assembleAST(std::queue<std::string> tokenList){

	if(tokenList.empty())
		return false;

	bool madeChild = false;	

	//assuming the tokenList is syntactically correct
	while(!tokenList.empty()){

		if(tokenList.front() == "(" && root == nullptr){
			//the next entry needs to be the root			
			tokenList.pop();

			if(tokenList.front() == ")")
				return false;
			//create new node and make it root 
			Node* newNode = new Node();

			//detect if the token is a number
			if(isdigit(tokenList.front()[0]) || (tokenList.front()[0] == '-' && isdigit(tokenList.front()[1]))){
				newNode->doubleValue = std::stod(tokenList.front());
				newNode->atomType = aDouble;
			}
			//detect if the token is a true boolean value
			else if((tokenList.front().compare("true") == 0) || (tokenList.front().compare("True") == 0)){
				newNode->boolValue = true;
				newNode->atomType = aBool;
			}
			//detect if the token is a false boolean value
			else if((tokenList.front().compare("false") == 0) || (tokenList.front().compare("False") == 0)){
				newNode->boolValue = false;
				newNode->atomType = aBool;
			}
			//else it should be a string
			else{
				newNode->symbolValue = tokenList.front();
				newNode->atomType = aSymbol;
			}
				
			newNode->top = nullptr;
			newNode->isLeaf = true;
			root = newNode;
			currNode = root;
			tokenList.pop();
			
		}
		else if(tokenList.front() == "("){
			//the next entry needs to be a child
			tokenList.pop();

			madeChild = true;		
	
			if(tokenList.front() == ")")
				return false;			

			Node* newNode = new Node();

			//detect if the token is a number
			if(isdigit(tokenList.front()[0]) || (tokenList.front()[0] == '-' && isdigit(tokenList.front()[1]))){
				newNode->doubleValue = std::stod(tokenList.front());
				newNode->atomType = aDouble;
			}
			//detect if the token is a true boolean value
			else if((tokenList.front().compare("true") == 0) || (tokenList.front().compare("True") == 0)){
				newNode->boolValue = true;
				newNode->atomType = aBool;
			}
			//detect if the token is a false boolean value
			else if((tokenList.front().compare("false") == 0) || (tokenList.front().compare("False") == 0)){
				newNode->boolValue = false;
				newNode->atomType = aBool;
			}
			//else it should be a string
			else{
				newNode->symbolValue = tokenList.front();
				newNode->atomType = aSymbol;
			}
			
			currNode->isLeaf = false;
			newNode->top = currNode;
			newNode->isLeaf = true;

			currNode->branches.push_back(newNode);
			currNode = newNode;
			tokenList.pop();		   
		}
		else if(tokenList.front() == ")"){
		
			//go up one node
			tokenList.pop();
			
			if(currNode != root)			
				currNode = currNode->top;
			else if(currNode == root && !tokenList.empty() && !madeChild)
				madeChild = false;//return false;
			else
				madeChild = false;
		}
		//these are branches of the current nodes
		else{
			
			//assign current token as a branch
			Node* newNode = new Node();

			//detect if the token is a number
			if(isdigit(tokenList.front()[0]) || (tokenList.front()[0] == '-' && isdigit(tokenList.front()[1]))){
				newNode->doubleValue = std::stod(tokenList.front());
				newNode->atomType = aDouble;
			}
			//detect if the token is a true boolean value
			else if((tokenList.front().compare("true") == 0 )|| (tokenList.front().compare("True") == 0)){
				newNode->boolValue = true;
				newNode->atomType = aBool;
			}
			//detect if the token is a false boolean value
			else if((tokenList.front().compare("false") == 0) || (tokenList.front().compare("False") == 0)){
				newNode->boolValue = false;
				newNode->atomType = aBool;
			}
			//else it should be a string
			else{
				newNode->symbolValue = tokenList.front();
				newNode->atomType = aSymbol;
			}

			newNode->isLeaf = true;
			newNode->top = currNode;
			newNode->top->isLeaf = false;

			currNode->branches.push_back(newNode);
			tokenList.pop();
		}
	}

	return !empty();
}

bool AST::empty(){

	if(root == nullptr)
		return true;
	else	
		return false;
}

Node* AST::getRoot(){
	
	if(empty()){
		std::cout << "Empty tree" << std::endl;
		//exit();
	}
	
	return root; 
}



