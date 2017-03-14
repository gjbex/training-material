#include <functional>
#include <iostream>
#include <queue>
#include <random>

using namespace std;

class Particle {
    private:
        double _time;
        int _id;
        double _mass;
        int _x, _y;
        function<double()> _time_distr;
        mt19937_64* _engine;
    public:
        Particle(int id, double mass, int x, int y, mt19937_64* engine) :
            _id {id}, _mass {mass}, _x {x}, _y {y}, _engine {engine}
        {
            _time_distr = bind(gamma_distribution<double>(1.0, _mass),
                               ref(*_engine));
            _time = _time_distr();
        };
        int id() const { return _id; };
        double mass() const { return _mass; };
        int x() const { return _x; };
        int y() const { return _y; };
        double time() const { return _time; };
        void update() {  };
        bool operator<(const Particle& other) const {
            return this->time() < other.time();
        };
        void update(int x, int y) {
            _time = _time_distr(); _x = x; _y = y;
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
        poisson_distribution<int> _mass_distr;
        uniform_int_distribution<int> _move_distr;
        int* find_moves(const Particle& particle);
    public:
        System(size_t nr_particles, size_t grid_size);
        ~System();
        void print_grid() const;
        void print_queue() const;
        double update();
};
