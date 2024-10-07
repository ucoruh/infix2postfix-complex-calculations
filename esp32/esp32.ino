#include <Arduino.h>
#include <stack>
#include <cmath>
#include <map>
#include <vector>

// Define constants if not available
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_E
#define M_E 2.71828182845904523536
#endif

// Operatörlerin ve fonksiyonların öncelikleri
int precedence(const String& op) {
    if (op == "+" || op == "-") return 2;
    if (op == "*" || op == "/") return 3;
    if (op == "^") return 4;
    if (op == "sin" || op == "cos" || op == "tan" || op == "ln") return 5; // Fonksiyonlar en yüksek önceliğe sahip
    return 0;
}

// Operatör olup olmadığını kontrol eder
bool isOperator(const String& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "^";
}

// Fonksiyon olup olmadığını kontrol eder
bool isFunction(const String& token) {
    return token == "sin" || token == "cos" || token == "tan" || token == "ln";
}

// Sayı olup olmadığını kontrol eder
bool isNumber(const String& token) {
    return token.length() > 0 && (isdigit(token[0]) || token[0] == '.');
}

// Tokenizer: İfadeyi token'lara ayırır
std::vector<String> tokenize(const String& infix) {
    std::vector<String> tokens;
    String token;
    for (size_t i = 0; i < infix.length(); ) {
        if (isspace(infix[i])) {
            i++;
            continue;
        }
        if (isdigit(infix[i]) || infix[i] == '.') {
            token = "";
            while (i < infix.length() && (isdigit(infix[i]) || infix[i] == '.')) {
                token += infix[i++];
            }
            tokens.push_back(token);
        }
        else if (isalpha(infix[i])) {
            token = "";
            while (i < infix.length() && isalpha(infix[i])) {
                token += infix[i++];
            }
            tokens.push_back(token);
        }
        else {
            tokens.push_back(String(infix[i++]));
        }
    }
    return tokens;
}

// İnfix ifadeyi postfix'e çeviren fonksiyon (Shunting Yard Algoritması)
std::vector<String> infixToPostfix(const std::vector<String>& tokens) {
    std::vector<String> output;
    std::stack<String> opStack;

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
            while (!opStack.empty() && ((precedence(opStack.top()) > precedence(token)) || 
                   (precedence(opStack.top()) == precedence(token) && token != "^")) && opStack.top() != "(") {
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
double evaluatePostfix(const std::vector<String>& postfix) {
    std::stack<double> s;
    std::map<String, double> constants = { {"pi", M_PI}, {"e", M_E} }; // pi ve e sabitleri

    for (const auto& token : postfix) {
        if (isNumber(token)) {
            s.push(token.toDouble());
        }
        else if (token == "pi" || token == "e") {
            s.push(constants[token]);
        }
        else if (isFunction(token)) {
            if (s.empty()) {
                Serial.println("Error: Stack is empty when expecting operand for function " + token);
                return NAN;
            }
            double a = s.top(); s.pop();
            double result = 0;
            if (token == "sin") result = sin(a);
            else if (token == "cos") result = cos(a);
            else if (token == "tan") result = tan(a);
            else if (token == "ln") result = log(a);
            s.push(result);
        }
        else if (isOperator(token)) {
            if (s.size() < 2) {
                Serial.println("Error: Not enough operands in stack for operator " + token);
                return NAN;
            }
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
    if (s.size() == 1) {
        return s.top();
    } else {
        Serial.println("Error: Stack should contain only one element after evaluation.");
        return NAN;
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000); // Serial monitor zaman tanıması için

    String infix = "2*(sin(pi/4)+e^(ln(2)+1))/2*pi";
    Serial.println("Infix: " + infix);

    // Tokenize infix expression
    std::vector<String> tokens = tokenize(infix);

    // Convert to postfix
    std::vector<String> postfix = infixToPostfix(tokens);

    // Display postfix expression
    Serial.print("Postfix: ");
    for (const auto& token : postfix) {
        Serial.print(token + " ");
    }
    Serial.println();

    // Evaluate postfix expression
    double result = evaluatePostfix(postfix);
    Serial.print("Sonuç: ");
    Serial.println(result, 10);  // 10 basamaklı gösterim
}

void loop() {
    // ESP32'nin ana döngüsü, burada sürekli tekrar eden bir işlem yok.
}
