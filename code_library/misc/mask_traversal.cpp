int mask = 0;
for (int curOp = 1; curOp < (1LL << n); ++curOp) {
  int curOp = __builtin_ctz(x);
  mask ^= (1LL << curOp);
}