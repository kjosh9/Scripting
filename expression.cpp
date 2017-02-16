#include "expression.hpp"
#include <iostream>


Expression::Expression(){
	_dataType = None;
}

Expression::Expression(bool value){
	_dataType = Bool;
	_boolData = value;
}

Expression::Expression(double value){
	_dataType = Double;
	_doubleData = value;
}

Expression::Expression(const std::string & value){
	_dataType = String;
	_stringData = value;
}

bool Expression::operator==(const Expression & exp) const noexcept{
	
	if(exp.dataType() == this->dataType()){
	
		if((exp.dataType() == Bool) && (exp.boolData() == this->boolData())){	
			return true;	
		}
		else if((exp.dataType() == Double) && (exp.doubleData() == this->doubleData())){
			return true;	
		}
		else if(exp.dataType() == String){
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

expType Expression::dataType() const{
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



