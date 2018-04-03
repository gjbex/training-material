#include <boost/units/io.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si.hpp>
#include <iostream>

using Length_unit = boost::units::si::length;
using Time_unit = boost::units::si::time;
using Velocity_unit = boost::units::si::velocity;
using Length = boost::units::quantity<Length_unit>;
using Time = boost::units::quantity<Time_unit>;
using Velocity = boost::units::quantity<Velocity_unit>;

Velocity compute_velocity(const Length dx, const Time dt) {
    return dx/dt;
}

int main() {
    // define units to make formulas easier to read
    Length_unit m {boost::units::si::meter};
    Time_unit s {boost::units::si::seconds};

    Length distance {3.5*m};
    Time time {2.0*s};
    Velocity velocity = compute_velocity(distance, time);
    std::cout << velocity << std::endl;
    std::cout << velocity.value() << std::endl;
    return 0;
}
