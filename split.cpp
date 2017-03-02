#include "split.hpp"

bool split(std::string first, std::string second){

	for(int i = 0; i < first.length(); i++){
		if(first[i] == '(' || first[i] == ')' || first[i] == ' '){
			second = first.substr(i+1, first.length()-i+1);
			first.erase(0,i); 
			return true;
		}
	}
	
	return false;
}


