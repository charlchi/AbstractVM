
#include "IOperand.hpp"

template <class T>
class Operand : public IOperand
{
	T value;
	int type;
public:

	// "The pure method getPrecision allows to get the precision
	// of an operand. When an operation uses two operands from two
	// types the comparison of their precisions allows to figure
	// out the result type of the operation."
	int getPrecision( void ) {
		return type;
	}

	eOperandType getType( void ) {
		return type;
	}

	IOperand const * operator+( IOperand const & rhs ) {
		return this->value + rhs.val;
	}

	IOperand const * operator-( IOperand const & rhs ) {
		return this->value - rhs.val;
	}

	IOperand const * operator*( IOperand const & rhs ) {
		return this->value * rhs.val;
	}

	IOperand const * operator/( IOperand const & rhs ) {
		if (rhs.val == 0)
			return 0;
		return this->value / rhs.val;
	}

	IOperand const * operator%( IOperand const & rhs ) {
		if (rhs.val == 0)
			return 0;
		return this->value % rhs.val;
	}

	std::string const & toString( void ) {
		std::ostringstream ss;
		ss << this->value;
		return ss.str();
	}

	Operand(T pvalue) {
		value = pvalue;
	}

	Operand(const Operand& rhs) {}
	Operand& operator=(const Operand& rhs) { return *this; }
	~Operand() {}
};
