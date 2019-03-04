#ifndef SLIDING_WINDOW_HDR
#define SLIDING_WINDOW_HDR

#include <list>
#include <numeric>

template<typename T>
class SlidingWindow {
    private:
        size_t size_;
        std::list<T> window_;
    public:
        explicit SlidingWindow(size_t size) : size_ {size} {}
        void add(const T& value);
        T mean() const;
        size_t size() const { return size_; }
        bool is_full() const { return size_ == window_.size(); }
};

template<typename T>
T SlidingWindow<T>::mean() const {
    if (window_.size() == 0)
        throw std::out_of_range("computing mean over empty window");
    T sum = std::accumulate(window_.cbegin(), window_.cend(),
                            static_cast<T>(0));
    return sum/static_cast<T>(window_.size());
}

template<typename T>
void SlidingWindow<T>::add(const T& value) {
    if (is_full())
        window_.pop_front();
    window_.push_back(value);
}

#endif
