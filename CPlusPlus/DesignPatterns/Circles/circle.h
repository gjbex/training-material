#ifndef CIRCLE_HDR
#define CIRCLE_HDR

#include <vector>

class Circle {
    private:
        double _x;
        double _y;
        double _radius;
    public:
        Circle(double x, double y, double radius) :
            _x {x}, _y {y}, _radius {radius} {};
        Circle() : Circle(0.5, 0.5, 0.1) {};
        Circle(const Circle& other) :
            Circle(other.x(), other.y(), other.radius()) {};
        double x() const { return _x; };
        void x(double x) { _x = x; };
        double y() const { return _y; };
        void y(double y) { _y = y; };
        double radius() const { return _radius; };
        void radius(double radius) { _radius = radius; };
        bool has_overlap(const Circle& other) const;
        static std::vector<Circle> read_circles();
};

std::ostream& operator<<(std::ostream& out, const Circle& circle);
std::istream& operator>>(std::istream& in, Circle& circle);

#endif
