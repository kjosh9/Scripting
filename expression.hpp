#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

template <typename T>

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


private: 

	T* data;

};
#endif // EXPRESSION_HPP
