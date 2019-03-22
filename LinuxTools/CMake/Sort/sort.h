#ifndef SORT_HDR
#define SORT_HDR

#include <utility>

template<typename T>
void naive_sort(T& data) {
    for (long i = 0; i < static_cast<long>(data.size()) - 1; ++i)
        for (std::size_t j = i + 1; j < data.size(); ++j)
            if (data[j] < data[i])
                std::swap(data[i], data[j]);
}

template<typename T>
long partition(T& data, const long low, const long high) {
    auto low_idx {low - 1};
    for (long i = low; i < high; ++i)
        if (data[i] < data[high])
            std::swap(data[++low_idx], data[i]);
    std::swap(data[++low_idx], data[high]);
    return low_idx;
}

template<typename T>
void quick_sort(T& data, const long low, const long high) {
    if (low < high) {
        auto pivot = partition(data, low, high);
        quick_sort(data, low, pivot - 1);
        quick_sort(data, pivot + 1, high);
    }
}

template<typename T>
void quick_sort(T& data) {
    quick_sort(data, 0, static_cast<long>(data.size()) - 1);
}

#endif
