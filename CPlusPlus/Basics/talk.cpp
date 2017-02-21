#include <iostream>

using namespace std;

int main() {
    const string question {"Who are you?"};
    const string greeting {"Hi "};
    const string bye {"Bye!"};
    string name;
    cout << "Type 'quit' or press Ctrl-d to exit" << endl;
    cout << question << endl;
    while (cin >> name) {
        if (name == "quit")
            break;
        cout << greeting << name << "!" << endl;
    }
    cout << bye << endl;
    return 0;
}
