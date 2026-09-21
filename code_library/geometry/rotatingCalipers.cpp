// Outer loop advances edge (i -> i+1), inner loop advances antipodal pointer j
for (int i = 0, j = 1; i < n; ++i) {
  while ((p[(i + 1) % n] - p[i]).cross(p[(j + 1) % n] - p[j]) > 0) {
    j = (j + 1) % n;
  }
  // Process antipodal pair: p[i] (or edge i -> i+1) and p[j]
}