struct compress {
  vector<int> a;
  compress(vector<int>& v) : a(v) {
    sort(all(a));
    a.erase(unique(all(a)), a.end());
  }
  int size() { return a.size(); }
  int operator[](int val) { return lower_bound(all(a), val) - a.begin(); }
};