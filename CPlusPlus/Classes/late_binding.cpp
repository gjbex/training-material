#include <iostream>
#include <memory>

struct Base {
    explicit Base(int id) : id_ {id} {
        std::cout << "Base(" << id_ << ")" << std::endl;
    }
    void hello() const {
        std::cout << "hello from Base(" << id_ << ")" << std::endl;
    }
    virtual void bye() const {
        std::cout << "bye from Base(" << id_ << ")" << std::endl;
    }
    ~Base() {
        std::cout << "~Base(" << id_ << ")" << std::endl;
    }
    protected:
        int id_;
};

struct Derived1 : public Base {
    explicit Derived1(int id) : Base(id) {
        std::cout << "Derived1(" << id_ << ")" << std::endl;
    }
    void hello() const {
        std::cout << "hello from Derived1(" << id_ << ")" << std::endl;
    }
    void bye() const {
        std::cout << "bye from Derived1(" << id_ << ")" << std::endl;
    }
    virtual ~Derived1() {
        std::cout << "~Derived1(" << id_ << ")" << std::endl;
    }
};

struct Derived2 : public Derived1 {
    explicit Derived2(int id) : Derived1(id) {
        std::cout << "Derived2(" << id_ << ")" << std::endl;
    }
    virtual void hello() const {
        std::cout << "hello from Derived2(" << id_ << ")" << std::endl;
    }
    void bye() const {
        std::cout << "bye from Derived2(" << id_ << ")" << std::endl;
    }
    ~Derived2() {
        std::cout << "~Derived2(" << id_ << ")" << std::endl;
    }
};

int main() {
    std::unique_ptr<Base> bp1, bp2, bp3;
    std::unique_ptr<Derived1> dp1, dp2;
    bp1 = std::make_unique<Base>(1);
    bp2 = std::make_unique<Derived1>(2);
    bp3 = std::make_unique<Derived2>(3);
    dp1 = std::make_unique<Derived1>(4);
    dp2 = std::make_unique<Derived2>(5);
    bp1->hello();
    bp2->hello();
    bp3->hello();
    dp1->hello();
    dp2->hello();
    bp1->bye();
    bp2->bye();
    bp3->bye();
    dp1->bye();
    dp2->bye();
    return 0;
}
