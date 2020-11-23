#include "square.h"
#include <cmath>

Square::Square(const Point& a, const Point& b) : Rectangle(a, b, 1.0) {}

Circle Square::circumscribedCircle() const {
  return Circle(center(), (points[0] - points[2]).length());
}

Circle Square::inscribedCircle() const {
  return Circle(center(), (points[0] - points[2]).length() / std::sqrt(2));
}
