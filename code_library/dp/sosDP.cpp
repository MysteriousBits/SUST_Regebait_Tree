const int B = 20;
int a[1 << B], f[1 << B], g[1 << B];
for (int i = 1; i <= n; i++) {
  cin >> a[i];
  f[a[i]]++;
  g[a[i]]++;
}
// sum over subsets
for (int i = 0; i < B; i++) {
  for (int mask = 0; mask < (1 << B); mask++) {
    if ((mask & (1 << i)) != 0) {
      f[mask] += f[mask ^ (1 << i)];
    }
  }
}
// sum over supersets
for (int i = 0; i < B; i++) {
  for (int mask = (1 << B) - 1; mask >= 0; mask--) {
    if ((mask & (1 << i)) == 0) g[mask] += g[mask ^ (1 << i)];
  }
}