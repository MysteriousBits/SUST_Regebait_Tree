// mod: NTT prime < 2^31. Needs global modpow
template<long long mod = 998244353, long long root = 3>
struct NTT {
  typedef unsigned u32; typedef unsigned long long u64;
  static const u32 M = mod;
  vector<u32> rt{0, 1}, irt{0, 1};
  void init(int n) {
    for (int len = rt.size(); len < n; len <<= 1) {
      u64 w = modpow(root, (mod - 1) / (2 * len), mod);
      u64 iw = modpow(w, mod - 2, mod);
      rt.resize(2 * len); irt.resize(2 * len); rt[len] = irt[len] = 1;
      for (int j = 1; j < len; j++)
        rt[len + j] = rt[len + j - 1] * w % M, irt[len + j] = irt[len + j - 1] * iw % M;
    }
  }
  void fwd(u32* a, int n) {
    for (int len = n >> 1; len; len >>= 1)
      for (int i = 0; i < n; i += 2 * len) {
        u32 *x = a + i, *y = x + len;
        for (int j = 0; j < len; j++) {
          u32 u = x[j], v = y[j], s = u + v;
          x[j] = s >= M ? s - M : s;
          y[j] = (u64)(u + M - v) * rt[len + j] % M;
        }
      }
  }
  void inv(u32* a, int n) {
    for (int len = 1; len < n; len <<= 1)
      for (int i = 0; i < n; i += 2 * len) {
        u32 *x = a + i, *y = x + len;
        for (int j = 0; j < len; j++) {
          u32 u = x[j], v = (u64)y[j] * irt[len + j] % M, s = u + v, d = u + M - v;
          x[j] = s >= M ? s - M : s;
          y[j] = d >= M ? d - M : d;
        }
      }
  }
  vector<ll> conv(const vector<ll>& a, const vector<ll>& b) {
    if (a.empty() || b.empty()) return {};
    int s = a.size() + b.size() - 1, n = 1;
    while (n < s) n <<= 1;
    init(n);
    vector<u32> fa(n), fb(n);
    for (size_t i = 0; i < a.size(); i++) fa[i] = (a[i] % mod + mod) % mod;
    for (size_t i = 0; i < b.size(); i++) fb[i] = (b[i] % mod + mod) % mod;
    fwd(fa.data(), n); fwd(fb.data(), n);
    u64 d = modpow(n, mod - 2, mod);
    for (int i = 0; i < n; i++) fa[i] = (u64)fa[i] * fb[i] % M * d % M;
    inv(fa.data(), n);
    return vector<ll>(fa.begin(), fa.begin() + s);
  }
  vector<ll> mul(const vector<ll>& a, const vector<ll>& b, int n) {
    vector<ll> c = conv(a, b);
    if ((int)c.size() > n + 1) c.resize(n + 1);
    return c;
  }
  vector<ll> power(vector<ll> f, ll m, int n) {
    vector<ll> r = {1};
    if ((int)f.size() > n + 1) f.resize(n + 1);
    while (m) {
      if (m & 1) r = mul(r, f, n);
      m >>= 1;
      if (m) f = mul(f, f, n);
    }
    return r;
  }
};