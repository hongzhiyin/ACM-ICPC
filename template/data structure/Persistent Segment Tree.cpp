/*
【可持久化线段树思想】
1. 每一个版本的线段树其实代表一条链，通过 rt[] 标识根节点。
2. 每次生成新版本，即为复制依赖版本的一条链，并稍加修改
*/

int rt[N], no;
struct { int sum, l, r; } t[N<<5];
inline void upd(int &now, int pos, int val, int l, int r) {
    t[++no] = t[now]; now = no;
    t[now].sum += val;
    if (l == r) return ;
    int m = l + r >> 1;
    if (pos <= m) upd(t[now].l, pos, val, l, m);
    else upd(t[now].r, pos, val, m + 1, r);
}
inline int mink(int L, int R, int k, int l, int r) {
    if (l == r) return l;
    int m = l + r >> 1, sum = t[t[R].l].sum - t[t[L].l].sum;
    if (sum >= k) return mink(t[L].l, t[R].l, k, l, m);
    return mink(t[L].r, t[R].r, k - sum, m + 1, r);
}
int Qrymink(int l, int r, int k) {
    return mink(rt[l-1], rt[r], k, -INF, INF);  // 根据具体情况设置值域
}
int Qrymaxk(int l, int r, int k) {
    return Qrymink(l, r, r - l - k + 2);
}

void init() {
    no = 0;
    rep(i, 1, n+1) upd(rt[i]=rt[i-1], a[i], 1, -INF, INF);  // 根据具体情况设置值域
}
