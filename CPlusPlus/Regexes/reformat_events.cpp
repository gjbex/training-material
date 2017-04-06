#include <iostream>
#include <regex>

using namespace std;

int main() {
    regex expr {R"((\w+)\s+(\d+))"};
    string line;
    while (getline(cin, line)) {
        string new_line = regex_replace(line, expr, "$1_$2");
        cout << new_line << endl;
    }
    return 0;
}
