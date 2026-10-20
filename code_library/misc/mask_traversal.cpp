long long mask = 0;
for (int i = 1; i < (1LL << n); ++i) {
  int bit = __builtin_ctz(i);
  mask ^= (1LL << bit); 
}