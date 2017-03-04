#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <stdlib.h>

/*Will this will need a destuctor and a copy contructor?*/

enum expType {None, Bool, String, Double};
class Expression{

	//overloading the output operator to make things easier
	friend std::ostream& operator<<(std::ostream& out, Expression& exp);

public:
	// Default construct and Expression of type None
	Expression();

	// Construct an Expression with a single Boolean atom with value
	Expression(bool value);

	// Construct and Expression with a single Number atom with value
	Expression(double value);

	// Construct an Expresion with a single Symbol atom with value
	Expression(const std::string & value);

	//destructor
	~Expression();

	//copy constructor
	Expression(const Expression& another);

	// Equality operator for two Expressions, to expression are equal if they have the same
	// type, atom value, and number of arguments
	bool operator==(const Expression & exp) const noexcept;

	Expression& operator=(const Expression& another);

	/*non-elegant solution*/
	expType dataType() const;

	bool boolData() const;

	std::string stringData() const;

	double doubleData() const;


private: 
		
	//an enum type that tells the data type
	expType _dataType;

	//the actual data
	bool _boolData;
	std::string _stringData;
	double _doubleData;

};
#endif // EXPRESSION_HPP
