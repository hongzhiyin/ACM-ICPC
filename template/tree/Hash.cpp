int base = 2333;
ull Hash(int u, int f) {  // 返回以 u 为根的树的哈希值
    vector <ull> vec; ull res = 1;
    for (auto v : e[u]) if (v != f) vec.pb(Hash(v, u));
    sort(all(vec));
    for (auto x : vec) res = res * base + x;
    return res;
}
