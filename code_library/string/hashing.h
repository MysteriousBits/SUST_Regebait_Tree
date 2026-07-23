const int SZ = int(1e6) + 9;
const int B1 = 151, B2 = 239;
const int mod1 = 127657753, mod2 = 987654319;
vector<int> P1(SZ, 1), P2(SZ, 1);
void pow_cal() {
  for (int i = 1; i < SZ; i++) {
    P1[i] = (P1[i - 1] * B1) % mod1;
    P2[i] = (P2[i - 1] * B2) % mod2;
  }
}
class Hash {
 public:
  int n;
  vector<int> H1, H2;
  Hash(const string& s) {
    n = s.size();
    H1.assign(n + 1, 0);
    H2.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      H1[i] = (H1[i - 1] + ((s[i - 1] - 'a' + 1) * P1[i]) % mod1) % mod1;
      H2[i] = (H2[i - 1] + ((s[i - 1] - 'a' + 1) * P2[i]) % mod2) % mod2;
    }
  }
  pair<int, int> geth(int l, int r) {
    int h1 = (((H1[r] - H1[l - 1] + mod1) % mod1) * P1[SZ - l]) % mod1;
    int h2 = (((H2[r] - H2[l - 1] + mod2) % mod2) * P2[SZ - l]) % mod2;
    return make_pair(h1, h2);
  }
  pair<int, int> geth() { return geth(1, n); }
};