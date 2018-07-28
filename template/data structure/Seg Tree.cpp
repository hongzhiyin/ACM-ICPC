#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
struct SegTree {
    ll lazy[N << 2], t[N << 2];
    void PushUp(int rt) {
        t[rt] = t[rt << 1] + t[rt << 1 | 1];        // 求和
        // t[rt] = min(t[rt << 1], t[rt << 1 | 1]);    // 最值
    }
    void PushDown(int rt, int m) {
        if (lazy[rt]) {
            lazy[rt << 1] += lazy[rt];
            lazy[rt << 1 | 1] += lazy[rt];
            t[rt << 1] += lazy[rt] * (m - (m >> 1));
            t[rt << 1 | 1] += lazy[rt] * (m >> 1);
            lazy[rt] = 0;
        }
    }
    void build(int l, int r, int rt) {
        lazy[rt] = 0; t[rt] = 0;
        if (l == r) {
            scanf("%lld", &t[rt]);
            return;
        }
        int m = (l + r) >> 1;
        build(lson);
        build(rson);
        PushUp(rt);
    }
    void update(int L, int R, int c, int l, int r, int rt) {
        if (L <= l && r <= R) {
            lazy[rt] += c;
            t[rt] += (ll) c * (r - l + 1);
            return;
        }
        PushDown(rt, r - l + 1);
        int m = (l + r) >> 1;
        if (L <= m) update(L, R, c, lson);
        if (m < R) update(L, R, c, rson);
        PushUp(rt);
    }
    ll query(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            return t[rt];
        }
        PushDown(rt, r - l + 1);
        int m = (l + r) >> 1;
        // 求和
        ll ret = 0;
        if (L <= m) ret += query(L, R, lson);
        if (m < R) ret += query(L, R, rson);
        /*  最值
        ll ret = LINF;
        if (L <= m) ret = min(ret, query(L, R, lson));
        if (m < R) ret = min(ret, query(L, R, rson));
        */
        return ret;
    }
};

// hdu 4578
// 区间加，区间乘，区间赋值，查询区间和，区间平方和，区间立方和
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
struct SegTree {
    int sum[N << 2][4], sz[N << 2], lz_a[N << 2], lz_m[N << 2], lz_s[N << 2];
    void PushUp(int rt) {
        rep(i, 1, 4) sum[rt][i] = add(sum[rt << 1][i], sum[rt << 1 | 1][i]);
    }
    void PushDown(int rt) {
        if (lz_s[rt]) {
            Set(rt << 1, lz_s[rt]);
            Set(rt << 1 | 1, lz_s[rt]);
            lz_s[rt] = 0;
        }
        if (lz_m[rt]) {
            Mul(rt << 1, lz_m[rt]);
            Mul(rt << 1 | 1, lz_m[rt]);
            lz_m[rt] = 0;
        }
        if (lz_a[rt]) {
            Add(rt << 1, lz_a[rt]);
            Add(rt << 1 | 1, lz_a[rt]);
            lz_a[rt] = 0;
        }
    }
    void build(int l, int r, int rt) {
        lz_a[rt] = lz_m[rt] = lz_s[rt] = 0;
        rep(i, 1, 4) sum[rt][i] = 0;
        sz[rt] = r - l + 1;
        if (l == r) {
            return;
        }
        int m = (l + r) >> 1;
        build(lson);
        build(rson);
        PushUp(rt);
    }
    void Add(int rt, int val) {
        lz_a[rt] = add(lz_a[rt], val);
        int sum1 = sum[rt][1], sum2 = sum[rt][2], sum3 = sum[rt][3];
        int val2 = mul(val, val), val3 = mul(val, val2);
        sum[rt][1] = add(sum1, mul(sz[rt], val));
        sum[rt][2] = add(sum2, add(mul(2ll * sum1, val), mul(sz[rt], val2)));
        sum[rt][3] = add(sum3, mul(sz[rt], val3));
        sum[rt][3] = add(sum[rt][3], add(mul(3ll * sum1, val2), mul(3ll * sum2, val)));
    }
    void Mul(int rt, int val) {
        lz_a[rt] = mul(lz_a[rt], val);      // 乘标记改变加标记
        if (lz_m[rt]) lz_m[rt] = mul(lz_m[rt], val);
        else lz_m[rt] = val;
        sum[rt][1] = mul(sum[rt][1], val);
        int val2 = mul(val, val), val3 = mul(val, val2);
        sum[rt][2] = mul(sum[rt][2], val2);
        sum[rt][3] = mul(sum[rt][3], val3);
    }
    void Set(int rt, int val) {
        lz_a[rt] = lz_m[rt] = 0;        // 赋值标记将清空加、乘标记
        lz_s[rt] = val;
        sum[rt][1] = mul(sz[rt], val);
        int val2 = mul(val, val), val3 = mul(val, val2);
        sum[rt][2] = mul(sz[rt], val2);
        sum[rt][3] = mul(sz[rt], val3);
    }
    void update(int op, int L, int R, int val, int l, int r, int rt) {
        if (L <= l && r <= R) {
            if (op == 1) Add(rt, val);
            else if (op == 2) Mul(rt, val);
            else Set(rt, val);
            return ;
        }
        PushDown(rt);
        int m = (l + r) >> 1;
        if (L <= m) update(op, L, R, val, lson);
        if (m < R) update(op, L, R, val, rson);
        PushUp(rt);
    }
    int query(int L, int R, int p, int l, int r, int rt) {
        if (L <= l && r <= R) {
            return sum[rt][p];
        }
        PushDown(rt);
        int m = (l + r) >> 1;
        int ret = 0;
        if (L <= m) ret = add(ret, query(L, R, p, lson));
        if (m < R) ret = add(ret, query(L, R, p, rson));
        return ret;
    }
};
