#include <iostream>
#include <fstream>
#include <string.h>

#include "interpreter.hpp"
#include "expression.hpp"

//check the file type and return a boolean
bool checkFileType(std::string filename){

	if(filename.find(".") == std::string::npos)
		return false;
	
	//throws an error if there is no period
	std::string fileType = filename.substr(filename.find("."), 4);
	
	if(fileType.compare(".vts") == 0 && !fileType.empty())
		return true;
	else
		return false;
}


//REPL
bool REPL(){
	Interpreter inter;
	std::string inputString;
	std::cout << "vtscript> ";
	Expression result;


	while(std::getline(std::cin, inputString) && !std::cin.eof()){

		std::istringstream INstream;

		if(inputString.compare("") !=0){		
			INstream.str(inputString);
			inter.parse(INstream);
			try{
				result = inter.eval();		
			}
			//catch in the event of an error
			catch(const InterpreterSemanticError & ex){
				std::cout << ex.what() << std::endl;
				//return false;
			}
			if(result.dataType() == String)
				std::cout << "(" << result.stringData() << ")";
			else if(result.dataType() == Bool){
				std::cout << "(";
				if(result.boolData())
					std::cout << "True";
				else 
					std::cout << "False";
				std::cout << ")";
			}
			else if(result.dataType() == Double)
				std::cout << "(" << result.doubleData() << ")";
			else if(result.dataType() == None){}
					
		}
		std::cout << std::endl;
		std::cout << "vtscript> ";
	}
	return true;

}

int main(int argc, char * argv[]){

	Interpreter interp;
	Expression answer;
	std::istringstream inputStream;

	switch(argc){
		//case where there is no command line arguments and
		//we enter the environment for REPL
		case 1:{

			if(REPL()){
				std::cout << std::endl;
				return EXIT_SUCCESS;
			}
			else
				return EXIT_FAILURE;
			break;
		} 
		
		//case where the only command line argument is a file to interperet 
		case 2: {
			Expression sum;
			//check if it is the correct file type
			if(!checkFileType(argv[1])){
				std::cout << "Error: Incorrect file type" << std::endl;
				return EXIT_FAILURE;
			}

			std::ifstream inFile (argv[1]);
			if(inFile.is_open()){	
				interp.parse(inFile);
				try{
					sum = interp.eval();
				}
				catch(InterpreterSemanticError const& ex){
					std::cout << "Catch3" << ex.what() << std::endl;
					return EXIT_FAILURE;
				}
				answer = sum;
			}  	
			else{
				std::cout << "Error: File does not exist" << std::endl;
				return EXIT_FAILURE;
			}
			break;
		}

		//all other cases
		default: {
	

			std::string arg1 = argv[1];
			
			std::string inputString = "";
			for(int i = 2; i < argc; i++){
				inputString.append((std::string)argv[i]);
			}

			//put the input string into the stream format
			inputStream.str(inputString);

			if(arg1.compare("-e") == 0){
				interp.parse(inputStream);
				try{
					answer = interp.eval();
				}
				catch(const InterpreterSemanticError & ex){
					return EXIT_FAILURE;
				}
			}	
			else{	
				std::cout <<"Incorrect input" << std::endl;
				return EXIT_FAILURE;
			}
			
			break;
		}	
	}

	//print out expression
	if(answer.dataType() == String)
		std::cout << "(" << answer.stringData() << ")";
	else if(answer.dataType() == Bool){
		std::cout << "(";
		if(answer.boolData())
			std::cout << "True";
		else 
			std::cout << "False";
		std::cout << ")";
	}
	else if(answer.dataType() == Double)
		std::cout << "(" << answer.doubleData() << ")" ;
	else if(answer.dataType() == None)
		return EXIT_FAILURE;

	std::cout << std::endl;

	return EXIT_SUCCESS;
}
