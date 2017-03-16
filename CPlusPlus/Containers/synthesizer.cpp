#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <valarray>
#include <vector>

using namespace std;

using wave_t = pair<double, double>;

vector<wave_t> read_wave_properties();

int main(int argc, char *argv[]) {
    const double pi {acos(-1.0)};
    const size_t nr_points {1000};
    const double delta_t {10.0*pi/nr_points};
    auto waves = read_wave_properties();
    valarray<double> time(nr_points);
    generate(begin(time), end(time),
             [delta_t] () {
                 static double t {0.0};
                 auto curr_time = t;
                 t += delta_t;
                 return curr_time;
            }); 
    valarray<double> signal(0.0, nr_points);
    for (auto wave: waves) {
        auto freq = wave.first;
        auto phase = wave.second;
        signal += cos(2.0*pi*freq*time + phase);
    }
    for (size_t i = 0; i < time.size(); i++)
        cout << time[i] << "\t" << signal[i] << endl;
    return 0;
}

vector<wave_t> read_wave_properties() {
    vector<wave_t> waves;
    string line;
    while (getline(cin, line)) {
        stringstream stream(line);
        double freq, phase;
        stream >> freq >> phase;
        waves.push_back(wave_t(freq, phase));
    }
    return waves;
}
