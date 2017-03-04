#include "expression.hpp"

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
	
	if(value.compare("True") == 0){
		_dataType = Bool;
		_boolData = true;
	}
	else if(value.compare("False") == 0){
		_dataType = Bool;
		_boolData = false;
	}
	else{
		_dataType = String;
		_stringData = value;
	}
}

Expression::~Expression(){

}

Expression::Expression(const Expression& rhs){

	_dataType = rhs._dataType;
	
	if(_dataType == Bool)
		_boolData = rhs._boolData;
	else if(_dataType == Double)
		_doubleData = rhs._doubleData;
	else if(_dataType == String)
		_stringData = rhs._stringData;

	//std::cout << "COPY: " << _dataType << std::endl;
	
}

bool Expression::operator==(const Expression & exp) const noexcept{
	if(exp.dataType() == dataType()){
	
		if((exp.dataType() == Bool) && (exp.boolData() == boolData())){	
			return true;	
		}
		else if(exp.dataType() == Bool){
			//std::cout << "RHS: " << exp.boolData() << std::endl;
			//std::cout << "LHS: " << boolData() << std::endl;
		}
		
		if((exp.dataType() == Double) && (exp.doubleData() == doubleData())){
			return true;	
		}
		else if(exp.dataType() == Double){
			//std::cout << "RHS: " << exp.doubleData() << std::endl;
			//std::cout << "LHS: " << doubleData() << std::endl;
		}

		if(exp.dataType() == String){
			if(exp.stringData().compare(stringData()) == 0)
				return true;
			else
				return false;
		}
		else{
			return false;
		}
	}
	else {
		//std::cout << "incompatible types" <<std::endl;
		//std::cout << "RHS: " << exp.dataType() << std::endl;
		//std::cout << "LHS: " << dataType() << std::endl;
	
		return false;
	}

}

Expression& Expression::operator=(const Expression& rhs){
	
	if(this == &rhs)
		return *this;

	_dataType = rhs._dataType;
	
	if(_dataType == Bool)
		_boolData = rhs._boolData;
	else if(_dataType == String)
		_stringData = rhs._stringData;
	else if(_dataType == Double)
		_doubleData = rhs._doubleData;

	//std::cout << "Assignment: " << _dataType << std::endl;

	return *this;

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

//operator << 
std::ostream& operator<<(std::ostream& out, Expression& exp){
	
	std::cout << "(";
	if(exp.dataType() == String)
		std::cout << exp.stringData();
	else if(exp.dataType() == Bool){
		if(exp.boolData())
			std::cout << "True";
		else
			std::cout << "False";		
	}
	else if(exp.dataType() == Double)
		std::cout << exp.doubleData();

	std::cout << ")";

	return out;
}



