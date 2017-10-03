#include <cinttypes>
#include <iostream>

int main() {
    std::int16_t nr_A {0};
    std::int16_t nr_C {0};
    std::int16_t nr_G {0};
    std::int16_t nr_T {0};
    char c;
    while (std::cin >> c) {
        switch (c) {
            case 'A':
                nr_A++;
                break;
            case 'C':
                nr_C++;
                break;
            case 'G':
                nr_G++;
                break;
            case 'T':
                nr_T++;
                break;
            default:
                std::cerr << "### warning: illegal symbol '" << c << "'"
                          << std::endl;
        }
    }
    std::cout << "A: " << nr_A << std::endl;
    std::cout << "C: " << nr_C << std::endl;
    std::cout << "G: " << nr_G << std::endl;
    std::cout << "T: " << nr_T << std::endl;
    return 0;
}
