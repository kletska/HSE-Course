#ifndef SQUARE_H
#define SQUARE_H

#include "point.h"
#include "circle.h"
#include "rectangle.h"

class Square : public Rectangle {
 public:
  Square(const Point&, const Point&);
  Circle circumscribedCircle() const;
  Circle inscribedCircle() const;
};

#endif
