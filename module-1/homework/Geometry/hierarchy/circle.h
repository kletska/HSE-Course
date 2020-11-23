#ifndef CIRCLE_H
#define CIRCLE_H
#include "point.h"
#include "line.h"
#include "ellipse.h"

class Circle : public Ellipse {
 public:
  Circle(const Point&, double);
  double radius() const;
};

#endif
