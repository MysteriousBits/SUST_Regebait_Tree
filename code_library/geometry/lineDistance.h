#pragma once
#include "Point.h"
template <class P>
double lineDist(const P& a, const P& b, const P& p) {
  return (double)(b - a).cross(p - a) / (b - a).dist();
}
