#ifndef SUM_TASK_HDR
#define SUM_TASK_HDR

#include <tbb/tbb.h>
#include "tree.h"

template<typename T>
class SumTask : public tbb::task {
    private:
        Node<T>* node_;
        T* sum_;
    public:
        SumTask(Node<T>* node, T* sum) : node_ {node}, sum_ {sum} {}
        tbb::task* execute() override;
        T sum() const { return *sum_; }
};

template<typename T>
tbb::task* SumTask<T>::execute() {
    *sum_ += (*node_)();
    tbb::task_list list;
    T left_sum {0.0};
    double right_sum {0.0};
    int count {1};
    if (node_->left()) {
        list.push_back(*new(allocate_child()) SumTask(node_->left(), &left_sum));
        ++count;
    }
    if (node_->right()) {
        list.push_back(*new(allocate_child()) SumTask(node_->right(), &right_sum));
        ++count;
    }
    set_ref_count(count);
    spawn_and_wait_for_all(list);
    *sum_ += left_sum + right_sum;
    return nullptr;
}

#endif
