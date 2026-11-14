// S: first K terms (S_0 ... S_{K-1})
// C: recurrence coefficients (S_n = C_0*S_{n-1} + C_1*S_{n-2} ...)
int linear_recurrence(vector<int> S, vector<int> C, long long n) {
  int k = C.size();
  vector<int> Q(k + 1, 1);
  for (int i = 0; i < k; i++) Q[i + 1] = (mod - C[i]) % mod;
  vector<int> P = multiply(S, Q);
  P.resize(k);
  for (; n; n >>= 1) {
    vector<int> Q_minus = Q;
    for (int i = 1; i < Q.size(); i += 2) Q_minus[i] = (mod - Q[i]) % mod;
    vector<int> S_P = multiply(P, Q_minus), T_Q = multiply(Q, Q_minus);
    for (int i = (n & 1); i < S_P.size(); i += 2) P[i >> 1] = S_P[i];
    for (int i = 0; i < T_Q.size(); i += 2) Q[i >> 1] = T_Q[i];
    P.resize(k); Q.resize(k + 1);
  }
  return P[0];
}