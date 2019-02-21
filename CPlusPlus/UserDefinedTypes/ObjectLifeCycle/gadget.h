#ifndef GADGET_HDR
#define GADGET_HDR

#include <iostream>

static int id_counter_ {0};

struct Gadget {
    private:
        int value_;
        int id_;
    public:
        Gadget() : value_ {0}, id_ {++id_counter_} {
            std::cerr << "Gadget " << id_ << "()" << std::endl;
        };
        Gadget(int value) : value_ {value}, id_ {++id_counter_} {
            std::cerr << "Gadget " << id_ << "(" << value_ << ")"
                      << std::endl;
        };
        Gadget(Gadget& other) : id_ {++id_counter_} {
            value_ = other.value_;
            std::cerr << "copy Gadget " << other.id_ << "(" << value_ << ")"
                      << " to " << id_ << std::endl;
        };
        Gadget& operator=(const Gadget& other) {
            value_ = other.value_;
            std::cerr << "copy assign "
                      << "Gadget " << other.id_ << "(" << value_ << ")"
                      << " to " << id_ << std::endl;
            return *this;
        };
        Gadget(Gadget&& other) : id_ {++id_counter_} {
            value_ = other.value_;
            std::cerr << "move Gadget " << other.id_ << "(" << value_ << ")"
                      << " to " << id_ << std::endl;
        };
        Gadget& operator=(Gadget&& other) {
            value_ = other.value_;
            std::cerr << "move assign "
                      << "Gadget " << other.id_ << "(" << value_ << ")"
                      << " to " << id_ << std::endl;
            return *this;
        };
        ~Gadget() {
            std::cerr << "~Gadget " << id_ <<  std::endl;
        };
        int id() const { return id_; };
        void greet() const {
            std::cout << "Hi from " << id_  << " with " << value_
                      << std::endl;
        };
};

#endif
