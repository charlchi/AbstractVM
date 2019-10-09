
#ifndef OPERAND_H
#define OPERAND_H

#include <cstdlib>
#include <cstring>
#include <string>
#include <math.h>
#include <ostream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <limits.h>
#include <exception>
#include <cfloat>
#include "OperandFactory.hpp"

template <class T>
class Operand : public IOperand
{
	T value;
	eOperandType type;
	const OperandFactory* factory;
	std::string strval;
public:

	// "The pure method getPrecision allows to get the precision
	// of an operand. When an operation uses two operands from two
	// types the comparison of their precisions allows to figure
	// out the result type of the operation."
	int getPrecision( void ) const {
		return type;
	}

	eOperandType getType( void ) const {
		return type;
	}

	class AVMException : public std::exception {
		std::string message;
	public:
	    AVMException(const std::string& msg) : message(msg) {}
	    virtual const char* what() const throw () {
       		return message.c_str();
    	}
	};

	IOperand const * doOperator( IOperand const & rhs, std::string op ) const {
		
		std::ostringstream ss;
		eOperandType tt = (type < rhs.getType()) ? rhs.getType() : type;

		if (tt < Float) {
			long long lhs_long = std::stoll(strval);
			long long rhs_long = std::stoll(rhs.toString());
			long long res;
			if ((op == "/") && rhs_long == 0)
				throw AVMException("Invalid division by zero");
			if ((op == "%") && rhs_long == 0)
				throw AVMException("Invalid mod by zero");
			if      (op == "+") res = (lhs_long + rhs_long);
			else if (op == "-") res = (lhs_long - rhs_long);
			else if (op == "*") res = (lhs_long * rhs_long);
			else if (op == "/") res = (lhs_long / rhs_long);
			else if (op == "%") res = (lhs_long % rhs_long);
			// test bounds
			if ((tt == Int8) && (res > SCHAR_MAX || res < SCHAR_MIN))
				throw AVMException("Int8 Overflow");
			else if ((tt == Int16) && (res > SHRT_MAX || res < SHRT_MIN))
				throw AVMException("Int16 Overflow");
			else if ((tt == Int32) && (res > INT_MAX || res < INT_MIN))
				throw AVMException("Int32 Overflow");
			ss << res;

		} else {
			long double lhs_double = std::stold(strval);
			long double rhs_double = std::stold(rhs.toString());
			long double res;
			if ((op == "/") && rhs_double == 0)
				throw AVMException("Invalid division by zero");
			if ((op == "%") && rhs_double == 0)
				throw AVMException("Invalid mod by zero");
			if      (op == "+") res = (lhs_double + rhs_double);
			else if (op == "-") res = (lhs_double - rhs_double);
			else if (op == "*") res = (lhs_double * rhs_double);
			else if (op == "/") res = (lhs_double / rhs_double);
			else if (op == "%") res = fmod(lhs_double, rhs_double);
			// test bounds
			if ((tt == Float) && (res > FLT_MAX || res < -FLT_MAX))
				throw AVMException("Float Overflow");
			else if ((tt == Double) && (res > DBL_MAX || res < -DBL_MAX))
				throw AVMException("Double Overflow");
			ss << std::setprecision(14) << res;
		}
		// error test for division zero
		return (factory->createOperand(tt, ss.str()));
	}

	IOperand const * operator+( IOperand const & rhs ) const { return this->doOperator(rhs, "+"); }
	IOperand const * operator-( IOperand const & rhs ) const { return this->doOperator(rhs, "-"); }
	IOperand const * operator*( IOperand const & rhs ) const { return this->doOperator(rhs, "*"); }
	IOperand const * operator/( IOperand const & rhs ) const { return this->doOperator(rhs, "/"); }
	IOperand const * operator%( IOperand const & rhs ) const { return this->doOperator(rhs, "%"); }

	std::string const & toString( void ) const { return strval; }

	Operand(T pvalue, const OperandFactory* of, eOperandType tt) {
		type = tt;
		value = pvalue;
		factory = of;
		std::stringstream ss(std::stringstream::out);
		ss << std::setprecision(14) << +pvalue;
		strval = ss.str();
	}

	Operand(std::string ss) { value = 0; }
	Operand(const Operand& rhs) {}
	Operand& operator=(const Operand& rhs) { return *this; }
	~Operand() {}
};

#endif // OPERAND_H