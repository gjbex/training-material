#include <iomanip>
#include <iostream>

#include "circle.h"

inline double sqr(double x) {
    return x*x;
}

bool Circle::has_overlap(const Circle& other) const {
    double dist2 = sqr(x() - other.x()) + sqr(y() - other.y());
    return dist2 < sqr(radius() + other.radius());
}

std::ostream& operator<<(std::ostream& out, const Circle& circle) {
    out << circle.x() << " " << circle.y() << " "
        << circle.radius();
    return out;
}

std::istream& operator>>(std::istream& in, Circle& circle) {
    double x, y, radius;
    in >> x >> y >> radius;
    circle._x = x;
    circle._y = y;
    circle._radius = radius;
    return in;
}

std::vector<Circle> Circle::read_circles() {
    std::vector<Circle> circles;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream in(line);
        Circle circle;
        in >> circle;
        circles.push_back(circle);
    }
    return circles;
}
