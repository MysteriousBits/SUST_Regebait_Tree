struct pointhash {
  size_t operator()(const pair<int, int>& p) const {
    return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
  }
};
// Usage: unordered_set<pair<int, int>, pointhash> st;