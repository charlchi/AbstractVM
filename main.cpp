 
#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <regex>
#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include "AbstractVM.hpp"

int main(int argc, char const* argv[])
{
    try {
        AbstractVM env = AbstractVM(argc, argv);
    }
    catch(const std::exception& e) {
        std::cout << "\033[1;31mError:\033[0m " << e.what() << '\n';
    }
    return 0;
}