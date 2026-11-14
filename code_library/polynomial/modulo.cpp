vector<int> poly_mod(vector<int> a, vector<int> b) {
  if (a.size() < b.size()) return a;
  int m = a.size() - b.size() + 1;
  vector<int> ra = a, rb = b;
  reverse(ra.begin(), ra.end()); 
  reverse(rb.begin(), rb.end());
  vector<int> q = multiply(ra, poly_inv(rb, m));
  q.resize(m); 
  reverse(q.begin(), q.end());
  vector<int> prod = multiply(b, q), rem(b.size() - 1);
  for (int i = 0; i < (int)rem.size(); i++) 
    rem[i] = (a[i] - prod[i] + mod) % mod;
  return rem;
}