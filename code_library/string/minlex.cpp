int mnlex(string& s) {
  int n = s.size(), sz = 2 * n, l = 0, j = 1, k = 0;
  while(l + k < sz && j + k < sz) {
    int a = ((l + k >= n) ? s[l + k - n] : s[l + k]);
    int b = ((j + k >= n) ? s[j + k - n] : s[j + k]);
    if(a == b) k++;
    else if(a > b) { // if maxlex then (a<b)
      l = l + k + 1;  k = 0;
      if(l <= j) { l = j + 1; }
    }
    else {
      j = j + k + 1;
      k = 0;
      if(j <= l) { j = l + 1; }
    }
  }
  return min(l, j);
}