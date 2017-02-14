#include "expression.hpp"
#include <iostream>


Expression::Expression(){
	_dataType = "none";
}


Expression::Expression(bool value){
	_dataType = "bool";
	_boolData = value;
}


Expression::Expression(double value){
	_dataType = "double";
	_doubleData = value;
}


Expression::Expression(const std::string & value){
	_dataType = "string";
	_stringData = value;
}


bool Expression::operator==(const Expression & exp) const noexcept{
	
	if(exp.dataType().compare(this->dataType()) == 0){
	
		if((exp.dataType() == "bool") && (exp.boolData() == this->boolData())){	
			return true;	
		}
		else if((exp.dataType() == "double") && (exp.doubleData() == this->doubleData())){
			return true;	
		}
		else if(exp.dataType() == "string"){
			if(exp.stringData().compare(this->stringData()) == 0)
				return true;
			else
				return false;
		}
		else{
			return false;
		}
	}
	else 
		return false;

}

std::string Expression::dataType() const{
	return _dataType;
}

bool Expression::boolData() const{
	return _boolData;
}

std::string Expression::stringData() const{
	return _stringData;
}

double Expression::doubleData() const{
	return _doubleData;
}

