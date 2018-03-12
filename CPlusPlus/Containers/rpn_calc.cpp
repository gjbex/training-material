#include <iostream>
#include <stack>
#include <stdlib.h>
#include <sstream>
#include <tuple>

long add(std::stack<long>& stack) throw (std::string);
long substract(std::stack<long>& stack) throw (std::string);
long multiply(std::stack<long>& stack) throw (std::string);
long divide(std::stack<long>& stack) throw (std::string);

int main(int argc, char *argv[]) {
    std::stack<long> stack;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "q"|| line == "quit") {
            return 0;
        } else if (line == "h" || line == "help") {
            std::cout << "Type an integer arithmetic expression "
                << "using the operators '+', '-', '*', '/' in "
                << "reverse Polish notation, or 'quit' to exit."
                << std::endl;
        } else {
            std::istringstream stream(line);
            try {
                std::string token;
                while (std::getline(stream, token, ' ')) {
                    if (token.empty()) {
                        continue;
                    } else if (token == "+") {
                        stack.push(add(stack));
                    } else if (token == "-") {
                        stack.push(substract(stack));
                    } else if (token == "*") {
                        stack.push(multiply(stack));
                    } else if (token == "/") {
                        stack.push(divide(stack));
                    } else {
                        try {
                            stack.push(std::stol(token));
                        } catch (std::invalid_argument) {
                            throw "can't convert '" + token + "' to number";
                        }
                    }
                }
                if (!stack.empty())
                    std::cout << stack.top() << std::endl;
                else
                    std::cerr << "### error: no result" << std::endl;
            } catch (std::string except) {
                std::cerr << "### error: " << except << std::endl;
            }
        }
    }
    return 0;
}

std::tuple<long, long> get_operands(std::stack<long>& stack)
    throw (std::string) {
    if (stack.size() < 2) {
        throw std::string("too few operands on stack");
    } else {
        auto op1 = stack.top();
        stack.pop();
        auto op2 = stack.top();
        stack.pop();
        return std::make_tuple(op1, op2);
    }
}

long add(std::stack<long>& stack) throw (std::string) {
    auto operands = get_operands(stack);
    return std::get<1>(operands) + std::get<0>(operands);
}

long substract(std::stack<long>& stack) throw (std::string) {
    auto operands = get_operands(stack);
    return std::get<1>(operands) - std::get<0>(operands);
}

long multiply(std::stack<long>& stack) throw (std::string) {
    auto operands = get_operands(stack);
    return std::get<1>(operands)*std::get<0>(operands);
}

long divide(std::stack<long>& stack) throw (std::string) {
    auto operands = get_operands(stack);
    if (std::get<0>(operands) == 0)
        throw std::string("division by zero");
    return std::get<1>(operands)/std::get<0>(operands);
}
