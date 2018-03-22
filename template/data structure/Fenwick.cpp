struct Fenwick {    //注意下标从 1 开始，以及可能需要离散化操作
    int n; ll tree[N];

    int Lowbit(int x) { return x & -x; }

    void Init(int n) {
        memset(tree, 0, sizeof(tree));
        this->n = n;
    }

    ll Sum(int x) {
        ll ret = 0;
        for (; x > 0; x -= Lowbit(x))
            ret += tree[x];
            //ret = add(ret, tree[x]);
        return ret;
    }

    void Add(int x, ll d) {
        for (; x <= n; x += Lowbit(x))
            tree[x] += d;
            //tree[x] = add(tree[x], d);
    }
};

//区间修改，区间查询
Fenwick c1, c2;
void FenInit(ll *a)     //a[]下标从1开始，a[0] = 0
{
    c1.Init(n); c2.Init(n);
    rep(i, 1, n+1) {
        c1.Add(i, a[i] - a[i-1]);
        c2.Add(i, (i-1) * (a[i] - a[i-1]));
    }
}

void FenUpdate(ll l, ll r, ll x)
{
    c1.Add(l, x); c1.Add(r+1, -x);
    c2.Add(l, (l-1) * x); c2.Add(r+1, r * -x);
    //c2.Add(l, (l-1) * x % MOD); c2.Add(r+1, r * -x % MOD);
}

ll FenQuery(ll l, ll r)
{
    ll R = r * c1.Sum(r) - c2.Sum(r);
    ll L = (l-1) * c1.Sum(l-1) - c2.Sum(l-1);
    return R - L;
    /*
    ll R = add(r * c1.Sum(r) - c2.Sum(r), MOD) ;
    ll L = add((l-1) * c1.Sum(l-1) - c2.Sum(l-1), MOD);
    return add(R - L, MOD);
    */
}
