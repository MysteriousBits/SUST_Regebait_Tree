const int b1 = 137, b2 = 313, m1 = 1000000009, m2 = 1000000103;
ll p1[MAXN], p2[MAXN];
void calc_pow() { // call once; MAXN > max string length
  p1[0] = p2[0] = 1;
  for (int i = 1; i < MAXN; i++)
    p1[i] = p1[i-1] * b1 % m1, p2[i] = p2[i-1] * b2 % m2;
}
struct Hash { // 1-based index
  vector<ll> h1, h2;
  Hash(const string& s, char f = 'a') : h1(s.size() + 1), h2(s.size() + 1) {
    for (int i = 1; i <= (int)s.size(); i++) {
      h1[i] = (h1[i-1] * b1 + (s[i-1] - f + 1)) % m1;
      h2[i] = (h2[i-1] * b2 + (s[i-1] - f + 1)) % m2;
    }
  }
  pair<int,int> get(int l, int r) { // hash of s[l..r]
    return {int(((h1[r] - h1[l-1] * p1[r-l+1]) % m1 + m1) % m1),
            int(((h2[r] - h2[l-1] * p2[r-l+1]) % m2 + m2) % m2)};
  }
};