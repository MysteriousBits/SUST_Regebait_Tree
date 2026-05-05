#define EPS 1e-12
#define pi 3.1415926535897931159979634\
68544185161590576171875L
bool feq(const long double& a, const long double& b) {
  long double del = fabsl(a - b);
  if (del <= EPS) return true;
  return del <= EPS * max(fabsl(a), fabsl(b));
}