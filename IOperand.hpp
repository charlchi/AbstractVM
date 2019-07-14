
#ifndef I_OPERAND_HPP
#define I_OPERAND_HPP

#include <string>

// enum for operand types
enum eOperandType
{
	Int8,
	Int16,
	Int32,
	Float,
	Double,
	Error = -1
};

class IOperand
{
public:
	virtual int getPrecision( void ) const = 0;
	virtual eOperandType getType( void ) const = 0;
	virtual IOperand const * operator+( IOperand const & rhs ) const = 0;
	virtual IOperand const * operator-( IOperand const & rhs ) const = 0;
	virtual IOperand const * operator*( IOperand const & rhs ) const = 0;
	virtual IOperand const * operator/( IOperand const & rhs ) const = 0;
	virtual IOperand const * operator%( IOperand const & rhs ) const = 0;
	virtual std::string const & toString( void ) const = 0;
	virtual ~IOperand( void ) {}
};

#endif // I_OPERAND_HPP
