#ifndef DOUBLE_LINKED_LIST_HDR
#define DOUBLE_LINKED_LIST_HDR

#include <cstdint>

template<typename T>
T addr_xor(T prev, T next) {
    return reinterpret_cast<T>(reinterpret_cast<uintptr_t>(prev) ^
                               reinterpret_cast<uintptr_t>(next));
}

template<typename T>
class LinkedList {
    private:
        template<typename E_T>
        class Element {
            friend class LinkedList;
            private:
                E_T value_;
                Element<E_T>* ptr_diff_;
            public:
                Element<E_T>(E_T value, Element<E_T>* prev, Element<E_T>* next) {
                    value_ = value;
                    this->set_ptr_diff(prev, next);
                }
                E_T value() const { return value_; }
                void set_value(const E_T value) { value_ = value; }
                Element<E_T>* ptr_diff() { return ptr_diff_; }
                void set_ptr_diff(Element<E_T>* prev, Element<E_T>* next) {
                    ptr_diff_ = addr_xor(prev, next);
                }
        };
        Element<T>* first_;
        Element<T>* last_;
    public:
        class iterator {
            friend class LinkedList;
            public:
                T operator *() const { return curr_->value(); }
                const iterator& operator++() {
                    Element<T>* tmp = curr_;
                    curr_ = addr_xor(prev_, curr_->ptr_diff());
                    prev_ = tmp;
                    return *this;
                }
                iterator operator++(int) {
                    iterator copy(*this);
                    Element<T>* tmp = curr_;
                    curr_ = addr_xor(prev_, curr_);
                    prev_ = tmp;
                    return copy;
                }
                bool operator==(const iterator& other) const { return curr_ == other.curr_; }
                bool operator!=(const iterator& other) const { return curr_ != other.curr_; }
            protected:
                iterator(Element<T>* ptr) : prev_ {nullptr}, curr_ {ptr} {}
            private:
                Element<T>* prev_;
                Element<T>* curr_;
        };
        iterator begin() const { return iterator(first_); }
        iterator end() const { return iterator(nullptr); }

        LinkedList() : first_ {nullptr}, last_ {nullptr} {}
        bool is_empty() const { return first_ == nullptr; }
        const T front() const {return first_->value(); }
        const T back() const { return last_->value(); }
        void push_back(T value);
        void push_front(T value);
        T pop_back();
        T pop_front();
};

template<typename T>
void LinkedList<T>::push_back(T value) {
    LinkedList::Element<T>* element = new Element<T>(value, last_, nullptr);
    if (last_ != nullptr) {
        last_->set_ptr_diff(last_->ptr_diff(), element);
    } else {
        first_ = element;
    }
    last_ = element;
}

template<typename T>
void LinkedList<T>::push_front(T value) {
    Element<T>* element = new Element<T>(value, nullptr, first_);
    if (first_ != nullptr) {
        first_->set_ptr_diff(element, first_->ptr_diff());
    } else {
        last_ = element;
    }
    first_ = element;
}

template<typename T>
T LinkedList<T>::pop_back() {
    Element<T>* element = last_;
    last_ = last_->ptr_diff();
    if (last_ != nullptr) {
        auto new_prev = addr_xor(last_->ptr_diff(), element);
        last_->set_ptr_diff(new_prev, nullptr);
    } else {
        first_ = nullptr;
    }
    T value = element->value();
    delete element;
    return value;
}

template<typename T>
T LinkedList<T>::pop_front() {
    Element<T>* element = first_;
    first_ = first_->ptr_diff();
    // first_->set_ptr_diff(nullptr, first_->ptr_diff() ^ element);
    if (first_ != nullptr) {
        auto new_next = addr_xor(element, first_->ptr_diff());
        first_->set_ptr_diff(nullptr, new_next);
    } else {
        last_ = nullptr;
    }
    T value = element->value();
    delete element;
    return value;
}

#endif
