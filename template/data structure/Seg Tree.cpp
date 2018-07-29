// 基本线段树
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
struct SegTree {
    ll lazy[N << 2], t[N << 2], sz[N << 2];
    void PushUp(int rt) {
        t[rt] = t[rt << 1] + t[rt << 1 | 1];        // 求和
        // t[rt] = min(t[rt << 1], t[rt << 1 | 1]);    // 最值
    }
    void PushDown(int rt) {
        if (lazy[rt]) {
            Add(rt << 1, lazy[rt]);
            Add(rt << 1 | 1, lazy[rt]);
            lazy[rt] = 0;
        }
    }
    void Add(int rt, int val) {
        lazy[rt] += val;
        t[rt] += val * sz[rt];
    }
    void build(int l, int r, int rt) {
        lazy[rt] = 0; t[rt] = 0; sz[rt] = r - l + 1;
        if (l == r) {
            scanf("%lld", &t[rt]);
            return;
        }
        int m = (l + r) >> 1;
        build(lson);
        build(rson);
        PushUp(rt);
    }
    void update(int L, int R, int val, int l, int r, int rt) {
        if (L <= l && r <= R) {
            Add(rt, val);
            return;
        }
        PushDown(rt);
        int m = (l + r) >> 1;
        if (L <= m) update(L, R, val, lson);
        if (m < R) update(L, R, val, rson);
        PushUp(rt);
    }
    ll query(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            return t[rt];
        }
        PushDown(rt);
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

// POJ 3667
// 区间合并
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
struct SegTree {    // lsum 左端开始往右最长空区间，rsum 右端开始往左最长空区间，sum 区间内最大长度空区间
    ll lazy[N << 2], lsum[N << 2], rsum[N << 2], sum[N << 2], sz[N << 2];
    void PushUp(int rt) {
        lsum[rt] = lsum[rt << 1];
        rsum[rt] = rsum[rt << 1 | 1];
        if (lsum[rt] == sz[rt] + 1 >> 1) lsum[rt] += lsum[rt << 1 | 1];
        if (rsum[rt] == sz[rt] >> 1) rsum[rt] += rsum[rt << 1];
        sum[rt] = max(rsum[rt << 1] + lsum[rt << 1 | 1], max(sum[rt << 1], sum[rt << 1 | 1]));
    }
    void PushDown(int rt) {
        if (lazy[rt] != -1) {   // lazy ： -1 表示无操作，0 表示置空，1 表示置满
            Set(rt << 1, lazy[rt]);
            Set(rt << 1 | 1, lazy[rt]);
            lazy[rt] = -1;
        }
    }
    void Set(int rt, int val) {
        lazy[rt] = val;
        if (lazy[rt]) lsum[rt] = rsum[rt] = sum[rt] = 0;    // 置满，则剩余空区间为 0
        else lsum[rt] = rsum[rt] = sum[rt] = sz[rt];        // 置空，则剩余空区间为区间长度
    }
    void build(int l, int r, int rt) {
        sum[rt] = lsum[rt] = rsum[rt] = sz[rt] = r - l + 1;
        lazy[rt] = -1;
        if (l == r) return;
        int m = (l + r) >> 1;
        build(lson);
        build(rson);
    }
    void update(int L, int R, int val, int l, int r, int rt) {  // 更新区间 [L, R]，val = 0 置空， val = 1 置满
        if (L <= l && r <= R) {
            Set(rt, val);
            return;
        }
        PushDown(rt);
        int m = (l + r) >> 1;
        if (L <= m) update(L, R, val, lson);
        if (m < R) update(L, R, val, rson);
        PushUp(rt);
    }
    // 查询最左边能满足 val 长度的空区间的左端点，主函数中用 obj.sum[1] >= val 判断是否存在满足条件的区间
    int query(int val, int l, int r, int rt) {
        if (l == r) return l;
        PushDown(rt);
        int m = (l + r) >> 1;
        if (sum[rt << 1] >= val)
            return query(val, lson);
        else if (rsum[rt << 1] + lsum[rt << 1 | 1] >= val)
            return m - rsum[rt<<1] + 1;
        else
            return query(val, rson);
    }
};

// 矩形面积并 （至少被一个矩形覆盖）
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
struct SegTree {
    ll cnt[N << 2];
    db t[N << 2], sz[N << 2];
    void PushUp(int l, int r, int rt) {
        if (cnt[rt]) t[rt] = sz[rt];
        else if (l == r) t[rt] = 0;
        else t[rt] = t[rt << 1] + t[rt << 1 | 1];
    }
    void build(int l, int r, int rt) {
        cnt[rt] = 0; t[rt] = 0; sz[rt] = dis[r+1] - dis[l];    // 左闭右开，求的长度
        if (l == r) return;
        int m = (l + r) >> 1;
        build(lson);
        build(rson);
    }
    void update(int L, int R, int val, int l, int r, int rt) {
        if (L <= l && r <= R) {
            cnt[rt] += val;
            PushUp(l, r, rt);
            return;
        }
        int m = (l + r) >> 1;
        if (L <= m) update(L, R, val, lson);
        if (m < R) update(L, R, val, rson);
        PushUp(l, r, rt);
    }
};

int n = sz(dis) - 2;
obj.build(1, n, 1);
db ans = 0;
rep(i, 0, sz(a)-1) {
    if (a[i].dl < a[i].dr) obj.update(a[i].dl, a[i].dr - 1, a[i].val, 1, n, 1);      // !!! 左闭右开 !!!
    ans += obj.t[1] * (a[i+1].y - a[i].y);
}

// 矩形面积交 （至少被两个以上矩形覆盖）
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
struct SegTree {
    ll cnt[N << 2];
    db one[N << 2], two[N << 2], sz[N << 2];
    void PushUp(int l, int r, int rt) {
        if (cnt[rt] >= 2) two[rt] = one[rt] = sz[rt];
        else if (cnt[rt] == 1) {
            one[rt] = sz[rt];
            if (l == r) two[rt] = 0;
            else two[rt] = one[rt << 1] + one[rt << 1 | 1];
            // 若干覆盖次数为 1 的区间，再在它们的父区间上再加一次覆盖，就变成覆盖次数为 2 的区间
        } else {
            if (l == r) one[rt] = two[rt] = 0;
            else {
                one[rt] = one[rt << 1] + one[rt << 1 | 1];
                two[rt] = two[rt << 1] + two[rt << 1 | 1];
            }
        }
    }
    void build(int l, int r, int rt) {
        cnt[rt] = 0; one[rt] = two[rt] = 0; sz[rt] = dis[r+1] - dis[l];    // 左闭右开，求的长度
        if (l == r) return;
        int m = (l + r) >> 1;
        build(lson);
        build(rson);
    }
    void update(int L, int R, int val, int l, int r, int rt) {
        if (L <= l && r <= R) {
            cnt[rt] += val;
            PushUp(l, r, rt);
            return;
        }
        int m = (l + r) >> 1;
        if (L <= m) update(L, R, val, lson);
        if (m < R) update(L, R, val, rson);
        PushUp(l, r, rt);
    }
};

int n = sz(dis) - 2;
obj.build(1, n, 1);
db ans = 0;
rep(i, 0, sz(a)-1) {
    if (a[i].dl < a[i].dr)
        obj.update(a[i].dl, a[i].dr - 1, a[i].val, 1, n, 1);      // !!! 左闭右开 !!!
    ans += obj.two[1] * (a[i+1].y - a[i].y);    // two[1]
}
