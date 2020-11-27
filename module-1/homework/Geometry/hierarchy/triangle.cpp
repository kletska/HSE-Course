#include "triangle.h"

#include <cmath>

Triangle::Triangle(Point a, Point b, Point c) : Polygon({a, b, c}) {}

Circle Triangle::circumscribedCircle() const {
  Vector A = Vector(points[0]);
  Vector B = Vector(points[1]);
  Vector C = Vector(points[2]);
  double a = (B - C).length();
  double b = (A - C).length();
  double c = (A - B).length();
  Vector I = (a * A + b * B + c * C) * (1 / (a + b + c));
  double r = 2 * area() / (a + b + c);
  return Circle(Point(I), r);
}

Circle Triangle::inscribedCircle() const {
  Vector A = Vector(points[0]);
  Vector B = Vector(points[1]);
  Vector C = Vector(points[2]);
  double a2 = dotProduct(B - C, B - C);
  double b2 = dotProduct(A - C, A - C);
  double c2 = dotProduct(A - B, A - B);
  double k1 = a2 * (b2 + c2 - a2);
  double k2 = b2 * (c2 + a2 - b2);
  double k3 = c2 * (a2 + b2 - c2);
  Vector O = (k1 * A + k2 * B + k3 * C) * (1 / (k1 + k2 + k3));
  double r = std::sqrt(a2) * std::sqrt(b2) * std::sqrt(c2) / (4 * area());
  return Circle(Point(O), r);
}
