#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    string str;
    string line;
    while (getline(cin, line))
        str += line + "\n";
    const string target {"words"};
    auto start {str.cbegin()};
    auto it {str.cbegin()};
    while ((it = search(start, str.cend(),
                        target.cbegin(), target.cend())) != str.cend()) {
        cout << "found at " << it - str.cbegin() << endl;
        start = it + 1;
    }
    return 0;
}
