template <class T>
T polygonArea2(vector<Point<T>>& v) {
  T a = v.back().cross(v[0]);
  for(int i = 0; i < (int) v.size() - 1; ++i)
    a += v[i].cross(v[i + 1]);
  return a;
}
