/*
【函数功能】
void Init(int n)     : 初始化大小为 n 的树状数组
T Sum(int x)         : 返回前 x 个元素之和
T Qry(int l, int r)  : 返回区间 [l, r] 内元素之和
void Add(int x, T d) : 第 x 个元素加上 d

【注意事项】
1. 下标从 1 开始
2. 如果下标过大，需要离散化
*/

struct Fenwick {
    int n; ll t[N]; // map <int, int> t;
    void Init(int n) {
        this->n = n;
        memset(t, 0, sizeof(t));
    }
    ll Sum(int x) {
        ll ret = 0;
        for (; x > 0; x -= x&-x) ret += t[x];
        return ret;
    }
    ll Qry(int l, int r) { return Sum(r) - Sum(l-1); }
    void Add(int x, ll d) { for (; x <= n; x += x&-x) t[x] += d; }
};

/* 区间修改，区间查询
【函数功能】
void Init(int a[], int n)   : 根据大小为 n 的数组 a[] 初始化树状数组
void Upd(int l, int r, T x) : 区间 [l, r] 内元素都加上 x
T Qry(int l, int r)         : 返回区间 [l, r] 内元素之和
*/

template <class T>
struct Sec_Fenwick {
    Fenwick <T> c1, c2;
    void Init(T a[], int n) {    // a[] 下标从 1 开始， a[0] = 0
        c1.Init(n); c2.Init(n);
        rep(i, 1, n+1) {
            c1.Add(i, a[i] - a[i-1]);
            c2.Add(i, (i-1) * (a[i] - a[i-1]));
        }
    }
    void Upd(int l, int r, T x) {
        c1.Add(l, x); c1.Add(r+1, -x);
        c2.Add(l, (l-1) * x); c2.Add(r+1, r * -x);
    }
    T Qry(int l, int r) {
        T R = r * c1.Sum(r) - c2.Sum(r);
        T L = (l-1) * c1.Sum(l-1) - c2.Sum(l-1);
        return R - L;
    }
};
