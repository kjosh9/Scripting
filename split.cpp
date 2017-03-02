#include "split.hpp"
#include <iostream>

bool split(std::string& first, std::string& second){

	for(int i = 0; i < first.length(); i++){
		if(first[i] == '(' || first[i] == ')' || first[i] == ' '){
			if(i > 0){
				second = first.substr(0,i);
				//std::cout << second << std::endl;
			}
			else if(first.length() == 1)
				return false;
			first.erase(0,i+1); 
			return true;
		}
	}
	
	return false;
}


