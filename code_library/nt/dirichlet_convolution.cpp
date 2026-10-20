/** 
Prefix sum of multiplicative functions :
  p_f : the prefix sum of f(x) (1 <= x <= T).
  p_g : the prefix sum of g(x) (0 <= x <= N).
  p_c : the prefix sum of f * g(x) (0 <= x <= N).
  T : the threshold, generally should be n ^ (2 / 3). for n = 1e9, T = 1e6
Magic Functions for different f(x)
For f(x) = phi(x): Id(x) = phi * I(x) i.e. p_c = prefix sum of Id(x), p_g = prefix sum of I(x). Here Id(n) = n, I(n) = 1
For f(x) = mu(x): e(x) = mu * I(x). Here e(x) = x == 1 ? 1 : 0
Complexity: O(n^(2/3))
**/
namespace Dirichlet {
  //solution for f(x) = phi(x)
  const int T = 1e7 + 9;
  long long phi[T];
  gp_hash_table<long long, mint> mp;
  mint dp[T], inv;
  int sz, spf[T], prime[T];
  void init() {
    memset(spf, 0, sizeof spf);
    phi[1] = 1; sz = 0;
    for (int i = 2; i < T; i++) {
      if (spf[i] == 0) phi[i] = i - 1, spf[i] = i, prime[sz++] = i;
      for (int j = 0; j < sz && i * prime[j] < T && prime[j] <= spf[i]; j++) {
        spf[i * prime[j]] = prime[j];
        if (i % prime[j] == 0) phi[i * prime[j]] = phi[i] * prime[j];
        else phi[i * prime[j]] = phi[i] * (prime[j] - 1);
      }
    }
    dp[0] = 0;
    for(int i = 1; i < T; i++) dp[i] = dp[i - 1] + phi[i] % mod;
    inv = 1; // g(1)
  }
  mint p_c(long long n) {
    if (n % 2 == 0) return n / 2 % mod * ((n + 1) % mod) % mod;
    return (n + 1) / 2 % mod * (n % mod) % mod;
  }
  mint p_g(long long n) {
    return n % mod;
  }
  mint solve (long long x) {
    if (x < T) return dp[x];
    if (mp.find(x) != mp.end()) return mp[x];
    mint ans = 0;
    for (long long i = 2, last; i <= x; i = last + 1) {
      last = x / (x / i);
      ans += solve (x / i) * (p_g(last) - p_g(i - 1));
    }
    ans = p_c(x) - ans;
    ans /= inv;
    return mp[x] = ans;
  }
}
