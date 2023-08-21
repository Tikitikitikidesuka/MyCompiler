#include <iostream>

#include "parser.h"

int main() {
    Parser parser;

    std::cout << BinaryExpression(
            Operator::OP_ASSIGNMENT,
            std::make_unique<IdExpression>(IdExpression("a")),
            std::make_unique<NumberExpression>(NumberExpression(3))).toString() << "\n";

    std::cout << parser.parseExpr()->toString() << "\n";

    return 0;
}