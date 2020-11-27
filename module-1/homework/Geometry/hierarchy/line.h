#ifndef LINE_H
#define LINE_H
#include "point.h"

class Line {
  Point first;
  Point second;

 public:
  Line(const Point& first, const Point& second);
  friend bool operator==(const Line&, const Line&);
  friend bool operator!=(const Line&, const Line&);
  Line turn90() const;
  Point reflex(const Point&) const;
  Line moveTo(const Point&) const;
};
#endif
