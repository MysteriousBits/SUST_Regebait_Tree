// (x+1)*(x+2)*(x+3)...(x+n)
// O(n log n) only for ntt friendly primes
// otherwise use divide and conquer in O(n log^2 n)
vector<int> range_mul(int n) {
  if (n == 0) return vector<int>({1});
  if (n & 1) {
    vector<int> f = range_mul(n - 1);
    f.push_back(0);
    for (int i = (int)f.size()-1; i; --i) f[i] = (f[i - 1] + (long long) n * f[i]) % mod;
    f[0] = (long long) f[0] * n % mod;
    return f;
  } 
  else {
    int n_ = n >> 1;
    vector<int> f = range_mul(n_);
    vector<int> tmp = shift(f, n_);
    f.resize(n_ + 1);
    tmp.resize(n_ + 1);
    return multiply(f, tmp);
  }
}
// returns stirling1st(n, i) for 0 <= i <= n
vector<int> stirling(int n) {
  if (n == 0) return {1};
  vector<int> ans = range_mul(n - 1);
  ans.resize(n + 1);
  for (int i = n - 1; i >= 0; i--) {
    ans[i + 1] = ans[i];
  }
  ans[0] = 0;
  return ans;
}