#include <iostream>
#include <exception>

#define EXIT_MISSING_ARG 1
#define EXIT_ARG_TYPE 2
#define EXIT_NEG_ARG 3

using namespace std;

int fac(int n);

int main(int argc, char *argv[]) {
    int n = 0;
    try {
        n = stoi(string(argv[1]));
    } catch(invalid_argument) {
        cerr << "# error: '" << argv[1] << "' can not be converted to int"
             << endl;
        return EXIT_MISSING_ARG;
    } catch(logic_error) {
        cerr << "# error: expecting one argument to fac.exe" << endl;
        return EXIT_ARG_TYPE;
    }
    try {
        cout << fac(n) << endl;
    } catch(invalid_argument e) {
        cerr << "# error: invalid argument, " << e.what() << endl;
        return EXIT_NEG_ARG;
    }
    return 0;
}

int fac(int n) {
    if (n < 0) {
        throw invalid_argument("fac argument must be positive");
    } else {
        int result = 1;
        for (int i = 2; i <= n; i++) {
            result *= i;
        }
        return result;
    }
}
