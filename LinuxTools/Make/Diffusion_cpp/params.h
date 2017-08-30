#ifndef PARAMS_HDR
#define PARAMS_HDR

#include <iostream>
#include <string>

class Params {
    private:
        long _maxSteps;
        long _deltaSteps;
        long _leftWall;
        long _rightWall;
        long _nrParticles;
        bool _constrained;
        bool _verbose;
        size_t _seed;
    public:
        Params() :
            _maxSteps {100},
            _deltaSteps {5},
            _leftWall {-30},
            _rightWall {30},
            _nrParticles {10},
            _constrained {false},
            _verbose {false},
            _seed {0} {};
        long maxSteps() const { return _maxSteps; };
        long deltaSteps() const { return _deltaSteps; };
        long leftWall() const { return _leftWall; };
        long rightWall() const { return _rightWall; };
        long nrParticles() const { return _nrParticles; };
        bool constrained() const { return _constrained; };
        bool verbose() const { return _verbose; };
        size_t seed() const { return _seed; };
        void parse_file(const std::string& file_name);
        void dump() const;
        void dump(std::ostream &out, const std::string& prefix) const;
};

#endif
