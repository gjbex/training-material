#include <iostream>

using namespace std;

int main() {
    string str {"hello"};
    // concatenation
    str += " world!";
    cout << "'" << str << "', length: " << str.length() << endl;
    // substrings
    cout << "from 6: '" << str.substr(6) << "'" << endl;
    cout << "from 6, 5 chars: '" << str.substr(6, 5) << "'" << endl;
    auto pos = str.find("w");
    str[pos] = toupper(str[pos]);
    cout << str << endl;
    pos = 0;
    const string search_str {"o"};
    while ((pos = str.find(search_str, pos)) != string::npos) {
        cout << "found '" << search_str << "' at " << pos << endl;
        pos++;
    }
    str.replace(0, 1, "H");
    str.insert(6, "beautiful ");
    cout << str << endl;
    return 0;
}
