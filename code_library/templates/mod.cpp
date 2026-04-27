template <unsigned P>
struct modint {
  unsigned v;
  modint() = default;
  template <class T>
  modint(T x) {
    x %= (signed)P, v = x < 0 ? x + P : x;
  }
  modint operator+() const { return *this; }
  modint operator-() const { return modint(0) - *this; }
  static modint power(modint a, int b) {
    if (b < 0) return power(a, -b).inv();
    modint res = 1;
    while (b) {
      if (b & 1) res *= a;
      a *= a;
      b >>= 1;
    }
    return res;
  }
  modint inv() const { return assert(v), power(*this, P - 2); }
  modint& operator+=(const modint& q) {
    (v += q.v) < P || (v -= P);
    return *this;
  }
  modint& operator-=(const modint& q) {
    (v -= q.v) < P || (v += P);
    return *this;
  }
  modint& operator*=(const modint& q) {
    v = 1ull * v * q.v % P;
    return *this;
  }
  modint& operator/=(const modint& q) {
    v = 1ull * v * q.inv().v % P;
    return *this;
  }
  friend modint operator+(modint p, const modint& q) { return p += q; }
  friend modint operator-(modint p, const modint& q) { return p -= q; }
  friend modint operator*(modint p, const modint& q) { return p *= q; }
  friend modint operator/(modint p, const modint& q) { return p /= q; }
  friend istream& operator>>(istream& is, modint& a) {
    int x;
    is >> x;
    x %= (signed)P;
    a.v = x < 0 ? x + P : x;
    return is;
  }
  friend ostream& operator<<(ostream& os, const modint& a) {
    os << a.v;
    return os;
  }
};
typedef modint<998244353> mint;
typedef modint<1000000007> mint2;