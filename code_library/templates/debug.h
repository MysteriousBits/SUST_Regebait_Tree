#include <iostream>
using namespace std;
#define see(x) cerr << #x << ": " << x << nl
template <typename... Args>
void debug(Args... args) {
  ((cerr << " " << args), ...) << "\n";
}