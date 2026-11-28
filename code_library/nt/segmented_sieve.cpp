// Generate all primes from l to r using segmented sieve in
// O((r - l) log (r) + sqrt(r)) // needs sieve(limit)
vector<int64_t> segmented_sieve(int64_t l, int64_t r) {
  if (l == 1) l++;
  int limit = sqrtl(r);
  while (limit * limit <= r) limit++;
  while (limit * limit > r) limit--;
  auto primes = sieve(limit);
  vector<bool> is_prime(r - l + 1, true);
  for (int64_t p : primes) {
    int64_t start = max(p * p, (l + p - 1) / p * p);
    for (int64_t j = start; j <= r; j += p) {
      is_prime[j - l] = false;
    }
  }
  vector<int64_t> vec;
  for (int64_t i = l; i <= r; ++i) {
    if (is_prime[i - l]) vec.push_back(i);
  }
  return vec;
}