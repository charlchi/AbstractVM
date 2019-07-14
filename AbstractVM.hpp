
#ifndef ABSTRACTVM_HPP
#define ABSTRACTVM_HPP


#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <regex>
#include "IOperand.hpp"
#include "OperandFactory.hpp"

class AbstractVM {
    int argc;
    char const** argv;
    int isFile;
    OperandFactory factory;
    std::list<const IOperand*> stack;
public:
    AbstractVM(int ac, char const** av);
    ~AbstractVM(void);
    void parse(std::istream& input);
    IOperand* avm_stack_pop(void);
    eOperandType avm_get_value(std::string& tok, std::string& ret);
    void avm_push(std::stringstream& ss);
    void avm_pop(void);
    void avm_dump(void);
    void avm_assert(std::stringstream& ss);
    void avm_do_op(char op);
    void avm_print(void);
    void avm_exit(void);
    class ParserException : public std::exception {
        std::string message;
    public:
        ParserException(const std::string& msg) : message(msg) {}
        virtual const char* what() const throw () {
            return message.c_str();
        }
    };
};

#endif // ABSTRACTVM_HPP