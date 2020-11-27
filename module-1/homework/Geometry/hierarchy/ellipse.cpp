#include <cmath>
#include "ellipse.h"

double Ellipse::a() const { return r / 2; }

double Ellipse::b() const {
  double c = (first - second).half().length();
  double a = this->a();
  return sqrt(a * a - c * c);
}

std::pair<Point, Point> Ellipse::focuses() const {
  return std::make_pair(first, second);
}

std::pair<Line, Line> Ellipse::directrices() const {
  Point center = this->center();
  Line centerLine = Line(first, second);
  return std::make_pair(centerLine, centerLine.turn90().moveTo(center));
}

double Ellipse::eccentricity() const {
  double c = (first - second).half().length();
  return c / this->a();
}

Point Ellipse::center() const { return second + (first - second).half(); }

double Ellipse::perimeter() const {
  const double pi = 3.1415926;
  double a = this->a();
  double b = this->b();
  return 4 * (pi * a * b + (a - b) * (a - b)) / (a + b);
}

double Ellipse::area() const {
  double pi = 3.1415926;
  return pi * this->a() * this->b();
}

bool Ellipse::operator==(const Shape& another) const {
  const Shape* pointer = &another;
  const Ellipse* anotherEllipse = dynamic_cast<const Ellipse*>(pointer);
  if (anotherEllipse) {
    bool ffEqual = first == anotherEllipse->first;
    bool ssEqual = second == anotherEllipse->second;
    bool fsEqual = first == anotherEllipse->second;
    bool sfEqual = second == anotherEllipse->first;
    bool radiusEqual = doubleEq(r, anotherEllipse->r);
    return (ffEqual && ssEqual || fsEqual && sfEqual) && radiusEqual;
  }
  return false;
}

bool Ellipse::isCongruentTo(const Shape& another) const {
  const Shape* pointer = &another;
  const Ellipse* anotherEllipse = dynamic_cast<const Ellipse*>(pointer);
  if (anotherEllipse) {
    return doubleEq(this->a(), anotherEllipse->a()) &&
           doubleEq(this->b(), anotherEllipse->b());
  }
  return false;
}

bool Ellipse::isSimilarTo(const Shape& another) const {
  const Shape* pointer = &another;
  const Ellipse* anotherEllipse = dynamic_cast<const Ellipse*>(pointer);
  if (anotherEllipse) {
    return doubleEq(this->a() / anotherEllipse->a(),
                    this->b() / anotherEllipse->b());
  }
  return false;
}

bool Ellipse::containsPoint(Point point) const {
  return (first - point).length() + (second - point).length() <= r;
}

void Ellipse::rotate(Point center, double angle) {
  first = center + (first - center).rotate(angle);
  second = center + (second - center).rotate(angle);
}

void Ellipse::reflex(Point center) {
  first = center + (first - center).reflex();
  second = center + (second - center).reflex();
}

void Ellipse::reflex(Line axis) {
  first = axis.reflex(first);
  second = axis.reflex(second);
}

void Ellipse::scale(Point center, double coefficient) {
  r *= coefficient;
  first = center + coefficient * (first - center);
  second = center + coefficient * (second - center);
}
