/*
【线段树思想】
0. 考虑线段树问题时，应先想象一个二叉树，每个结点对应一个区间，修改和查询在结点上运动
1. PushUp
    用于区间查询，到相应区间结点便可获得信息
2. PushDown 及 lazy
    用于延迟修改，当有新修改要作用于子节点时，应先把父节点的修改传递下去，并消除父节点的修改
    PushDown 的作用直观地讲就是 : 清空当前结点的所有延迟标记
3. Upd 和 PushDown 中的 Add()
    可能有多个修改累积在同一个结点上，因此 Upd 和 PushDown 的修改应用函数 Add() 可能不同，
    取决于 lazy 标记是否记录了所有修改累积的信息。
4. 当有多种 Add() 操作时，要考虑各种操作的优先级，根据优先级在相应操作中修改其他标记
    如，当想对当前结点打上 A 标记时，若已经存在 B 、 C 、 D 等标记时，应如何处理这些标记，
    对其他标记应该删除或修改？以及 A 标记是否要删除或修改？

*/

/*
// zkw 线段树
// 《统计的力量》 —— 清华大学 张昆玮

【函数功能】
void Init(T a[], int n) : 用长度为 n 的数组 a[] 初始化线段树
T Qry(int l, int r)     : 查询区间 [l, r] 内元素 之和 或 最值
void Upd(int p, int c)  : 单点更新 a[p] 赋值为 c 或 累加上 c
*/

template <class T>
struct SegTree {
    int n; T t[N<<1];
    inline T op(T a, T b) { return ? ; }
    void Init(T a[], int n) {   // 下标从 1 开始
        this->n = n;
        rep(i, 0, n) t[i+n] = a[i+1];
        per(i, 1, n) t[i] = op(t[i<<1], t[i<<1|1]);
    }
    T Qry(int l, int r) {       // 最值 : -INF/INF ; 求和 : 0
        T res = ? ;
        for (l += n-1, r += n-1; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) res = op(res, t[l++]);
            if (~r & 1) res = op(res, t[r--]);
        }
        return res;
    }
    void Upd(int p, int c) {    // 最值 (= c) ; 求和 (+= c)
        for (t[p+=n-1] ? c, p >>= 1; p; p >>= 1)
            t[p] = op(t[p<<1], t[p<<1|1]);
    }
};

/* 基本线段树
如果只是单点更新，则不需要 pushdown 和 Node.upd ，删除这部分以加速程序。
*/

#define ls rt << 1
#define rs rt << 1 | 1
#define lson l, m, ls
#define rson m + 1, r, rs
struct SegmentTree {
    struct Node {
        int len, upd;
        int val;
        Node() : len(0), upd(-1), val(0) {}
        Node(int len, int upd, int val) :
            len(len), upd(upd), val(val) {}
    } node[N<<2];
    inline Node pushUp(Node L, Node R) {
        int len = L.len + R.len, upd = -1;
        int val = ;
        return Node(len, upd, val);
    }
    inline void upd(int rt, int val) {
        node[rt].upd = val;
        node[rt].val = ;
    }
    inline void pushDown(int rt) {
        if (node[rt].upd != -1) {
            upd(ls, node[rt].upd);
            upd(rs, node[rt].upd);
            node[rt].upd = -1;
        }
    }
    inline void build(int l, int r, int rt) {
        if (l == r) {
            node[rt].len = r - l + 1; node[rt].upd = -1;
            node[rt].val = ;
            return;
        }
        int m = (l + r) >> 1;
        build(lson); build(rson);
        node[rt] = pushUp(node[ls], node[rs]);
    }
    inline void upd(int L, int R, int val, int l, int r, int rt) {
        if (L <= l && r <= R) { upd(rt, val); return ; }
        pushDown(rt);
        int m = (l + r) >> 1;
        if (L <= m) upd(L, R, val, lson);
        if (m < R) upd(L, R, val, rson);
        node[rt] = pushUp(node[ls], node[rs]);
    }
    inline Node qry(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) return node[rt];
        pushDown(rt);
        int m = (l + r) >> 1;
        Node res;
        if (L <= m) res = pushUp(res, qry(L, R, lson));
        if (m < R) res = pushUp(res, qry(L, R, rson));
        return res;
    }
};

================================================== Problem Set ==================================================

// hdu 6447
// 二维坐标，严格上升，总权值最大
int Solve() {
    memset(t, 0, sizeof(t)); tmp.clear();
    sort(all(v));
    int cur = -1; ll pre = 0;
    len = -1; rep(i, 0, sz(v)) len = max(len, v[i].dy);
    rep(i, 0, sz(v)) {
        if (v[i].x != cur) {
            cur = v[i].x;
            pre = 0;
            rep(j, 0, sz(tmp)) update(tmp[j].se, tmp[j].fi);
            tmp.clear();
        }
        int r = v[i].dy;
        ll val = max(max(zuo, query(r, r)), query(1, r-1) + v[i].w);
        tmp.pb(mp(val, r));
        pre = max(pre, val);
    }
    rep(j, 0, sz(tmp)) update(tmp[j].se, tmp[j].fi);
    return !printf("%lld\n", query(1, len));
}

----------------------------------------------------------------------------------------------------

// hdu 4578
// 区间加，区间乘，区间赋值，查询区间和，区间平方和，区间立方和
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
int sum[N<<2][4], sz[N<<2], lz_a[N<<2], lz_m[N<<2], lz_s[N<<2];
inline void Add(int rt, int val) {
    lz_a[rt] = add(lz_a[rt], val);
    int sum1 = sum[rt][1], sum2 = sum[rt][2], sum3 = sum[rt][3];
    int val2 = mul(val, val), val3 = mul(val, val2);
    sum[rt][1] = add(sum1, mul(sz[rt], val));
    sum[rt][2] = add(sum2, add(mul(2ll * sum1, val), mul(sz[rt], val2)));
    sum[rt][3] = add(sum3, mul(sz[rt], val3));
    sum[rt][3] = add(sum[rt][3], add(mul(3ll * sum1, val2), mul(3ll * sum2, val)));
}
inline void Mul(int rt, int val) {
    lz_m[rt] = mul(lz_m[rt], val);
    if (lz_a[rt]) lz_a[rt] = mul(lz_a[rt], val);
    int val2 = mul(val, val), val3 = mul(val, val2);
    sum[rt][1] = mul(sum[rt][1], val);
    sum[rt][2] = mul(sum[rt][2], val2);
    sum[rt][3] = mul(sum[rt][3], val3);
}
inline void Set(int rt, int val) {
    lz_a[rt] = 0; lz_m[rt] = 1;
    lz_s[rt] = val;
    int val2 = mul(val, val), val3 = mul(val, val2);
    sum[rt][1] = mul(sz[rt], val);
    sum[rt][2] = mul(sz[rt], val2);
    sum[rt][3] = mul(sz[rt], val3);
}
void PushUp(int rt) {
    rep(i, 1, 4) sum[rt][i] = add(sum[rt<<1][i], sum[rt<<1|1][i]);
}
inline void PushDown(int rt) {
    if (lz_s[rt]) {
        Set(rt << 1, lz_s[rt]);
        Set(rt << 1 | 1, lz_s[rt]);
        lz_s[rt] = 0;
    }
    if (lz_m[rt] != 1) {
        Mul(rt << 1, lz_m[rt]);
        Mul(rt << 1 | 1, lz_m[rt]);
        lz_m[rt] = 1;
    }
    if (lz_a[rt]) {
        Add(rt << 1, lz_a[rt]);
        Add(rt << 1 | 1, lz_a[rt]);
        lz_a[rt] = 0;
    }
}
void build(int l, int r, int rt) {
    lz_a[rt] = lz_s[rt] = 0; lz_m[rt] = 1;
    rep(i, 1, 4) sum[rt][i] = 0;
    sz[rt] = r - l + 1;
    if (l == r) return ;
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    PushUp(rt);
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

----------------------------------------------------------------------------------------------------

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

----------------------------------------------------------------------------------------------------

// https://blog.csdn.net/lwt36/article/details/48908031
// 矩形面积并 （至少被一个矩形覆盖）
// HDU 1542 [POJ 1151]
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
struct SegTree {
    ll cnt[N << 2];
    db t[N << 2], sz[N << 2];       // 注意数据类型，数值范围
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
int Solve() {
    int n = sz(dis) - 2;
    obj.build(1, n, 1);
    db ans = 0;
    rep(i, 0, sz(a)-1) {
        if (a[i].dl < a[i].dr) obj.update(a[i].dl, a[i].dr - 1, a[i].val, 1, n, 1);      // !!! 左闭右开 !!!
        ans += obj.t[1] * (a[i+1].y - a[i].y);
    }
}

----------------------------------------------------------------------------------------------------

// 矩形面积交 （至少被两个以上矩形覆盖）
// HDU 1255
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
struct SegTree {
    ll cnt[N << 2];
    db one[N << 2], two[N << 2], sz[N << 2];        // 注意数据类型，数值范围
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
int Solve() {
    int n = sz(dis) - 2;
    obj.build(1, n, 1);
    db ans = 0;
    rep(i, 0, sz(a)-1) {
        if (a[i].dl < a[i].dr)
            obj.update(a[i].dl, a[i].dr - 1, a[i].val, 1, n, 1);      // !!! 左闭右开 !!!
        ans += obj.two[1] * (a[i+1].y - a[i].y);    // two[1]
    }
}

----------------------------------------------------------------------------------------------------

// 矩形周长并
// HDU 1828 [POJ 1177]
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
struct SegTree {
    ll cnt[N << 2];
    int t[N << 2], sz[N << 2];       // 注意数据类型，数值范围
    void PushUp(int l, int r, int rt) {
        if (cnt[rt]) t[rt] = sz[rt];
        else if (l == r) t[rt] = 0;
        else t[rt] = t[rt << 1] + t[rt << 1 | 1];
    }
    void build(int i, int l, int r, int rt) {
        cnt[rt] = 0; t[rt] = 0; sz[rt] = dis[i][r+1] - dis[i][l];    // 左闭右开，求的长度
        if (l == r) return;
        int m = (l + r) >> 1;
        build(i, lson);
        build(i, rson);
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
// 横竖两次扫描线
// 注意边重合时，要先计算 +1 的边，再计算 -1 的边
struct Line {
    int l, r, h;
    int val, dl, dr;
    Line (int l, int r, int h, int val) : l(l), r(r), h(h), val(val) {}
    bool operator < (const Line &rhs) const {
        return h != rhs.h ? h < rhs.h : val > rhs.val;      // 特殊处理边重合的情况
    }
};
int Solve() {
    int ans = 0;
    rep(i, 0, 2) {
        rep(j, 0, sz(line[i])) {
            line[i][j].dl = lower_bound(all(dis[i]), line[i][j].l) - dis[i].begin();
            line[i][j].dr = lower_bound(all(dis[i]), line[i][j].r) - dis[i].begin();
        }
        int n = sz(dis[i]) - 2, pre = 0;
        obj.build(i, 1, n, 1);
        rep(j, 0, sz(line[i])) {
            if (line[i][j].dl < line[i][j].dr)
                obj.update(line[i][j].dl, line[i][j].dr-1, line[i][j].val, 1, n, 1);
            ans += (int)fabs(obj.t[1] - pre);
            pre = obj.t[1];
        }
    }
}

----------------------------------------------------------------------------------------------------

// 立方体体积交（普通交只需要截面覆盖两次及以上即可，本题依具体题意要求覆盖三次及以上）
// hdu 3642
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
struct SegTree {
    ll cnt[N << 2];
    ll one[N << 2], two[N << 2], thre[N << 2], sz[N << 2];      // 注意数据类型，数值范围
    void PushUp(int l, int r, int rt) {
        if (cnt[rt] >= 3) thre[rt] = two[rt] = one[rt] = sz[rt];
        else if (cnt[rt] == 2) {
            two[rt] = one[rt] = sz[rt];
            if (l == r) thre[rt] = 0;
            else thre[rt] = one[rt << 1] + one[rt << 1 | 1];
            // 注意细节，当 cnt = (y)，则 (x)[rt] = (y-x)[rt<<1] + (y-x)[rt<<1|1]
        } else if (cnt[rt] == 1) {
            one[rt] = sz[rt];
            if (l == r) thre[rt] = two[rt] = 0;
            else {
                thre[rt] = two[rt << 1] + two[rt << 1 | 1];
                two[rt] = one[rt << 1] + one[rt << 1 | 1];
            }
        } else {
            if (l == r) one[rt] = two[rt] = thre[rt] = 0;
            else {
                one[rt] = one[rt << 1] + one[rt << 1 | 1];
                two[rt] = two[rt << 1] + two[rt << 1 | 1];
                thre[rt] = thre[rt << 1] + thre[rt << 1 | 1];
            }
        }
    }
    void build(int l, int r, int rt) {
        cnt[rt] = 0; one[rt] = two[rt] = thre[rt] = 0; sz[rt] = dis[r+1] - dis[l];    // 左闭右开，求的长度
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
// 枚举 z 轴（如果 z 值范围比较小）
// 然后在每个截面上做矩形面积交，相交次数依具体题意而定
int Solve() {
    ll ans = 0;
    rep(i, 0, sz(dz)-1) {
        line.clear(); dis.clear(); dis.pb(-INF);
        rep(j, 0, sz(c)) {
            // 判断立方体在该 z 坐标下是否有截面，即下底面 <= z ，上底面 > z
            if (c[j].z1 <= dz[i] && c[j].z2 > dz[i]) {
                line.pb(Line(c[j].x1, c[j].x2, c[j].y1, 1));
                line.pb(Line(c[j].x1, c[j].x2, c[j].y2, -1));
                dis.pb(c[j].x1); dis.pb(c[j].x2);
            }
        }
        sort(all(line));
        // 离散化 x 坐标
        sort(all(dis)); dis.erase(unique(all(dis)), dis.end());
        rep(j, 0, sz(line)) {
            line[j].dl = lower_bound(all(dis), line[j].l) - dis.begin();
            line[j].dr = lower_bound(all(dis), line[j].r) - dis.begin();
        }
        // 矩形面积交
        int n = sz(dis) - 2;
        obj.build(1, n, 1);
        rep(j, 0, sz(line)-1) {
            if (line[j].dl < line[j].dr)
                obj.update(line[j].dl, line[j].dr-1, line[j].val, 1, n, 1);
            ans += (ll)obj.thre[1] * (line[j+1].y - line[j].y) * (dz[i+1] - dz[i]);
        }
    }
}
