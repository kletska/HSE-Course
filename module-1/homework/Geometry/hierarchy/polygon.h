#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include "point.h"
#include "line.h"
#include "shape.h"

class Polygon : public Shape {
 protected:
  std::vector<Point> points;

 public:
  Polygon(const std::vector<Point>& points);
  size_t verticesCount() const;
  std::vector<Point> getVertices() const;
  bool isConvex() const;

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
  void print();
};

#endif
