#include "infix_calculator.h"
#include <iostream>
#include <cmath>
#include <stack>
#include <map>

using namespace std;

// Operatörlerin ve fonksiyonların öncelikleri
int precedence(const string& op) {
    if (op == "+" || op == "-") return 2;
    if (op == "*" || op == "/") return 3;
    if (op == "^") return 4;
    if (op == "sin" || op == "cos" || op == "tan" || op == "ln") return 5; // Fonksiyonlar en yüksek önceliğe sahip
    return 0;
}

// Operatör olup olmadığını kontrol eder
bool isOperator(const string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "^";
}

// Fonksiyon olup olmadığını kontrol eder
bool isFunction(const string& token) {
    return token == "sin" || token == "cos" || token == "tan" || token == "ln";
}

// Sayı olup olmadığını kontrol eder
bool isNumber(const string& token) {
    return !token.empty() && (isdigit(token[0]) || token[0] == '.');
}

// Tokenizer: İfadeyi token'lara ayırır
vector<string> tokenize(const string& infix) {
    vector<string> tokens;
    string token;
    for (size_t i = 0; i < infix.length(); ) {
        if (isspace(infix[i])) {
            i++;
            continue;
        }
        if (isdigit(infix[i]) || infix[i] == '.') {
            token.clear();
            while (i < infix.length() && (isdigit(infix[i]) || infix[i] == '.')) {
                token += infix[i++];
            }
            tokens.push_back(token);
        }
        else if (isalpha(infix[i])) {
            token.clear();
            while (i < infix.length() && isalpha(infix[i])) {
                token += infix[i++];
            }
            tokens.push_back(token);
        }
        else {
            tokens.push_back(string(1, infix[i++]));
        }
    }
    return tokens;
}

// İnfix ifadeyi postfix'e çeviren fonksiyon (Shunting Yard Algoritması)
vector<string> infixToPostfix(const vector<string>& tokens) {
    vector<string> output;
    stack<string> opStack;

    for (const auto& token : tokens) {
        if (isNumber(token) || token == "pi" || token == "e") {
            output.push_back(token);
        }
        else if (isFunction(token)) {
            opStack.push(token);
        }
        else if (token == "(") {
            opStack.push(token);
        }
        else if (token == ")") {
            while (!opStack.empty() && opStack.top() != "(") {
                output.push_back(opStack.top());
                opStack.pop();
            }
            if (!opStack.empty() && opStack.top() == "(") {
                opStack.pop();
            }
            if (!opStack.empty() && isFunction(opStack.top())) {
                output.push_back(opStack.top());
                opStack.pop();
            }
        }
        else if (isOperator(token)) {
            while (!opStack.empty() && ((precedence(opStack.top()) > precedence(token)) || (precedence(opStack.top()) == precedence(token) && token != "^")) && opStack.top() != "(") {
                output.push_back(opStack.top());
                opStack.pop();
            }
            opStack.push(token);
        }
    }
    while (!opStack.empty()) {
        output.push_back(opStack.top());
        opStack.pop();
    }
    return output;
}

// Postfix ifadeyi hesaplayan fonksiyon
double evaluatePostfix(const vector<string>& postfix) {
    stack<double> s;
    map<string, double> constants = { {"pi", M_PI}, {"e", M_E} }; // pi ve e sabitleri

    for (const auto& token : postfix) {
        if (isNumber(token)) {
            double num = stod(token);
            s.push(num);
        }
        else if (token == "pi" || token == "e") {
            s.push(constants[token]);
        }
        else if (isFunction(token)) {
            double a = s.top(); s.pop();
            double result = 0;
            if (token == "sin") result = sin(a);
            else if (token == "cos") result = cos(a);
            else if (token == "tan") result = tan(a);
            else if (token == "ln") result = log(a);
            s.push(result);
        }
        else if (isOperator(token)) {
            double b = s.top(); s.pop();
            double a = s.top(); s.pop();
            double result = 0;
            if (token == "+") result = a + b;
            else if (token == "-") result = a - b;
            else if (token == "*") result = a * b;
            else if (token == "/") result = a / b;
            else if (token == "^") result = pow(a, b);
            s.push(result);
        }
    }
    return s.size() == 1 ? s.top() : NAN;
}
