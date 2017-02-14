#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <string>

/*Will this will need a destuctor and a copy contructor?*/


class Expression{

public:
	// Default construct and Expression of type None
	Expression();

	// Construct an Expression with a single Boolean atom with value
	Expression(bool value);

	// Construct and Expression with a single Number aton with value
	Expression(double value);

	// Construct an Expresion with a single Symbol atom with value
	Expression(const std::string & value);

	// Equality operator for two Expressions, to expression are equal if they have the same
	// type, atom value, and number of arguments
	bool operator==(const Expression & exp) const noexcept;


	/*non-elegant solution*/
	std::string dataType() const;

	bool boolData() const;

	std::string stringData() const;

	double doubleData() const;
	/*--------------------*/

private: 
	
	/*non-elegant solution*/
	//as string that tells the data type
	std::string _dataType;

	//the actual data
	bool _boolData;
	std::string _stringData;
	double _doubleData;
	/*--------------------*/

};
#endif // EXPRESSION_HPP
