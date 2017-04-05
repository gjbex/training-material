#include <iostream>
#include <regex>

using namespace std;

int main() {
    const string str {"2.5, -1.3, alpha"};
    regex expr {R"(([^ ,]+))"};
    const string new_str = regex_replace(str, expr, "'$1'");
    cout << new_str << endl;
    return 0;
}
