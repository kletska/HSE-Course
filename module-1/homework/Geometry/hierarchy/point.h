#ifndef POINT_H
#define POINT_H

#include <vector>

bool doubleEq(double, double);

struct Vector;

struct Point {
  double x;
  double y;
  Point(double, double);
  explicit Point(const Vector &);
};

bool operator==(const Point &, const Point &);

bool operator!=(const Point &, const Point &);

bool inSegment(const Point &, const Point &, const Point &);

Vector operator-(const Point &, const Point &);

Point operator+(const Point &, const Vector &);

struct Vector {
  double x;
  double y;
  Vector(double, double);
  explicit Vector(const Point &);
  Vector half() const;
  Vector reflex() const;
  Vector turn90() const;
  Vector rotate(double) const;
  double length() const;
};

Vector operator-(const Vector &, const Vector &);

Vector operator+(const Vector &, const Vector &);

Vector operator*(double, const Vector &);

Vector operator*(const Vector &, double);

double crossProduct(const Vector &, const Vector &);

double dotProduct(const Vector &, const Vector &);

bool isClockwise(const std::vector<Point> &);
#endif
