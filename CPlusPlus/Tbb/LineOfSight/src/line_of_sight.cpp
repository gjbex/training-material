#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

using Seed_t = std::mt19937_64::result_type;
using Distr_t = std::normal_distribution<float>;

using Vec_t = std::vector<float>;
using Vis_t = std::vector<bool>;

Vec_t create_terrain(const size_t n, const Seed_t seed = 1234,
                     float mu = 1.0f, float sigma = 0.5f,
                     float flat_fraction = 0.1) {
    std::mt19937_64 engine;

    auto n_flat {static_cast<size_t>(std::ceil(n*flat_fraction))};
    engine.seed(seed);
    auto delta_distr = Distr_t(mu, sigma);
    Vec_t altitude;
    for (size_t i = 0; i < n_flat; ++i)
        altitude.push_back(0.0f);
    for (size_t i = n_flat; i < n; ++i)
        altitude.push_back(altitude[i - 1] + delta_distr(engine));
    return altitude;
}

Vec_t compute_angles(const Vec_t& altitude, const float dx) {
    Vec_t angles;
    for (size_t i = 0; i < altitude.size(); ++i)
        angles.push_back(atan2f(altitude[i] - altitude[0], i*dx));
    return angles;
}

Vis_t compute_visibility(const Vec_t& angles) {
    Vis_t is_visible;
    float max_angle = std::numeric_limits<float>::min();
    for (const auto& angle: angles)
        if (angle > max_angle) {
            max_angle = angle;
            is_visible.push_back(true);
        } else {
            is_visible.push_back(false);
        }
    return is_visible;
}

int main(int argc, char* argv[]) {
    size_t n {10};
    if (argc > 1)
        n = static_cast<Seed_t>(std::stoul(argv[1]));
    Seed_t seed {1234};
    if (argc > 2)
        seed = std::stoul(argv[2]);
    float distance {50.0f};
    if (argc > 3)
        distance = std::stof(argv[3]);
    float mu {1.0f};
    if (argc > 4)
        mu = std::stof(argv[4]);
    float sigma {0.5f};
    if (argc > 5)
        sigma = std::stof(argv[5]);
    auto altitude = create_terrain(n, seed, mu, sigma);
    float dx {distance/(n - 1)};
    auto angles = compute_angles(altitude, dx);
    auto is_visible = compute_visibility(angles);
    std::cout << "# " << "distance" << " " << "altitude" << " " << "angle"
              << "visibility" << std::endl;
    for (size_t i = 0; i < altitude.size(); ++i) {
        std::cout << i*dx << " " << altitude[i]  << " " << angles[i] << " "
                  << is_visible[i] << std::endl;
    }
    return 0;
}
