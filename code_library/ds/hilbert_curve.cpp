int K = 17; // adjust
inline uint64_t hilbertOrder(int x, int y) {
  uint64_t r = 0;
  for (int s = 1 << (K - 1); s; s >>= 1) {
    bool a = x & s, b = y & s;
    r = r << 2 | (a ? b ? 2 : 1 : b * 3);
    if (!a) {
      if (b) x = (1 << K) - 1 - x, y = (1 << K) - 1 - y;
      swap(x, y);
    }
  }
  return r;
}