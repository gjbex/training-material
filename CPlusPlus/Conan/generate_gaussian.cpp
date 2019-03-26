#include <args.hxx>
#include <functional>
#include <iostream>
#include <limits>
#include <random>

using Seed_t = std::mt19937_64::result_type;
using Seed_distr_t = std::uniform_int_distribution<Seed_t>;

int main(int argc, char **argv)
{
    args::ArgumentParser parser("random number generator",
                                "Uses Mersenne Twister");
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
    args::ValueFlag<double> mu_flag(parser, "mu", "mean value", {'m', "mu"});
    args::ValueFlag<double> sigma_flag(parser, "sigma", "standard deviation",
                                       {'s', "sigma"});
    args::Group group(parser, "flags", args::Group::Validators::DontCare);
    args::Flag display_idx(group, "index", "display index", {'i', "index"});
    args::Positional<std::size_t> n_value(parser, "n", "number of values");
    try
    {
        parser.ParseCLI(argc, argv);
    }
    catch (args::Help)
    {
        std::cout << parser;
        return 0;
    }
    catch (args::ParseError e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }
    catch (args::ValidationError e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 2;
    }
    double mu {mu_flag ? args::get(mu_flag) : 0.0};
    double sigma {sigma_flag ? args::get(sigma_flag) : 1.0};
    std::size_t n {n_value ? args::get(n_value) : 1};
    std::random_device device;
    auto seed_distr = Seed_distr_t(0, std::numeric_limits<Seed_t>::max());
    Seed_t seed = seed_distr(device);
    std::mt19937_64 engine(seed);
    auto distr = std::bind(std::normal_distribution<double>(mu, sigma),
                           engine);
    for (std::size_t i = 0; i < n; ++i) {
        if (display_idx)
            std::cout << i + 1 << " ";
        std::cout << distr() << std::endl;
    }
    return 0;
}
