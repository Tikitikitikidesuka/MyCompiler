#include <iostream>

#include "parser.h"

int main() {
    Parser parser;

    std::unique_ptr<Expression> a;
    do {
        a = parser.parseStatement();
        if (a != nullptr) std::cout << a->toString() << "\n";
        else std::cout << "nullptr\n";
    } while (a != nullptr);
    

    return 0;
}