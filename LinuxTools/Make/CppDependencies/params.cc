#include <fstream>
#include <sstream>
#include "params.h"

void Params::parse_file(const std::string& file_name) {
    std::ifstream ifs(file_name);
    if (!ifs) {
        std::cerr << "### error: can't open file '" << file_name << "'"
                  << std::endl;
        exit(1);
    }
    std::string line;
    while (std::getline(ifs, line)) {
        std::stringstream str(line);
        std::string var_name;
        str >> var_name;
        std::string sep;
        str >> sep;
        if (var_name == "maxSteps") {
            str >> _maxSteps;
        } else if (var_name == "deltaSteps") {
            str >> _deltaSteps;
        } else if (var_name == "leftWall") {
            str >> _leftWall;
        } else if (var_name == "rightWall") {
            str >> _rightWall;
        } else if (var_name == "nrParticles") {
            str >> _nrParticles;
        } else if (var_name == "constrained") {
            str >> _constrained;
        } else if (var_name == "verbose") {
            str >> _verbose;
        } else if (var_name == "seed") {
            str >> _seed;
        } else {
            std::cerr << "### warning: unknown variable '" << var_name
                      << "'" << std::endl;
        }
    }
    ifs.close();
}

void Params::dump() const {
    dump(std::cout, "# ");
}

void Params::dump(std::ostream &out, const std::string& prefix) const {
    out << prefix << "maxSteps = " <<  maxSteps() <<std::endl
        << prefix << "deltaSteps = " << deltaSteps() << std::endl
        << prefix << "leftWall = " << leftWall() << std:: endl
        << prefix << "rightWall = " << rightWall() << std::endl
        << prefix << "nrParticles = " << nrParticles() << std::endl
        << prefix << "constrained = " << constrained() << std::endl
        << prefix << "verbose = " << verbose() << std::endl
        << prefix << "seed = " << seed() << std::endl;
}
