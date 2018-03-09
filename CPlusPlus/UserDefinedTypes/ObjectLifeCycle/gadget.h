#ifndef GADGET_HDR
#define GADGET_HDR

#include <iostream>

static int _id_counter {0};

class Gadget {
    private:
        int _value;
        int _id;
    public:
        Gadget() : _value {0}, _id {++_id_counter} {
            std::cerr << "Gadget " << _id << "()" << std::endl;
        };
        Gadget(int value) : _value {value}, _id {++_id_counter} {
            std::cerr << "Gadget " << _id << "(" << _value << ")"
                      << std::endl;
        };
        Gadget(const Gadget& other) : _id {++_id_counter} {
            _value = other._value;
            std::cerr << "copy Gadget " << other._id << "(" << _value << ")"
                      << " to " << _id << std::endl;
        };
        Gadget& operator=(const Gadget& other) {
            _value = other._value;
            std::cerr << "copy assign "
                      << "Gadget " << other._id << "(" << _value << ")"
                      << " to " << _id << std::endl;
            return *this;
        };
        Gadget(const Gadget&& other) : _id {++_id_counter} {
            _value = other._value;
            std::cerr << "move Gadget " << other._id << "(" << _value << ")"
                      << " to " << _id << std::endl;
        };
        Gadget& operator=(const Gadget&& other) {
            _value = other._value;
            std::cerr << "move assign "
                      << "Gadget " << other._id << "(" << _value << ")"
                      << " to " << _id << std::endl;
            return *this;
        };
        ~Gadget() {
            std::cerr << "~Gadget " << _id <<  std::endl;
        };
        int id() const { return _id; };
        void greet() const {
            std::cout << "Hi from " << _id  << " with " << _value
                      << std::endl;
        };
};

#endif
