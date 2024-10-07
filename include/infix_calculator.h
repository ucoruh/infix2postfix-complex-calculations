#ifndef INFIX_CALCULATOR_H
#define INFIX_CALCULATOR_H

#include <string>
#include <vector>

// Fonksiyon prototipleri
int precedence(const std::string& op);
bool isOperator(const std::string& token);
bool isFunction(const std::string& token);
bool isNumber(const std::string& token);
std::vector<std::string> tokenize(const std::string& infix);
std::vector<std::string> infixToPostfix(const std::vector<std::string>& tokens);
double evaluatePostfix(const std::vector<std::string>& postfix);

#endif  // INFIX_CALCULATOR_H
