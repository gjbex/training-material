#include <iostream>
#include <unordered_map>
#include <regex>

using namespace std;

int main() {
    string line;
    regex pat {R"((\w+))"};
    unordered_map<string, int> counter;
    while (getline(cin, line)) {
        for (sregex_iterator token(line.begin(), line.end(), pat);
                token != sregex_iterator {}; token++) {
            string word = (*token)[1];
            if (counter.find(word) == counter.end())
                counter[word] = 0;
            counter[word]++;
        }
    }
    for (auto c: counter)
        cout << c.first << ": " << c.second << endl;
    return 0;
}
