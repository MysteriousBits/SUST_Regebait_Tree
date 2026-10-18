template <class P>
bool onSegment(P s, P e, P p) {
  double d = (e - s).dist();
  if (d < 1e-9) return (p - s).dist() <= 1e-9;
  return abs((e - s).cross(p - s)) / d <= 1e-9 && (s - p).dot(e - p) <= 1e-9;
}
