
#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <limits.h>
#include <cfloat>
#include <regex>
#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include "AbstractVM.hpp"


AbstractVM::AbstractVM(int ac, char const** av) : argc(ac), argv(av) {
    isFile = (ac == 2);
    // TODO FILE ERROR HANDLING
    factory = OperandFactory();
    if (isFile) {
        std::ifstream file(argv[1]);
        parse(file);
    }
    else {
        parse(std::cin);
    }
}

AbstractVM::~AbstractVM() {

}

void AbstractVM::parse(std::istream& input) {
    for (std::string line; getline(input, line);) {
        //std::cerr << line << "\n";
        if (!isFile && line.find(";;") != std::string::npos)
            return;

        // remove everything after ";" comment
        line = line.substr(0, line.find(";"));

        std::stringstream ss(line);

        std::string tok1;
        if (std::getline(ss, tok1, ' ')) {
            if (tok1 == "push")         avm_push(ss);
            else if (tok1 == "pop")     avm_pop();
            else if (tok1 == "dump")    avm_dump();
            else if (tok1 == "assert")  avm_assert(ss);
            else if (tok1 == "add")     avm_do_op('+');
            else if (tok1 == "sub")     avm_do_op('-');
            else if (tok1 == "mul")     avm_do_op('*');
            else if (tok1 == "div")     avm_do_op('/');
            else if (tok1 == "mod")     avm_do_op('%');
            else if (tok1 == "print")   avm_print();
            else if (tok1 == "exit")    avm_exit();
            else throw ParserException("Unidentified token");

            std::string tok2;
            if (std::getline(ss, tok2, ' ')) {
                throw ParserException("Excessive input tokens");
            }
        }
    }
    throw ParserException("No exit found");
}

eOperandType AbstractVM::avm_get_value(std::string& tok, std::string& ret) {

    unsigned start = tok.find("(") + 1;
    unsigned len = tok.find(")") - start;
    if (std::regex_match(tok, std::regex("int8\\(-?[0-9]\\d*\\)$") )) {
        ret = tok.substr(start, len);
        return eOperandType::Int8;
    } else if (std::regex_match(tok, std::regex("int16\\(-?[0-9]\\d*\\)$") )) {
        ret = tok.substr(start, len);
        return eOperandType::Int16;
    } else if (std::regex_match(tok, std::regex("int32\\(-?[0-9]\\d*\\)$") )) {
        ret = tok.substr(start, len);
        return eOperandType::Int32;
    } else if (std::regex_match(tok, std::regex("float\\(-?[0-9]\\d*(\\.\\d+)\\)$") )) {
        ret = tok.substr(start, len);
        return eOperandType::Float;
    } else if (std::regex_match(tok, std::regex("double\\(-?[0-9]\\d*(\\.\\d+)\\)$") )) {
        ret = tok.substr(start, len);
        return eOperandType::Double;
    }
    throw ParserException("Invalid VALUE");
}

void AbstractVM::avm_push(std::stringstream& ss) {
    std::string tok;
    if (std::getline(ss, tok, ' ')) {
        std::string ret;
        eOperandType tt = avm_get_value(tok, ret);
        if (tt < Float) {
            long long test = std::stoll(ret.c_str());
            if ((tt == Int8) && (test > SCHAR_MAX || test < SCHAR_MIN))
                throw ParserException("Int8 Overflow");
            else if ((tt == Int16) && (test > SHRT_MAX || test < SHRT_MIN))
                throw ParserException("Int16 Overflow");
            else if ((tt == Int32) && (test > INT_MAX || test < INT_MIN))
                throw ParserException("Int32 Overflow");
        } else {
            long double test = std::stold(ret.c_str());
            if ((tt == Float) && (test > FLT_MAX || test < -FLT_MAX))
                throw ParserException("Float Overflow");
            else if ((tt == Double) && (test > DBL_MAX || test < -DBL_MAX))
                throw ParserException("Double Overflow");

        }
        const IOperand* test = factory.createOperand(tt, ret);
        stack.push_back(test);
    } else throw ParserException("No VALUE after push");
}

void AbstractVM::avm_pop() {
    // unstacks a value, ERROR on empty
    if (stack.size() > 0) {
        stack.pop_back();
    } else throw ParserException("Pop on empty stack"); 
}

void AbstractVM::avm_dump() {
    // display each value, from recent to oldest, without change
    // seperated by newline
    for (std::list<const IOperand*>::reverse_iterator i = stack.rbegin(); 
        i != stack.rend(); ++i ) {
        std::cout << (*i)->toString() << "\n";
    }
}

void AbstractVM::avm_assert(std::stringstream& ss) {
    // assert token has same type and value as top of stack
    std::string tok;
    if (std::getline(ss, tok, ' ')) {
        std::string ret;
        eOperandType type = avm_get_value(tok, ret);
        const IOperand* test = factory.createOperand(type, ret);
        auto& op1 = *std::prev(stack.end(), 1);
        if (test->toString() != op1->toString())
           throw ParserException("Assert failed"); 
    } else throw ParserException("No VALUE after assert");
    // ERROR if assert is not true
    // else no value after assert ERROR
}

void AbstractVM::avm_do_op(char op) {
    // unstack 2 then add
    if (stack.size() > 1) {
        auto& op1 = *std::prev(stack.end(), 1);
        auto& op2 = *std::prev(stack.end(), 2);
        const IOperand* res;
        if (op == '+') res = *op2 + *op1;
        else if (op == '-') res = *op2 - *op1;
        else if (op == '*') res = *op2 * *op1;
        else if (op == '/') res = *op2 / *op1;
        else if (op == '%') res = *op2 % *op1;
        stack.pop_back();
        stack.pop_back();
        stack.push_back(res);
    } else throw ParserException("Not enough values in stack");
}

void AbstractVM::avm_print() {
    // assert value is Int8, then interprets it as ASCII value
    // displays character on standardoutput
    auto& op1 = *std::prev(stack.end(), 1);
    if (op1->getType() == Int8)
    {
        std::cout << static_cast<char>(std::stoll(op1->toString()));
    } else throw ParserException("\"print\" instruction can only handle int8");
}

void AbstractVM::avm_exit() {
    exit(0);
}
