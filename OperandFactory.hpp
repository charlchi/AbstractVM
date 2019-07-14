
#ifndef OPERAND_FACTORY_HPP
#define OPERAND_FACTORY_HPP

#include "IOperand.hpp"

class OperandFactory
{

// In order to use the right member function, MUST use an array
	IOperand const * createInt8( std::string const * value ) const;
	IOperand const * createInt16( std::string const * value ) const;
	IOperand const * createInt32( std::string const * value ) const;
	IOperand const * createFloat( std::string const * value ) const;
	IOperand const * createDouble( std::string const * value ) const;

public:
	IOperand const * createOperand( eOperandType type, std::string const & value ) const;
    OperandFactory();
    ~OperandFactory();
 
};

#endif // OPERAND_FACTORY_HPP
