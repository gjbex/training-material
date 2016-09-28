#include <iostream>
#include <stack>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <tuple>

long add(std::stack<long>& stack) throw (const char *);
long substract(std::stack<long>& stack) throw (const char *);
long multiply(std::stack<long>& stack) throw (const char *);
long divide(std::stack<long>& stack) throw (const char *);

int main(int argc, char *argv[]) {
    std::stack<long> stack;
    for (std::string line; std::getline(std::cin, line); ) {
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
                for (std::string token;
                        std::getline(stream, token, ' '); ) {
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
                        char *end_p;
                        long value = strtol(token.c_str(), &end_p, 10);
                        if (*end_p == 0)
                            stack.push(value);
                        else
                            std::cerr << "# error: '"
                                << token << "' is invalid" << std::endl;
                    }
                }
                if (!stack.empty())
                    std::cout << stack.top() << std::endl;
                else
                    std::cerr << "# error: no result" << std::endl;
            } catch (const char *except) {
                std::cerr << "# error: " << except << std::endl;
            }
        }
    }
    return 0;
}

std::tuple<long, long> get_operands(std::stack<long>& stack)
    throw (const char *) {
    if (stack.size() < 2) {
        throw "too few operands on stack";
    } else {
        auto op1 = stack.top();
        stack.pop();
        auto op2 = stack.top();
        stack.pop();
        return std::make_tuple(op1, op2);
    }
}

long add(std::stack<long>& stack) throw (const char *) {
    auto operands = get_operands(stack);
    return std::get<1>(operands) + std::get<0>(operands);
}

long substract(std::stack<long>& stack) throw (const char *) {
    auto operands = get_operands(stack);
    return std::get<1>(operands) - std::get<0>(operands);
}

long multiply(std::stack<long>& stack) throw (const char *) {
    auto operands = get_operands(stack);
    return std::get<1>(operands)*std::get<0>(operands);
}

long divide(std::stack<long>& stack) throw (const char *) {
    auto operands = get_operands(stack);
    return std::get<1>(operands)/std::get<0>(operands);
}
