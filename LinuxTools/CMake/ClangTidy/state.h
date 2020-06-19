#ifndef STATE_HDR
#define STATE_HDR

#include <iostream>
#include <set>
#include <vector>

using Pos_t = std::vector<int>;
using Opt_t = std::set<int>;

class State {
    private:
        int size_;
        Pos_t positions_;
        Opt_t options_;
        void initial_options();
    public:
        State(const int size);
        State(const State& state, const int new_position);
        auto size() const { return size_; }
        Pos_t positions() const;
        auto is_solution() const {
            return static_cast<int>(positions_.size()) == size_;
        }
        auto has_options() const {
            return options_.size() > 0;
        }
        int get_option();
        friend std::ostream& operator<<(std::ostream& out, State& state);
};

#endif
