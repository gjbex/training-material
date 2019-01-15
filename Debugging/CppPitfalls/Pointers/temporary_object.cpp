#include <iostream>
#include <memory>

class BaseCounter {
    public:
        BaseCounter(int init = 0) : _count {init} {};
        virtual void inc() { ++_count; };
        int value() const { return _count; };
    protected:
        int _count;
};

class DerivedCounter : public BaseCounter {
    public:
        void inc() override { _count += 2; };
};

int main() {
    DerivedCounter d;
    std::cout << "original d: " << d.value() << std::endl;
    d.inc();
    std::cout << "d.inc(): " << d.value() << std::endl;
    static_cast<BaseCounter>(d).inc();
    std::cout << "(static_cast<BaseCounter>d).inc(): " << d.value()
              << std::endl;
    BaseCounter b = static_cast<BaseCounter>(d);
    std::cout << "original b: " << b.value() << std::endl;
    b.inc();
    std::cout << "b.inc(): " << b.value() << std::endl;
    std::cout << "d: " << d.value() << std::endl;
    return 0;
}
