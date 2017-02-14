#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include "Expression.hpp"

//This module should define the C++ types and code
// required to implement the vtscript environment mapping


class Environment{

public:

	Environment();

	//take a token and retrun something that indicates that it is
	// an atom or procedure 
	whatIsThis(std::string &token);

private:

	

};


#endif //ENVIRONMENT_HPP
