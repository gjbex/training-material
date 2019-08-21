#include <cstdint>
#include <iostream>

struct Data {
    char c;
    int32_t i;
   double d;
   float f;
};

int main() {
    Data data;
    auto base = reinterpret_cast<uintptr_t>(&data);
    std::cout << "size: " << sizeof(Data) << "\n"
              << "align: " << alignof(Data) << "\n"
              << "base: " << base << "\n"
              << "  char: " << reinterpret_cast<uintptr_t>(&(data.c)) - base << "\n"
              << "  int: " << reinterpret_cast<uintptr_t>(&(data.i)) - base << "\n"
              << "  double: " << reinterpret_cast<uintptr_t>(&(data.d)) - base << "\n"
              << "  float: " << reinterpret_cast<uintptr_t>(&(data.f)) - base
              << std::endl;
    const int n = 3;
    auto data_array = new Data[n];
    base = reinterpret_cast<uintptr_t>(data_array);
    std::cout << "base: " << base << "\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "index: " << i << "\n"
            << "    char: " << reinterpret_cast<uintptr_t>(&(data_array[i].c)) - base << "\n"
            << "    int: " << reinterpret_cast<uintptr_t>(&(data_array[i].i)) - base << "\n"
            << "    double: " << reinterpret_cast<uintptr_t>(&(data_array[i].d)) - base << "\n"
            << "    float: " << reinterpret_cast<uintptr_t>(&(data_array[i].f)) - base
            << std::endl;
    }
    delete[] data_array;
    return 0;
}
