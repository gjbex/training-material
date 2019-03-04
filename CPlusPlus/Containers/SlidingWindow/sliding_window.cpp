#include <numeric>
#include <stdexcept>

#include "sliding_window.h"

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
        window_.pop();
    window_.push(value);
}
