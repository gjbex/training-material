#include <iostream>

int main(int argc __attribute__((unused)),
         char *argv[] __attribute__((unused))) {
    std::string line;
    double sum {0.0};
    while (std::getline(std::cin, line)) {
        if (line[0] == '#')
            continue;
        sum += std::stof(line);
    }
    std::cout << "sum = " << sum << std::endl;
    return 0;
}
