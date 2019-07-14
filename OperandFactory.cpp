
#include "OperandFactory.hpp"
#include "Operand.hpp"

IOperand const * OperandFactory::createInt8( std::string const * value ) const {
	return new Operand<int8_t>((int8_t)std::atoi(value->c_str()), value, this, eOperandType::Int8);
}

IOperand const * OperandFactory::createInt16( std::string const * value ) const {
	return new Operand<int16_t>((int16_t)std::atoi(value->c_str()), value, this, eOperandType::Int16);
}

IOperand const * OperandFactory::createInt32( std::string const * value ) const {
	return new Operand<int32_t>((int32_t)std::atoi(value->c_str()), value, this, eOperandType::Int32);
}

IOperand const * OperandFactory::createFloat( std::string const * value ) const {
	return new Operand<float>(atof(value->c_str()), value, this, eOperandType::Float);
}

IOperand const * OperandFactory::createDouble( std::string const * value ) const {
	return new Operand<double>(atof(value->c_str()), value, this, eOperandType::Double);
}

typedef IOperand const * (OperandFactory::*CreateMemFn)( std::string const * value ) const;

IOperand const * OperandFactory::createOperand( eOperandType type, std::string const & value ) const {

	CreateMemFn creatorPointers[] = {
		&OperandFactory::createInt8,
		&OperandFactory::createInt16,
		&OperandFactory::createInt32,
		&OperandFactory::createFloat,
		&OperandFactory::createDouble
	};

	CreateMemFn fn = creatorPointers[type];
	return (this->*fn)(&value);
}

OperandFactory::OperandFactory() {}
OperandFactory::~OperandFactory() {}
