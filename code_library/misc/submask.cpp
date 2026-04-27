int n = 17;
for (int mask = 0; mask < (1 << n); ++mask) {
  for (int sub = mask; sub; sub = (sub - 1) & mask) {
    // Process submask...
  }
}