#include <functional>
#include <iostream>
#include <queue>
#include <random>

using namespace std;

class Particle {
    private:
        double _time;
        int _x, _y;
    public:
        Particle(double time, int x, int y) :
            _time {time}, _x {x}, _y {y} {};
        double time() const {return _time; };
        int x() const {return _x;};
        int y() const {return _y;};
        bool operator<(const Particle& other) const {
            return this->time() < other.time();
        }
        void update(double time, int x, int y) {
            _time = time; _x = x; _y = y;
        };
};

ostream& operator<<(ostream& out, const Particle& p);

bool cmp(const Particle& p1, const Particle& p2);
typedef function<bool(const Particle&, const Particle&)> cmp_t;

typedef priority_queue<Particle, vector<Particle>, cmp_t>
    Particle_queue;

class System {
    private:
        size_t _nr_patricles, _grid_size;
        Particle_queue* _queue;
        bool* _grid;
        mt19937_64* _engine;
        uniform_int_distribution<int> _pos_distr;
        gamma_distribution<double> _time_distr;
        uniform_int_distribution<int> _move_distr;
        int* find_moves(const Particle& particle);
    public:
        System(size_t nr_particles, size_t grid_size);
        ~System();
        void print_grid() const;
        void print_queue() const;
        double update();
};
