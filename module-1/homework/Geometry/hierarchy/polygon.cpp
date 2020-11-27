#include "polygon.h"

#include <cmath>
#include <iostream>

Polygon::Polygon(const std::vector<Point>& points) : points(points) {
  if (!isClockwise(this->points)) {
    int n = this->points.size();
    for (int i = 0; i < this->points.size() / 2; ++i) {
      Point tmp = this->points[i];
      this->points[i] = this->points[n - i - 1];
      this->points[n - i - 1] = tmp;
    }
  }
}

size_t Polygon::verticesCount() const { return points.size(); }

bool Polygon::isConvex() const {
  size_t n = points.size();
  bool leftTurn = false;
  bool rightTurn = false;
  for (size_t i = 0; i < n; ++i) {
    Vector firstRay = points[i] - points[(i + 1) % n];
    Vector secondRay = points[(i + 2) % n] - points[(i + 1) % n];
    double cp = crossProduct(firstRay, secondRay);
    if (cp != 0) {
      if (cp > 0) {
        leftTurn = true;
      } else {
        rightTurn = true;
      }
    }
  }
  return leftTurn ^ rightTurn;
}

double Polygon::perimeter() const {
  size_t n = points.size();
  double result = 0;
  for (size_t i = 0; i < n; ++i) {
    result += (points[(i + 1) % n] - points[i]).length();
  }
  return result;
}

double Polygon::area() const {
  size_t n = points.size();
  double result = 0;
  for (size_t i = 0; i < n; ++i) {
    result += crossProduct(Vector(points[i]), Vector(points[(i + 1) % n]));
  }
  return result / 2;
}

bool Polygon::operator==(const Shape& another) const {
  const Shape* pointer = &another;
  const Polygon* anotherP = dynamic_cast<const Polygon*>(pointer);
  if (anotherP) {
    size_t n = points.size();
    if (n != anotherP->points.size()) {
      return false;
    }
    for (size_t i = 0; i < n; ++i) {
      bool isAnswerYes = true;
      for (size_t j = 0; j < n; ++j) {
        if (points[j] != anotherP->points[(i + j) % n]) {
          isAnswerYes = false;
          break;
        }
      }
      if (isAnswerYes) {
        return true;
      }
    }
  }
  return false;
}

bool Polygon::isCongruentTo(const Shape& another) const {
  const Shape* pointer = &another;
  const Polygon* anotherP = dynamic_cast<const Polygon*>(pointer);
  if (anotherP) {
    size_t n = points.size();
    if (n == anotherP->points.size()) {
      for (size_t i = 0; i < n; ++i) {
        bool isAnswerYes = true;
        for (size_t j = 0; j < n; ++j) {
          Vector d = points[(j + 1) % n] - points[j];
          Vector anotherD =
              anotherP->points[(i + j + 1) % n] - anotherP->points[(i + j) % n];
          if (Point(d) != Point(anotherD)) {
            isAnswerYes = false;
          }
        }
        if (isAnswerYes) {
          return true;
        }
      }
    }
  }
  return false;
}

bool Polygon::isSimilarTo(const Shape& another) const {
  const Shape* pointer = &another;
  const Polygon* anotherP = dynamic_cast<const Polygon*>(pointer);
  if (anotherP) {
    size_t n = points.size();
    if (n == anotherP->points.size()) {
      for (size_t i = 0; i < n; ++i) {
        bool isAnswerYes = true;
        double k = -1.0;
        for (size_t j = 0; j < n; ++j) {
          Vector d1 = points[j] - points[(j + 1) % n];
          Vector d2 = points[(j + 2) % n] - points[(j + 1) % n];
          Vector anotherD1 =
              anotherP->points[(i + j) % n] - anotherP->points[(i + j + 1) % n];
          Vector anotherD2 = anotherP->points[(i + j + 2) % n] -
                             anotherP->points[(i + j + 1) % n];
          double cp = crossProduct(d1, d2);
          double anotherCp = crossProduct(anotherD1, anotherD2);
          double dp = dotProduct(d1, d2);
          double anotherDp = dotProduct(anotherD1, anotherD2);
          if (k < 0) {
            k = anotherD1.length() / d1.length();
          }
          if (anotherCp == k * k * cp && anotherDp == k * k * dp) {
            //                        std::cout << k << ' ' << i << std::endl;
            isAnswerYes = false;
            break;
          }
        }
        if (isAnswerYes) {
          return true;
        }
      }
    }
  }
  return false;
}

bool Polygon::containsPoint(Point point) const {
  double ang = 0;
  size_t n = points.size();
  for (size_t i = 0; i < n; ++i) {
    Vector firstRay = points[i] - point;
    Vector secondRay = points[(i + 1) % n] - point;
    double cp = crossProduct(firstRay, secondRay);
    double dp = dotProduct(firstRay, secondRay);
    ang += std::atan2(cp, dp);
  }
  for (size_t i = 0; i < n; ++i) {
    if (inSegment(points[i], points[(i + 1) % n], point)) {
      return true;
    }
  }
  const double pi = 3.1415926;
  return doubleEq(ang, 2 * pi);
}

void Polygon::rotate(Point center, double angle) {
  const double pi = 3.1415926;
  angle = angle * pi / 180;
  for (size_t i = 0; i < points.size(); ++i) {
    points[i] = center + (points[i] - center).rotate(angle);
  }
}

void Polygon::reflex(Point center) {
  for (size_t i = 0; i < points.size(); ++i) {
    Vector centerToPoint = points[i] - center;
    points[i] = center + centerToPoint.reflex();
  }
}

void Polygon::reflex(Line axis) {
  int n = points.size();
  for (size_t i = 0; i < n; ++i) {
    points[i] = axis.reflex(points[i]);
  }
  for (int i = 0; i < points.size() / 2; ++i) {
    Point tmp = points[i];
    points[i] = points[n - i - 1];
    points[n - i - 1] = tmp;
  }
}

void Polygon::scale(Point center, double coefficient) {
  for (size_t i = 0; i < points.size(); ++i) {
    points[i] = center + coefficient * (points[i] - center);
  }
}

void Polygon::print() {
  for (auto i : points) {
    std::cout << '(' << i.x << ", " << i.y << ") ";
  }
  std::cout << std::endl;
}
