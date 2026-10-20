// returns stirling1st(i, k) for 0 <= i < n
// O(n log^2 n)
vector<int> stirling(int n, int k) {
  assert(k <= n);
  vector<int> a(n); // sum c(i) / i! x^i, c(i) = (i - 1)!
  a[0] = 0;
  for (int i = 1; i < n; i++) {
    a[i] = POW(i, mod - 2);
  }
  auto ans = power(a, k, n);
  ans.resize(n);
  int f = 1;
  for (int i = 1; i <= k; i++) {
    f = 1LL * f * i % mod;
  }
  int cur = 1;
  // sum ans(i) / i! = 1 / k! * a^k
  for (int i = 0; i < n; i++) {
    ans[i] = 1LL * ans[i] * cur % mod;
    cur = 1LL * cur * (i + 1) % mod;
    ans[i] = 1LL * ans[i] * POW(f, mod - 2) % mod;
  }
  return ans;
}