/* ----- 树状数组 -----
< 准备 >
    0. 树状数组可看作是 “ 支持单点修改的前缀和 ”
    
< 使用 >
    1. 调用构造函数对树状数组初始化， _n 为数组大小
    2. 调用 add(i, d) ，即在下标为 i 的位置加上 d 
    3. 调用 sum(i) 查询 1 到 i 的前缀和
    4. 调用 qry(l, r) 查询 l 到 r 的区间和
    
< 注意 >
    1. 数组下标从 1 开始
    2. 当下标过大时，可选择离散化，或使用 map <int, int> t;
*/

template <class T>
struct Fenwick_Tree {
    int n; vector<T> t;
    Fenwick_Tree(int _n) : n(_n) { t = vector<T>(n+1, 0); }
    void add(int i, T d) { for (; i <= n; i += i&-i) t[i] += d; }
    T sum(int i) { T r = 0; for (; i; i -= i&-i) r += t[i]; return r; }
    T qry(int l, int r) { return sum(r) - sum(l-1); }
};

/* ----- 支持区间修改 -----
< 准备 >
    1. 树状数组中保存的是原数组的差分数组，即
    .. b[1] = a[1], b[i] = b[i] - b[i-1] (i > 1)
    
< 使用 >
    1. init(n)      : 对数组初始化， n 为数组大小
    2. upd(x, d)    : 在差分数组下标为 x 的位置加上 d
    3. upd(l, r, d) : 在原数组区间 [l, r] 加上 d
    4. sum(x)       : 查询原数组 1 到 x 的前缀和
    5. qry(l, r)    : 查询原数组 l 到 r 的区间和
*/

typedef long long T;
int fn; T c1[N], c2[N];
struct Fenwick {
    void init(int n) {
        fn = n;
        memset(c1, 0, sizeof(c1[0]) * (fn+1));
        memset(c2, 0, sizeof(c2[0]) * (fn+1));
    }
    void upd(int x, T d) { for (int i = x; i <= fn; i += i&-i) c1[i] += d, c2[i] += x * d; }
    void upd(int l, int r, T d) { upd(l, d); upd(r + 1, -d); }
    T sum(int x) { T r = 0; for (int i = x; i; i -= i&-i) r += (x+1) * c1[i] - c2[i]; return r; }
    T qry(int l, int r) { return sum(r) - sum(l-1); }
} fen;
