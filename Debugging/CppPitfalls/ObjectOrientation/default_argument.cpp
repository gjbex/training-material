#include <iostream>

struct BaseClass {
    virtual std::string method1() const {
        return "BaseClass::method1";
    };
    virtual std::string method2() const {
        return "BaseClass::method2";
    };
    virtual std::string method3(int i = 0) const {
        return "BaseClass::method3 with " + std::to_string(i);
    };
};

struct DerivedClass : public BaseClass {
    std::string method1() const {
        return "DerivedClass::method1";
    };
    std::string method2(int i = 3) const {
        return "DerivedClass::method2 with " + std::to_string(i);
    };
    std::string method3(int i = 5) const {
        return "DerivedClass::method3 with " + std::to_string(i);
    };
};

int main() {
    DerivedClass d;
    BaseClass *b_ptr = static_cast<BaseClass*>(&d);
    std::cout << "d.method1(): " << d.method1() << std::endl;
    std::cout << "d.method2(): " << d.method2() << std::endl;
    std::cout << "d.method2(5): " << d.method2(5) << std::endl;
    std::cout << "d.method3(): " << d.method3() << std::endl;
    std::cout << "d.method3(15): " << d.method3(15) << std::endl;
    std::cout << "b_prt->method1(): " << b_ptr->method1() << std::endl;
    std::cout << "b_prt->method2(): " << b_ptr->method2() << std::endl;
    std::cout << "b_prt->method3(): " << b_ptr->method3() << std::endl;
    std::cout << "b_prt->method3(15): " << b_ptr->method3(15) << std::endl;
    /* this will not compile
    std::cout << "b_prt->method2(5): " << b_ptr->method2(5) << std::endl;
    */
    return 0;
}
