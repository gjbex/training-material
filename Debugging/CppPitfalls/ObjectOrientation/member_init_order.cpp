#include <iostream>

class MyClass {
    public:
        MyClass(int n) : _a {n}, _c {_a + 1} {
            std::cout << "_a = " << _a << ", _c = " << _c << std::endl;
        };
        int sum() const { return _a + _c; };
    private:
        int _c;
        int _a;
};

int main() {
    MyClass c(5);
    std::cout << "sum = " << c.sum() << std::endl;
    return 0;
}
