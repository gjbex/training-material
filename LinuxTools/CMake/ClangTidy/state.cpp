#include "state.h"

void State::initial_options() {
    for (int j = 0; j < size_; ++j) {
        options_.insert(j);
    }
    std::size_t current = positions_.size();
    for (std::size_t i = 0; i < positions_.size(); ++i) {
        auto j = positions_[i];
        auto search = options_.find(j);
        if (search != options_.cend()) {
            options_.erase(j);
        }
        int left = j - (current - i);
        if (left >= 0) {
            search = options_.find(left); 
            if (search != options_.cend()) {
                options_.erase(left);
            }
        }
        int right = j + (current - i);
        if (right < size_) {
            search = options_.find(right); 
            if (search != options_.cend()) {
                options_.erase(right);
            }
        }
    }
}

State::State(const int size) : size_ {size} {
    for (int i = 0; i < size_; ++i) {
        options_.insert(i);
    }
}

State::State(const State& state, const int new_position) :
    positions_(state.positions_) {
    size_ = state.size_;
    positions_.push_back(new_position);
    initial_options();
}

Pos_t State::positions() const {
    Pos_t positions(positions_);
    return positions;
}

int State::get_option() {
    int option = *(options_.cbegin());
    options_.erase(options_.begin());
    return option;
}

std::ostream& operator<<(std::ostream& out, State& state) {
    out << "size: " << state.size_ << "\n";
    out << "positions:";
    for (const auto& position: state.positions_) {
        out << " " << position;
    }
    out << "\n";
    out << "options:";
    for (const auto& option: state.options_) {
        out << " " << option;
    }
    out << "\n";
    return out;
}
