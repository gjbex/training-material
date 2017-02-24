#include <iostream>
#include <exception>

const int EXIT_MISSING_ARG = 1;
const int EXIT_ARG_TYPE = 2;
const int EXIT_NEG_ARG = 3;

using namespace std;

int fac(int n);

int main(int argc, char *argv[]) {
    int n = 0;
    try {
        n = stoi(string(argv[1]));
    } catch(invalid_argument) {
        cerr << "# error: '" << argv[1] << "' can not be converted to int"
             << endl;
        exit(EXIT_ARG_TYPE);
    } catch(logic_error) {
        cerr << "# error: expecting one argument to fac.exe" << endl;
        exit(EXIT_MISSING_ARG);
    }
    try {
        cout << fac(n) << endl;
    } catch(invalid_argument e) {
        cerr << "# error: invalid argument, " << e.what() << endl;
        exit(EXIT_NEG_ARG);
    }
    return 0;
}

int fac(int n) {
    if (n < 0) {
        string msg("fac argument ");
        msg += to_string(n) + ", must be positive";
        throw invalid_argument(msg);
    } else {
        int result = 1;
        for (int i = 2; i <= n; i++) {
            result *= i;
        }
        return result;
    }
}
