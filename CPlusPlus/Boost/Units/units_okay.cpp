#include <boost/units/cmath.hpp>
#include <boost/units/io.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si.hpp>
#include <iostream>
#include <tuple>

using Length_unit = boost::units::si::length;
using Length = boost::units::quantity<Length_unit>;
using Time_unit = boost::units::si::time;
using Time = boost::units::quantity<Time_unit>;
using Velocity_unit = boost::units::si::velocity;
using Velocity = boost::units::quantity<Velocity_unit>;

Velocity compute_velocity(const Length dx, const Time dt) {
    return dx/dt;
}

using Point = std::tuple<Length, Length>;

Length distance(const Point& p1, const Point& p2) {
    Length x1 {std::get<0>(p1)};
    Length x2 {std::get<0>(p2)};
    Length y1 {std::get<1>(p1)};
    Length y2 {std::get<1>(p2)};
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

int main() {
    // define units to make formulas easier to read
    Length_unit m {boost::units::si::meter};
    Time_unit s {boost::units::si::seconds};

    Length dx {3.5*m};
    Time dt {2.0*s};
    Velocity velocity = compute_velocity(dx, dt);
    std::cout << velocity << std::endl;
    std::cout << velocity.value() << std::endl;

    Point p1 {std::make_tuple(3.0*m, 4.0*m)};
    Point p2 {std::make_tuple(5.0*m, 2.0*m)};
    std::cout << distance(p1, p2) << std::endl;

    return 0;
}
