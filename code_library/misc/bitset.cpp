bitset<N> b; // All 0s; b[i] access; b.test(i) bounds check
bitset<N> b(string("110")); // b[0]=0, b[1]=1, b[2]=1
b.set(i, v=1); b.reset(i); b.flip(i); // Single bit modify
b.set(); b.reset(); b.flip(); // All bits modify
b.count(); b.any(); b.all(); // popcount; if 1+ bits set; if all bits set
b >>= k; b <<= k; b &= b2; b |= b2; b ^= b2; b = ~b; // O(N/64) bitwise
// GCC Specific (The good stuff):
b._Find_first(); // Index of first '1' (returns N if none)
b._Find_next(i); // Index of next '1' after i (returns N if none)

// COMPARATORS
namespace std {
template <size_t N>
bool operator<(const bitset<N>& a, const bitset<N>& b) {
  auto *pa = (const ull*)&a, *pb = (const ull*)&b;
  for (int i = (N + 63) / 64 - 1; i >= 0; --i)
    if (pa[i] != pb[i]) return pa[i] < pb[i];
  return false;
}
template <size_t N> bool operator<=(const bitset<N>& a, const bitset<N>& b) { return !(b < a); }
template <size_t N> bool operator>(const bitset<N>& a, const bitset<N>& b) { return b < a; }
template <size_t N> bool operator>=(const bitset<N>& a, const bitset<N>& b) { return !(a < b); }
}