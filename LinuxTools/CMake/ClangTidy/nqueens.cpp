#include <iostream>
#include <optional>
#include <sstream>

#include "state.h"

using Stack = std::vector<State>;

void solve(Stack& stack);
std::optional<State> solve(const int size);
void show_board(std::ostream& out, const State& state);

int main(int argc, char* argv[]) {
    int size {4};
    if (argc > 1) {
        size = std::stoi(argv[1]);
    }
    auto solution = solve(size);
    if (solution) {
        show_board(std::cout, *solution);
    } else {
        std::cout << "no solution" << std::endl;
    }
    return 0;
}

void solve(Stack& stack) {
    while (!stack.empty() && stack.back().has_options()) {
        int position = stack.back().get_option();
        stack.emplace_back(stack.back(), position);
        solve(stack);
    }
    if (!stack.empty() && !stack.back().is_solution()) {
        stack.pop_back();
        solve(stack);
    }
}

std::optional<State> solve(const int size) {
    Stack stack;
    stack.emplace_back(size);
    solve(stack);
    if (!stack.empty() && stack.back().is_solution()) {
        return stack.back();
    } else {
        return {};
    }
}

std::string create_divider(const int size) {
    std::string divider {"+"};
    std::stringstream divider_stream(divider);
    for (int col = 0; col < size; ++col) {
        divider_stream << "---+";
    }
    divider_stream << "\n";
    return divider_stream.str();
}

void show_board(std::ostream& out, const State& state) {
    std::string divider {create_divider(state.size())};
    Pos_t positions = state.positions();
    out << divider;
    for (int row = 0; row < state.size(); ++row) {
        out << "|";
        for (int col = 0; col < state.size(); ++col) {
            if (col == positions[row]) {
                out << " o |";
            } else {
                out << "   |";
            }
        }
        out << "\n" << divider;
    }
}
