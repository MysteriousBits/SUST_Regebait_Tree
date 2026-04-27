VI primes;
bool isprime[MAXN];
void sieve() {
  isprime[1] = false;
  for (int i = 2; i < MAXN; ++i) isprime[i] = true;
  for (int i = 2; i < MAXN; ++i) {
    if (!isprime[i]) continue;
    primes.pb(i);
    if (1LL * i * i >= MAXN) continue;
    for (int j = i * i; j < MAXN; j += i) isprime[j] = false;
  }
}