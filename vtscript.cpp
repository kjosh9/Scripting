#include <iostream>
#include <fstream>
#include <string.h>

//#include "interpreter.hpp"
//#include "tokenize.hpp"

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

	//Interpreter reader;
	
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
				while(!inFile.eof()){
					std::string line;
					getline(inFile, line);
					std::cout << "Line" << std::endl;
				}
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

			std::cout << arg1 << std::endl;

			if(arg1.compare("-e") == 0){
				
				//now use the interpreter

			}	
			else{	
				std::cout <<"Incorrect input" << std::endl;
				return EXIT_FAILURE;
			}
			
			break;
		}	
	}


	return EXIT_SUCCESS;
}
