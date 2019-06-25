
#include <iostream>
#include <fstream>

void parse(std::istream& in) {
    for (std::string line; getline(in, line); ) {
        std::cout << line << "\n";
    }
}

int main(int argc, char const *argv[])
{
    


    if (argc == 2) {
        std::ifstream file(argv[1]);
        parse(file);
    } else {
        parse(std::cin);
    }
    return 0;
}