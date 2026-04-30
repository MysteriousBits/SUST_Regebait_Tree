#pragma once
#include "Point.h"
typedef Point<double> P;
vector<P> polygonCut(const vector<P>& poly, P s, P e) {
  vector<P> res;
  rep(i, 0, sz(poly)) {
    P cur = poly[i], prev = i ? poly[i - 1] : poly.back();
    auto a = s.cross(e, cur), b = s.cross(e, prev);
    if ((a < 0) != (b < 0)) res.push_back(cur + (prev - cur) * (a / (a - b)));
    if (a < 0) res.push_back(cur);
  }
  return res;
}
