#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "point.h"
#include "line.h"
#include "polygon.h"

class Rectangle : public Polygon {
 public:
  Rectangle(const Point&, const Point&, double);
  Point center() const;
  std::pair<Line, Line> diagonals() const;
};

#endif
