#include "infix_calculator.h"
#include <iostream>

int main() {
    std::string infix = "2*(sin(pi/4)+e^(ln(2)+1))/2*pi";
    std::cout << "Infix: " << infix << std::endl;

    // Tokenize infix expression
    std::vector<std::string> tokens = tokenize(infix);

    // Convert to postfix
    std::vector<std::string> postfix = infixToPostfix(tokens);

    // Display postfix expression
    std::cout << "Postfix: ";
    for (const auto& token : postfix) {
        std::cout << token << " ";
    }
    std::cout << std::endl;

    // Evaluate postfix expression
    double result = evaluatePostfix(postfix);
    std::cout << "Sonuç: " << result << std::endl;

    return 0;
}
