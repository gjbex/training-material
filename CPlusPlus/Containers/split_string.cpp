#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string& str, const string& delim);

int main(int argc, char *argv[]) {
    string delim = argc > 1 ? string(argv[1]) : string(",");
    while (cin) {
        string line;
        getline(cin, line);
        if (line.length() == 0)
            continue;
        vector<string> parts = split(line, delim);
        for (auto part: parts)
            cout << "'" << part << "'" << endl;
    }
    return 0;
}

vector<string> split(const string& str, const string& delim) {
    vector<string> parts;
    size_t pos = 0, old_pos = 0;
    while ((pos = str.find(delim, old_pos)) != string::npos) {
        parts.push_back(str.substr(old_pos, pos - old_pos));
        old_pos = pos + delim.length();
    }
    parts.push_back(str.substr(old_pos));
    return parts;
}
