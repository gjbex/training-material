#include <chrono>
#include <iostream>
#include <vector>

using my_time_t = std::chrono::nanoseconds;

struct DataItem {
    double x, y, z;
    DataItem(double xv, double yv, double zv) : x {xv}, y {yv}, z {zv} {}
};

struct Data {
    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> z;
};

int main(int argc, char* argv[]) {
    const int default_n {100};
    int n {default_n};
    if (argc > 1)
        n = std::stoi(argv[1]);
    std::cout << "data size: " << n << std::endl;

    // array of structures
    std::cout << "array of structures:" << "\n";
    auto start_time = std::chrono::steady_clock::now();
    std::vector<DataItem> aos;
    aos.reserve(n);
    for (int i = 0; i < n; ++i)
        aos.emplace_back(0.1*i, 0.2*i, 0.5*i);
    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<my_time_t>(end_time - start_time);
    std::cout << "  initialization: " << duration.count()*1.0e-9 << std::endl;
    start_time = std::chrono::steady_clock::now();
    double x_sum {0.0};
    double y_sum {0.0};
    double z_sum {0.0};
    for (int i = 0; i < n; ++i) {
        x_sum += 10.0*aos[i].x;
        y_sum += 5.0*aos[i].y;
        z_sum += 2.0*aos[i].z;
    }
    end_time = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<my_time_t>(end_time - start_time);
    std::cout << "  aggregation: " << duration.count()*1.0e-9 << std::endl;
    std::cout << "  result: " << x_sum << " " << y_sum << " " << z_sum << "\n";
    start_time = std::chrono::steady_clock::now();
    x_sum = 0.0;
    for (int i = 0; i < n; ++i)
        x_sum += 10.0*aos[i].x;
    y_sum = 0.0;
    for (int i = 0; i < n; ++i)
        y_sum += 5.0*aos[i].y;
    z_sum = 0.0;
    for (int i = 0; i < n; ++i)
        z_sum += 2.0*aos[i].z;
    end_time = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<my_time_t>(end_time - start_time);
    std::cout << "  aggregation: " << duration.count()*1.0e-9 << std::endl;
    std::cout << "  result: " << x_sum << " " << y_sum << " " << z_sum << "\n";

    // structure of arrays
    std::cout << "structure of arrays:" << "\n";
    start_time = std::chrono::steady_clock::now();
    Data soa;
    soa.x.reserve(n);
    soa.y.reserve(n);
    soa.z.reserve(n);
    for (int i = 0; i < n; ++i) {
        soa.x.emplace_back(0.1*i);
        soa.y.emplace_back(0.2*i);
        soa.z.emplace_back(0.5*i);
    }
    end_time = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<my_time_t>(end_time - start_time);
    std::cout << "  initialization: " << duration.count()*1.0e-9 << std::endl;
    start_time = std::chrono::steady_clock::now();
    x_sum = 0.0;
    y_sum = 0.0;
    z_sum = 0.0;
    for (int i = 0; i < n; ++i) {
        x_sum += 10.0*soa.x[i];
        y_sum += 5.0*soa.y[i];
        z_sum += 2.0*soa.z[i];
    }
    end_time = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<my_time_t>(end_time - start_time);
    std::cout << "  aggregation: " << duration.count()*1.0e-9 << std::endl;
    std::cout << "  result: " << x_sum << " " << y_sum << " " << z_sum << "\n";
    start_time = std::chrono::steady_clock::now();
    x_sum = 0.0;
    for (int i = 0; i < n; ++i)
        x_sum += 10.0*soa.x[i];
    y_sum = 0.0;
    for (int i = 0; i < n; ++i)
        y_sum += 5.0*soa.y[i];
    z_sum = 0.0;
    for (int i = 0; i < n; ++i)
        z_sum += 2.0*soa.z[i];
    end_time = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<my_time_t>(end_time - start_time);
    std::cout << "  aggregation: " << duration.count()*1.0e-9 << std::endl;
    std::cout << "  result: " << x_sum << " " << y_sum << " " << z_sum << "\n";

    return 0;
}
