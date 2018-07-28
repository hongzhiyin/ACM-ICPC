#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
struct SegTree {
    ll lazy[N << 2], t[N << 2];
    void PushUp(int rt) {
        t[rt] = t[rt << 1] + t[rt << 1 | 1];
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
        lazy[rt] = 0;
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
        ll ret = 0;
        if (L <= m) ret += query(L, R, lson);
        if (m < R) ret += query(L, R, rson);
        return ret;
    }
};
