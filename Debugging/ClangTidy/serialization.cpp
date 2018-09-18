#include <iostream>
#include <unistd.h>

struct Person {
    std::string first_name;
    std::string last_name;
    int age;
};

std::ostream& operator<<(std::ostream& out, const Person& person);
std::istream& operator>>(std::istream& in, Person& person);

int main(int argc, char *argv[]) {
    bool is_read {false};
    char opt {'\0'};
    while ((opt = getopt(argc, argv, "r")) != -1) {
        switch (opt) {
            case 'r':
                is_read = true;
                break;
            default:
                std::cerr << "#error: invalid option " << opt
                          << std::endl;
                std::terminate();
        }
    }
    if (is_read) {
        Person person;
        std::cin >> person;
        std::cout << "read: " << person << std::endl;
    } else {
        std::string sep(" ");
        Person alice;
        alice.last_name = std::string("Wonderland");
        alice.first_name = std::string("Alice");
        alice.age = 9;
        std::cout << alice << std::endl;
    }
    return 0;
}

std::ostream& operator<<(std::ostream& out, const Person& person) {
    std::string sep(" ");
    return out << person.first_name << sep << person.last_name << sep
               << person.age;
}

std::istream& operator>>(std::istream& in, Person& person) {
    return in >> person.first_name >> person.last_name >> person.age;
}
