void FMT(vector<int> &a, bool inv) {
  int n = (int)a.size() - 1;
  vector<int> primes;
  vector<bool> is_p(n + 1, true);
  for (int i = 2; i <= n; i++) {
    if (is_p[i]) {
      primes.push_back(i);
      for (int j = 2 * i; j <= n; j += i) is_p[j] = false;
    }
  }
  for (int p : primes) {
    if (!inv) for (int i = n / p; i >= 1; i--) a[i] += a[i * p];  // GCD
    else for (int i = 1; i <= n / p; i++) a[i] -= a[i * p];
    // if (!inv) for (int i = 1; i <= n / p; i++) a[i * p] += a[i]; /// LCM
    // else      for (int i = n / p; i >= 1; i--) a[i * p] -= a[i]; /// LCM
  }
}
vector<int> conv(vector<int> a, vector<int> b) {
  FMT(a, 0);
  FMT(b, 0);
  for (int i = 1; i < (int)a.size(); i++) a[i] *= b[i];
  FMT(a, 1);
  return a;
}