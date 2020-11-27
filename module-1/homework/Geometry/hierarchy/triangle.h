#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"
#include "polygon.h"
#include "circle.h"

class Triangle : public Polygon {
 public:
  Triangle(Point a, Point b, Point c);
  Circle circumscribedCircle() const;
  Circle inscribedCircle() const;
};

#endif
