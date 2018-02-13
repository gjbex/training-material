#include <iostream>

int main(int argc __attribute__((unused)),
         char *argv[] __attribute__((unused))) {
    if (std::string str; std::cin >> str) {
        std::cout << "read '" << str << "'" << std::endl;
    }
    return 0;
}
