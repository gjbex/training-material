#include <array>
#include <functional>
#include <queue>

using namespace std;

typedef array<int, 2> Coordinates;
typedef pair<double, Coordinates*> Particle;

bool cmp(const Particle& p1, const Particle& p2);

typedef function<bool(const Particle&, const Particle&)> cmp_t;

typedef priority_queue<Particle, vector<Particle>, cmp_t>
    Particle_queue;

typedef array<size_t, 4> Potential_positions;

class System {
    private:
        size_t _nr_patricles, _grid_size;
        Particle_queue*_queue;
        bool*_grid;
        function<int()> _pos_distr;
        function<double()> _time_distr;
        function<int()> _move_distr;
    public:
        System(size_t nr_particles, size_t grid_size);
        ~System();
        void print_grid() const;
        void print_queue() const;
};
