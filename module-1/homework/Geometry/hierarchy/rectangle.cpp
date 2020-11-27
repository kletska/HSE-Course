#include "rectangle.h"
#include <cmath>
#include <vector>

Rectangle::Rectangle(const Point& A, const Point& C, double k)
    : Polygon(std::vector<Point>()) {
  double len = dotProduct(A - C, A - C);
  double b = std::sqrt(len / (k * k + 1));
  double a = k * b;
  Point center = A + (C - A).half();
  Point B = center + (A - center).rotate(2 * atan2(a / len, b / len));
  Point D = center + (B - center).reflex();
  points.push_back(A);
  points.push_back(B);
  points.push_back(C);
  points.push_back(D);
  if (!isClockwise(points)) {
    Point tmp = points[1];
    points[1] = points[3];
    points[3] = tmp;
  }
}

Point Rectangle::center() const {
  return Point(points[0] + (points[0] - points[2]).half());
}

std::pair<Line, Line> Rectangle::diagonals() const {
  return std::make_pair(Line(points[0], points[2]), Line(points[1], points[3]));
}
