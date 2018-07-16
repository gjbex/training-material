#include <iostream>

int main() {
    const std::string question {"Who are you?"};
    const std::string greeting {"Hi "};
    const std::string bye {"Bye!"};
    std::string name;
    std::cout << "Type 'quit' or press Ctrl-d to exit" << std::endl;
    std::cout << question << std::endl;
    while (std::cin >> name) {
        if (name == "quit")
            break;
        std::cout << greeting << name << "!" << std::endl;
    }
    std::cout << bye << std::endl;
    return 0;
}
