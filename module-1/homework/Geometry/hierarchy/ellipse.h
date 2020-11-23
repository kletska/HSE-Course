#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "point.h"
#include "line.h"
#include "shape.h"

class Ellipse : public Shape {
 protected:
  double r;
  Point first;
  Point second;

 private:
  double a() const;
  double b() const;

 public:
  Ellipse(const Point& first, const Point& second, double r)
      : first(first), second(second), r(r) {}
  std::pair<Point, Point> focuses() const;
  std::pair<Line, Line> directrices() const;
  double eccentricity() const;
  Point center() const;

  double perimeter() const override;
  double area() const override;
  bool operator==(const Shape& another) const override;
  bool isCongruentTo(const Shape& another) const override;
  bool isSimilarTo(const Shape& another) const override;
  bool containsPoint(Point point) const override;
  void rotate(Point center, double angle) override;
  void reflex(Point center) override;
  void reflex(Line axis) override;
  void scale(Point center, double coefficient) override;
};

#endif
