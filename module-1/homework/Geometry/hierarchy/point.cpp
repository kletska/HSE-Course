#include "point.h"

#include <cmath>

bool doubleEq(double a, double b) {
  const double eps = 1e-6;
  return abs(a - b) < eps;
}

Point::Point(double x, double y) : x(x), y(y) {}

Point::Point(const Vector& v) : x(v.x), y(v.y) {}

bool operator==(const Point& a, const Point& b) {
  return doubleEq(a.x, b.x) && doubleEq(a.y, b.y);
}

bool operator!=(const Point& a, const Point& b) { return !(a == b); }

bool inSegment(const Point& s1, const Point& s2, const Point& p) {
  bool inSameLine = doubleEq(crossProduct(p - s1, s2 - s1), 0);
  bool inRay1 = dotProduct(p - s1, s2 - s1) >= 0;
  bool inRay2 = dotProduct(p - s2, s1 - s2) >= 0;
  return inSameLine && inRay1 && inRay2;
}

Vector operator-(const Point& end, const Point& start) {
  return Vector(end.x - start.x, end.y - start.y);
}

Point operator+(const Point& start, const Vector& d) {
  return Point(start.x + d.x, start.y + d.y);
}

Vector::Vector(double x, double y) : x(x), y(y) {}

Vector::Vector(const Point& p) : x(p.x), y(p.y) {}

Vector Vector::half() const { return Vector(x / 2, y / 2); }

Vector Vector::reflex() const { return Vector(-x, -y); }

Vector Vector::turn90() const { return Vector(y, -x); }

Vector Vector::rotate(double angle) const {
  return Vector(x * cos(angle) - y * sin(angle),
                x * sin(angle) + y * cos(angle));
}

double Vector::length() const { return sqrt(x * x + y * y); }

Vector operator+(const Vector& a, const Vector& b) {
  return Vector(a.x + b.x, a.y + b.y);
}

Vector operator-(const Vector& a, const Vector& b) {
  return Vector(a.x - b.x, a.y - b.y);
}

Vector operator*(double c, const Vector& v) { return Vector(c * v.x, c * v.y); }

Vector operator*(const Vector& v, double c) { return Vector(c * v.x, c * v.y); }

double crossProduct(const Vector& a, const Vector& b) {
  return a.x * b.y - a.y * b.x;
}

double dotProduct(const Vector& a, const Vector& b) {
  return a.x * b.x + a.y * b.y;
}

bool isClockwise(const std::vector<Point>& points) {
  size_t n = points.size();
  for (size_t i = 0; i < n; ++i) {
    Vector firstRay = points[i] - points[(i + 1) % n];
    Vector secondRay = points[(i + 2) % n] - points[(i + 1) % n];
    if (crossProduct(firstRay, secondRay) < 0) {
      return false;
    }
  }
  return true;
}
