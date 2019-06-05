#include <chrono>
#include <iostream>
#include <tbb/tbb.h>

class FibTask : public tbb::task {
    private:
        long n_;
        long* result_;
        static long task_threshold_;
        void fib(long n, long* result) {
            if (n < 2) {
                *result = 1;
            } else {
                long result_n_1;
                long result_n_2;
                fib(n - 1, &result_n_1);
                fib(n - 2, &result_n_2);
                *result = result_n_1 + result_n_2;
            }
        }
    public:
        FibTask(long n, long* result) : n_ {n}, result_ {result} {}
        tbb::task* execute() {
            if (n_ < task_threshold_) {
                fib(n_, result_);
            } else {
                long result_n_1;
                long result_n_2;
                tbb::task_list list;
                list.push_back(*new(allocate_child()) FibTask(n_ - 1, &result_n_1));
                list.push_back(*new(allocate_child()) FibTask(n_ - 2, &result_n_2));
                set_ref_count(3);
                spawn_and_wait_for_all(list);
                *result_ = result_n_1 + result_n_2;
            }
            return nullptr;
        }
        static long task_threshold() { return task_threshold_; }
        static void set_task_threshold(const long task_threshold) {
            task_threshold_ = task_threshold;
        }
};

long FibTask::task_threshold_ {10};

using my_time_t = std::chrono::nanoseconds;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: expecting positive integer as argument" << std::endl;
        std::exit(1);
    }
    long n {std::stol(argv[1])};
    if (n < 0) {
        std::cerr << "Error: expecting positive integer as argument" << std::endl;
        std::exit(1);
    }
    if (argc > 2)
        FibTask::set_task_threshold(std::stol(argv[2]));
    std::cout << "task threshold: " << FibTask::task_threshold() << std::endl;
    long result;
    auto start_time = std::chrono::steady_clock::now();
    auto task = new(tbb::task::allocate_root()) FibTask(n, &result);
    tbb::task::spawn_root_and_wait(*task);
    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<my_time_t>(end_time - start_time);
    std::cout << "fib(" << n << ") = " << result << std::endl;
    std::cout << "time: " << duration.count()*1.0e-9 << " s" << std::endl;
    return 0;
}
