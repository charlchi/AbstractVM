
#include "OperandFactory.hpp"
#include "Operand.hpp"

IOperand const * OperandFactory::createInt8( std::string const * value ) const {
	return new Operand<char>(value);
}

IOperand const * OperandFactory::createInt16( std::string const * value ) const {
	return new Operand<short>(value);
}

IOperand const * OperandFactory::createInt32( std::string const * value ) const {
	return new Operand<int>(value);
}

IOperand const * OperandFactory::createFloat( std::string const * value ) const {
	return new Operand<float>(value);
}

IOperand const * OperandFactory::createDouble( std::string const * value ) const {
	return new Operand<double>(value);
}

typedef IOperand const * (OperandFactory::*CreateMemFn)( std::string const * value );

CreateMemFn[] creatorPointers = {
	&OperandFactory::createInt8,
	&OperandFactory::createInt16,
	&OperandFactory::createInt32,
	&OperandFactory::createFloat,
	&OperandFactory::createDouble	
};

IOperand const * OperandFactory::createOperand( eOperandType type, std::string const & value ) const {
	CreateMemFn fn = creatorPointers[type];
	return (this->*fn)(value);
}

