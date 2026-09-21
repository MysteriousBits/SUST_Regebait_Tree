template <class P>
bool circleLineIntersection(P c, double r, P a, P b) {
  auto d1 = (c-a).dist(), d2 = (c-b).dist();
  if(max(d1, d2) < r-1e-9) return false;
  ld dd;
  if ((c - a).dot(b - a) > 0 && (c - b).dot(a - b) > 0) {
    dd = abs((b - a).cross(c - a)) / (b - a).dist();
  } else {
    dd = min(d1, d2);
  }
  return dd <= r+1e-9;
}