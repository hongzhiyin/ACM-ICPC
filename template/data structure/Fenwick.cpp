/*
< 准备 >
    0. 树状数组可看作是 “ 支持单点修改的前缀和 ” 。
    1. N 为数组大小。
< 使用 >
    1. 调用 init(n) 对数组初始化， n 为数组大小。
    2. 调用 upd(x, d) ，即在下标为 x 的位置加上 d 。
    3. 调用 sum(x) 查询 1 到 x 的前缀和。
    4. 调用 qry(l, r) 查询 l 到 r 的区间和。
< 注意 >
    1. 数组下标从 1 开始。
    2. 当下标过大时，可选择离散化，或使用 map <int, int> t;
*/

typedef int T;
struct Fenwick {
    int n; T t[N];
    void init(int _n) { n = _n; memset(t, 0, sizeof(t[0]) * (n+1)); }
    void upd(int x, T d) { for (; x <= n; x += x&-x) t[x] += d; }
    T sum(int x) { T r = 0; for (; x; x -= x&-x) r += t[x]; return r; }
    T qry(int l, int r) { return sum(r) - sum(l-1); }
} fen;
