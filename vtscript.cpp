#include <iostream>
#include <fstream>
#include <string.h>

#include "interpreter.hpp"
#include "expression.hpp"

//check the file type and return a boolean
bool checkFileType(std::string filename){

	//throws an error if there is no period
	std::string fileType = filename.substr(filename.find("."), 4);
	
	if(fileType == ".vts")
		return true;
	else
		return false;
}

int main(int argc, char * argv[]){

	Interpreter interp;
	Expression answer;
	

	switch(argc){
		//case where there is no command line arguments
		case 1:{
			std::string input;
			while(true){
				
				//put into the environment?
			
				std::cout << "vtscript> ";
				std::cin >> input;			
			}
				
			break;
		} 
		
		//case where the only command line argument is a file to interperet 
		case 2: {
			//check if it is the correct file type
			if(!checkFileType(argv[1])){
				std::cout << "ERROR: Incorrect file type" << std::endl;
				return EXIT_FAILURE;
			}

			std::ifstream inFile (argv[1]);
			if(inFile.is_open()){	
				interp.parse(inFile);
			}  	
			else{
				std::cout << "File does not exist" << std::endl;
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
			std::istringstream inputStream;
			inputStream.str(inputString);

			if(arg1.compare("-e") == 0){
				interp.parse(inputStream);
				answer = interp.eval();
			}	
			else{	
				std::cout <<"Incorrect input" << std::endl;
				return EXIT_FAILURE;
			}
			
			break;
		}	
	}

	//print out expression
	std::cout << "(";
	if(answer.dataType() == String)
		std::cout << answer.stringData();
	else if(answer.dataType() == Bool)
		std::cout << answer.boolData();
	else if(answer.dataType() == Double)
		std::cout << answer.doubleData();
	std::cout << ")";


	return EXIT_SUCCESS;
}
