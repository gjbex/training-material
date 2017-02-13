#include <iostream>

using namespace std;

int fac(int n);

int main(int argc, char *argv[]) {
    if (argc < 1) {
        cerr << "#error: expecting one integer as argument" << endl;
        return 1;
    }
    int n {0};
   try {
      n = stoi(string(argv[1]));
    } catch (invalid_argument) {
        cerr << "# error: argument can not be converted to an integer"
             << endl;
        return 3;
    }
    if (n < 0) {
        cerr << "# error: argument should be positive" << endl;
        return 4;
    }
    cout << fac(n) << endl;
    return 0;
}

int fac(int n) {
    int val {1};
    for (int i = 2; i <= n; i++)
        val *= i;
    return val;
}
