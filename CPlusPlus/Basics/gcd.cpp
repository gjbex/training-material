#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "#error: expecting two integers as arguments" << endl;
        return 1;
    }
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);
    if (x <= 0 || y <= 0) {
        cerr << "# error: positive integers expected" << endl;
        return 2;
    }
    while (x != y)
        if (x > y)
            x -= y;
        else
            y -= x;
    cout << x << endl;
    return 0;
}
