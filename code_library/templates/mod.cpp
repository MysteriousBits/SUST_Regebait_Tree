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
};
typedef modint<998244353> mint;
typedef modint<1000000007> mint2;