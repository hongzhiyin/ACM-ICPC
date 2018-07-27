struct Fenwick {    //注意下标从 1 开始，以及可能需要离散化操作
    int n; ll t[N];
    int Lowbit(int x) { return x & -x; }
    void Init(int n) {
        memset(tree, 0, sizeof(tree));
        this->n = n;
    }
    ll Sum(int x) {
        ll ret = 0;
        for (; x > 0; x -= Lowbit(x))
            ret += t[x];
            //ret = add(ret, t[x]);
        return ret;
    }
    void Add(int x, ll d) {
        for (; x <= n; x += Lowbit(x))
            t[x] += d;
            //t[x] = add(t[x], d);
    }
    
    // 区间最值 （需要传入原数组 a[]）
    void update(int x, int d, int *a) {     // 将 a[x] 更新为 d
        for (a[x] = d; x <= n; x += Lowbit(x)) {
            t[x] = a[x];
            for(int i = 1; i < Lowbit(x); i <<= 1)
                t[x] = max(t[x], t[x-i]);
        }
    }
    int query(int l, int r, int *a) {       // 求 [l, r] 的最值
        int ans = 0;
        while (r >= l) {
            ans = max(a[r], ans);
            for (--r; r-Lowbit(r) >= l; r -= Lowbit(r))
                ans = max(t[r], ans);
        }
        return ans;
    }
};

//区间修改，区间查询
struct Sec_Fenwick {
    Fenwick c1, c2;
    void Init(ll *a, int n) {    //a[] 下标从 1 开始， a[0] = 0
        c1.Init(n); c2.Init(n);
        rep(i, 1, n+1) {
            c1.Add(i, a[i] - a[i-1]);
            c2.Add(i, (i-1) * (a[i] - a[i-1]));
        }
    }
    void Update(ll l, ll r, ll x) {
        c1.Add(l, x); c1.Add(r+1, -x);
        c2.Add(l, (l-1) * x); c2.Add(r+1, r * -x);
        //c2.Add(l, (l-1) * x % MOD); c2.Add(r+1, r * -x % MOD);
    }
    ll Query(ll l, ll r) {
        ll R = r * c1.Sum(r) - c2.Sum(r);
        ll L = (l-1) * c1.Sum(l-1) - c2.Sum(l-1);
        return R - L;
        /*
        ll R = add(r * c1.Sum(r) - c2.Sum(r), MOD) ;
        ll L = add((l-1) * c1.Sum(l-1) - c2.Sum(l-1), MOD);
        return add(R - L, MOD);
        */
    }
};
