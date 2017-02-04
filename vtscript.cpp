#include <iostream>
#include <fstream>
#include <string.h>

//#include "expression.hpp"
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

int main(int agrc, char * argv[]){

	//make a stack to handle command line arguments
	//right now, we will assume there are no switches
	
	//Since I am not considering any flags atm, assume
	//argv[1] is the .vts file

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
	

	return EXIT_SUCCESS;

}
