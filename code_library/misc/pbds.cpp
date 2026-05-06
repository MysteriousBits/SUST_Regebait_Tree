#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// ordered set
ordered_set<int> st;
// ordered multiset
ordered_set<pair<int, int>> multi;
// get index/ number of smaller elements than x
st.order_of_key(x);
// access by index
st.find_by_order(idx);