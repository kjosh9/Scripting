#include "expression.hpp"

template<typename T> 
Expression::Expression(){
	
}

template<typename T>
Expression::Expression(bool value){
	data = value;
}

template<typename T>
Expression::Expression(double value){
	data = value;
}

template<typename T>
Expression::Expression(const std::string & value){
	data = value;
}

template<typename T>
bool Expression::operator==(const Expression & exp const noexcept{
	
}
