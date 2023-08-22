#include <iostream>

#include "parser.h"

int main() {
    Parser parser;

    /*
    std::cout << BinaryExpression(
            Operation::OP_ASSIGNMENT,
            std::make_unique<IdExpression>(IdExpression("a")),
            std::make_unique<NumberExpression>(NumberExpression(3))).toString() << "\n";
            */

    std::unique_ptr<Expression> a;
    do {
        a = parser.parseExpr();
        if (a != nullptr) std::cout << a->toString() << "\n";
        else std::cout << "nullptr\n";
    } while (a != nullptr);
    

    return 0;
}