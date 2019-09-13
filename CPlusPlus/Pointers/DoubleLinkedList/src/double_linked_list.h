#ifndef DOUBLE_LINKED_LIST_HDR
#define DOUBLE_LINKED_LIST_HDR

#include <assert.h>
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
                Element<E_T>(const E_T& value, Element<E_T>* prev, Element<E_T>* next) {
                    value_ = value;
                    set_ptr_diff(prev, next);
                }
                Element<E_T>(E_T&& value, Element<E_T>* prev, Element<E_T>* next) :
                    Element<E_T>(std::move(value), prev, next) {}
                E_T value() const { return value_; }
                void set_value(const E_T value) { value_ = value; }
                Element<E_T>* ptr_diff() { return ptr_diff_; }
                void set_ptr_diff(Element<E_T>* prev, Element<E_T>* next) {
                    ptr_diff_ = addr_xor(prev, next);
                }
        };
        Element<T>* first_;
        Element<T>* last_;
        size_t size_;
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
                iterator(Element<T>* prev, Element<T>* curr) : prev_ {prev}, curr_ {curr} {}
            private:
                Element<T>* prev_;
                Element<T>* curr_;
        };
        iterator begin() const { return iterator(first_); }
        iterator end() const { return iterator(nullptr); }

        LinkedList() : first_ {nullptr}, last_ {nullptr}, size_ {0} {}
        ~LinkedList() { clear(); }
        void clear() {
            while (!is_empty())
                pop_front();
        }
        bool is_empty() const { return size() == 0; }
        const T front() const {return first_->value(); }
        const T back() const { return last_->value(); }
        size_t size() const { return size_; }
        iterator insert(iterator pos, const T& value) {
            // insert doesn't handle edge cases such as empty lists
            assert(pos.curr_ != nullptr);
            auto next = addr_xor(pos.prev_, pos.curr_->ptr_diff());
            Element<T>* element = new Element<T>(value, pos.curr_, next);
            pos.curr_->set_ptr_diff(pos.prev_, element);
            next->set_ptr_diff(element, addr_xor(pos.curr_, next->ptr_diff()));
            ++size_;
            return iterator(pos.curr_, element);
        }
        void push_back(const T& value);
        void push_front(const T& value);
        void pop_back();
        void pop_front();
};

template<typename T>
void LinkedList<T>::push_back(const T& value) {
    LinkedList::Element<T>* element = new Element<T>(value, last_, nullptr);
    if (last_ != nullptr) {
        last_->set_ptr_diff(last_->ptr_diff(), element);
    } else {
        first_ = element;
    }
    last_ = element;
    ++size_;
}

template<typename T>
void LinkedList<T>::push_front(const T& value) {
    Element<T>* element = new Element<T>(value, nullptr, first_);
    if (first_ != nullptr) {
        first_->set_ptr_diff(element, first_->ptr_diff());
    } else {
        last_ = element;
    }
    first_ = element;
    ++size_;
}

template<typename T>
void LinkedList<T>::pop_back() {
    if (size() > 0) {
        Element<T>* element = last_;
        last_ = last_->ptr_diff();
        if (last_ != nullptr) {
            auto new_prev = addr_xor(last_->ptr_diff(), element);
            last_->set_ptr_diff(new_prev, nullptr);
        } else {
            first_ = nullptr;
        }
        delete element;
        --size_;
    }
}

template<typename T>
void LinkedList<T>::pop_front() {
    if (size() > 0) {
        Element<T>* element = first_;
        first_ = first_->ptr_diff();
        // first_->set_ptr_diff(nullptr, first_->ptr_diff() ^ element);
        if (first_ != nullptr) {
            auto new_next = addr_xor(element, first_->ptr_diff());
            first_->set_ptr_diff(nullptr, new_next);
        } else {
            last_ = nullptr;
        }
        delete element;
        --size_;
    }
}

#endif
