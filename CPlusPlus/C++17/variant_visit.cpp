#include <functional>
#include <iostream>
#include <random>
#include <variant>

using Seed_t = std::mt19937_64::result_type;
using Engine_t = std::mt19937_64;
using Int_distr_t = std::uniform_int_distribution<int>;
using Double_distr_t = std::uniform_real_distribution<double>;
using Distrs = std::variant<Int_distr_t*, Double_distr_t*>;
using Return_t = std::variant<int, double>;

struct Visitor {
    Visitor(Engine_t& engine) : engine_ {engine} {}
    Return_t operator()(Int_distr_t* distr) { return (*distr)(engine_); }
    Return_t operator()(Double_distr_t* distr) { return (*distr)(engine_); }
    private:
        Engine_t engine_;
};

int main(int argc, char *argv[]) {
    const Seed_t seed {1234};
    std::string distr_type {"int"};
    if (argc > 1)
        distr_type = std::string(argv[1]);
    std::mt19937_64 engine(seed);
    Distrs distrs;
    if (distr_type == "int")
        distrs = new Int_distr_t(-10, 10);
    else
        distrs = new Double_distr_t(-5.0, 5.0);
    Visitor visitor(engine);
    for (int i = 0; i < 5; ++i) {
        auto result = std::visit(visitor, distrs);
        std::cout << i << ": ";
        if (std::holds_alternative<int>(result)) {
            auto value = std::get<int>(result);
            std::cout << value;
        } else {
            auto value = std::get<double>(result);
            std::cout << value;
        }
        std::cout << std::endl;
    }
    return 0;
}
