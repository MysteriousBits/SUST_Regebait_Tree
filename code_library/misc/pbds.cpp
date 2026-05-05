// ordered set
ordered_set<int> st;
// ordered multiset
ordered_set<int, less_equal<int>> multi;

// insert element
st.insert(x);
// get index
st.order_of_key(x);
// access by index
st.find_by_order(idx);