vector<int> pi(const string& s) {
  int n = s.size();
  vector<int> p(n);
  for (int i = 1; i < n; ++i) {
    int g = p[i-1];
    while (g && s[i] != s[g]) g = p[g-1];
    p[i] = g + (s[i] == s[g]);
  }
  return p;
}
vector<int> match(const string& s, const string& pat) {
  vector<int> p = pi(pat + '\0' + s), res;
  int n = p.size(), ns = s.size(), np = pat.size();
  for (int i = n - ns; i < n; ++i)
    if (p[i] == np) res.push_back(i - 2 * np);
  return res;
}