const ll a1 = 151, b1 = 127657753;
const ll a2 = 239, b2 = 987654319;
ll p1[maxN], p2[maxN];
void pre() {
  p1[0] = p2[0] = 1;
  for (int i = 1; i < maxN; i++) {
    p1[i] = (p1[i - 1] * a1) % b1;
    p2[i] = (p2[i - 1] * a2) % b2;
  }
}
struct Hash {
  vector<ll> h1, h2;
  int n;
  string s;
  Hash(string s) : s(s), n(s.size()) {
    h1.resize(n + 1, 0); h2.resize(n + 1, 0);
    for (int i = 0; i < n; i++) {
        h1[i + 1] = (h1[i] * a1 + s[i]) % b1;
        h2[i + 1] = (h2[i] * a2 + s[i]) % b2;
    }
  }
  array<int,2> get(int l, int r) { // [l, r] 0-indexed
    ll r1 = (h1[r + 1] - h1[l] * p1[r - l + 1]) % b1;
    ll r2 = (h2[r + 1] - h2[l] * p2[r - l + 1]) % b2;
    return {r1 < 0 ? r1 + b1 : r1, r2 < 0 ? r2 + b2 : r2};
  }
  // implement lcp, lcs, etc yourself
  // if s+s+s... (1 or more times) = t -> true
  bool repeat(string& s_in) {
    int m = s_in.size();
    if (m == 0 || n % m != 0 || n == 0) return false;
    Hash temp(s_in);
    if (get(0, m - 1) != temp.get(0, m - 1)) return false; 
    if (n > m && get(0, n - m - 1) != get(m, n - 1)) return false; 
    return true;
  }
};