#include <iostream>
#include <regex>
#include <vector>

using namespace std;

int main() {
    regex expr {R"([acgt]+)"};
    regex expr_icase(R"([acgt]+)", regex::icase);
    const vector<string> strs {"aagt", "abgt", "AAGT", "ABGT"};
    for (auto str: strs) {
        if (regex_match(str, expr))
            cout << "case sensitive: " << str << endl;
        if (regex_match(str, expr_icase))
            cout << "case insensitive: " << str << endl;
    }
    return 0;
}
