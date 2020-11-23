#include "line.h"

Line::Line(const Point& first, const Point& second)
    : first(first), second(second) {}

bool operator==(const Line& a, const Line& b) {
  bool firstInA =
      doubleEq(crossProduct(a.second - a.first, b.first - a.first), 0);
  bool secondInA =
      doubleEq(crossProduct(a.second - a.first, b.second - a.first), 0);
  return firstInA && secondInA;
}

bool operator!=(const Line& a, const Line& b) { return !(a == b); }

Line Line::turn90() const {
  Line result = *this;
  result.second = first + (second - first).turn90();
  return result;
}

Point Line::reflex(const Point& p) const {
  Vector v = p - second;
  Vector l = first - second;
  return second + ((2 * dotProduct(v, l) / dotProduct(l, l)) * l - v);
}

Line Line::moveTo(const Point& p) const {
  Line result = *this;
  Vector v = p - first;
  result.first = first + v;
  result.second = second + v;
  return result;
}
