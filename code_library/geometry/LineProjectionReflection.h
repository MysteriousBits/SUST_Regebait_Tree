#pragma once
#include "Point.h"
template <class P>
P lineProj(P a, P b, P p, bool refl = false) {
  P v = b - a;
  return p - v.perp() * (1 + refl) * v.cross(p - a) / v.dist2();
}
