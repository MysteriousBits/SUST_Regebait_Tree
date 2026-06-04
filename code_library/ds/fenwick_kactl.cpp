struct FT {
  std::vector<ll> s;
  FT(int n) : s(n + 1, 0) {}
  void update(int pos, ll dif) {
    for (; pos < s.size(); pos += pos & -pos) s[pos] += dif;
  }
  ll query(int pos) {
    ll res = 0;
    for (; pos > 0; pos -= pos & -pos) res += s[pos];
    return res;
  }
  ll query(int l, int r) { 
    return query(r) - query(l - 1); 
  }
  void update(int l, int r, ll dif) {
    update(l, dif);
    if (r + 1 < s.size()) update(r + 1, -dif);
  }
  int lower_bound(ll sum) {
    if (sum <= 0) return 0;
    int pos = 0;
    for (int pw = 1 << 25; pw; pw >>= 1) {
      if (pos + pw < s.size() && s[pos+pw] < sum) {
        pos += pw;
        sum -= s[pos];
      }
    }
    return pos + 1;
  }
};