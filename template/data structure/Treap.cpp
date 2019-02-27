/*
【平衡树思想】
0. 无论是以序列位置为排序关键字，还是以值为排序关键字的二叉平衡树，都想象成一个长条的数组，然后对其分裂与合并。
1. 虽然结构与线段树类似，但关键的区别在于，对于非叶子结点，在线段树中代表区间，在平衡树中代表一个独立的值。
2. 一棵树，代表一个区间，即一个长条数组，而树的根节点，是这个区间中的一个元素，左子树表示其左端区间，右子树同理，这是与线段树的本质区别。
3. 分裂就是把一个长条分成两个长条，合并就是把两个长条按拼在一起。

*/

// 针对序列操作
// 二叉搜索树按 !! 序列位置 !! 排序，左子树结点表示在序列中位置在根结点前面，右子树反之。

#define lson t[rt].l
#define rson t[rt].r
int rt, no;
struct Node { int l, r, val, sum, mi, rnd, sz, rev, ad; } t[N];
void Clear() {  // 初始化， t[0] 表示空结点，注意其值的初始化，例如在处理最值的时候
    rt = no = 0;
    t[0] = (Node){ 0, 0, 0, 0, INF, rand(), 0, 0, 0 };
}
int newnode(int val) { t[++no] = (Node){ 0, 0, val, val, val, rand(), 1, 0, 0 }; return no; }
void ADD(int rt, int val) {  // 区间加
    if (rt == 0) return;
    t[rt].ad += val;
    t[rt].sum += t[rt].sz * val;
    t[rt].val += val;
    t[rt].mi += val;
}
void REV(int rt) {  // 区间反转
    if (rt == 0) return;
    t[rt].rev ^= 1;
    swap(lson, rson);
}
void PushUp(int rt) {
    t[rt].sz = t[lson].sz + t[rson].sz + 1;
    t[rt].sum = t[lson].sum + t[rson].sum + t[rt].val;
    t[rt].mi = min(t[rt].val, min(t[lson].mi, t[rson].mi));
}
void PushDown(int rt) {
    if (t[rt].rev) {
        REV(lson);
        REV(rson);
        t[rt].rev = 0;
    }
    if (t[rt].ad) {
        ADD(lson, t[rt].ad);
        ADD(rson, t[rt].ad);
        t[rt].ad = 0;
    }
}
void split(int rt, int k, int &x, int &y) {  // 将 rt 对应的一段区间分成长度为 k 和 len-k 的两段，对应两颗树，根结点分别为 x 和 y
    PushDown(rt);
    if (!k) { x = 0; y = rt; return ; }
    if (t[rt].sz <= k) { x = rt; y = 0; return ; }
    if (t[lson].sz >= k) { y = rt; split(lson, k, x, lson); }
    else { x = rt; split(rson, k-t[lson].sz-1, rson, y); }
    PushUp(rt);
}
int merge(int x, int y) {  // 将 x 和 y 对应的区间按 x 区间在左， y 区间在右的顺序合并起来，返回合并后的根结点
    if (!x || !y) return x + y;
    PushDown(x); PushDown(y);
    if (t[x].rnd < t[y].rnd) {
        t[x].r = merge(t[x].r, y);
        PushUp(x); return x;
    } else {
        t[y].l = merge(x, t[y].l);
        PushUp(y); return y;
    }
}
void INS(int pos, int val) {  // 在 pos 位置的 !! 后面 !! 插入值为 val 的元素
    int x, y;
    split(rt, pos, x, y);
    rt = merge(merge(x, newnode(val)), y);
}
void DEL(int pos) {  // 删除 pos 位置上的元素
    int x, y, z;
    split(rt, pos-1, x, y); split(y, 1, y, z);
    rt = merge(x, z);
}
void SHR(int rt, int val, int len) {  // rt 对应的区间循环右移 val 次，想循环左移只需要 val 取负值即可
    int x, y;
    val = (val % len + len) % len;
    split(rt, len-val, x, y);
    merge(y, x);
}
void Build(int a[], int n) {  // 初始序列 a[] ，从 1 开始
    rep(i, 1, n+1) rt = merge(rt, newnode(a[i]));
}
void Upd(int l, int r, int op, int val) {  // 区间更新 ( 1. 区间加 ; 2. 区间反转 ; 3. 区间循环右移 )
    int x, y, z;
    split(rt, l-1, x, y); split(y, r-l+1, y, z);
    switch (op) {
        case 1 : ADD(y, val); break;
        case 2 : REV(y); break;
        case 3 : SHR(y, val, r - l + 1); break;
    }
    rt = merge(merge(x, y), z);
}
int Qry(int l, int r, int op) {  // 区间查询 ( 1. 最小值 ; 2. 区间和 )
    int x, y, z;
    split(rt, l-1, x, y); split(y, r-l+1, y, z);
    int res;
    switch (op) {
        case 1 : res = t[y].mi; break;
        case 2 : res = t[y].sum; break;
    }
    rt = merge(merge(x, y), z);
    return res;
}
vi vout;
void out(int rt) {
    PushDown(rt);
    if (lson) out(lson);
    vout.pb(t[rt].val);
    if (rson) out(rson);
}
void print(int rt) {  // 输出 rt 对应区间
    vout.clear();
    out(rt);
    rep(i, 0, sz(vout)) printf("%d%c", vout[i], " \n"[i==sz(vout)-1]);
}

----------------------------------------------------------------------------------------------------

// 针对有序可重集合操作
// 二叉搜索树按 !! 元素值 !! 排序，左子树结点表示所有元素值比根结点元素值小的结点，右子树反之。

#define lson t[rt].l
#define rson t[rt].r
int rt, no;
struct Node { int l, r, val, rnd, sz; } t[N];
void Clear() {
    rt = no = 0;
    t[0] = (Node){ 0, 0, 0, rand(), 0 };
}
int newnode(int val) { t[++no] = (Node){ 0, 0, val, rand(), 1 }; return no; }
void PushUp(int rt) { t[rt].sz = t[lson].sz + t[rson].sz + 1; }
void split(int rt, int k, int &x, int &y) {  // 将 rt 对应的一段区间分成元素值 小于等于 k 和 大于 k 的两段，根结点分别为 x 和 y
    if (!rt) { x = y = 0; return ; }
    if (t[rt].val <= k) { x = rt; split(rson, k, rson, y); }
    else { y = rt; split(lson, k, x, lson); }
    PushUp(rt);
}
int merge(int x, int y) {  // 将 x 和 y 对应的区间按 x 区间在左， y 区间在右的顺序合并起来，返回合并后的根结点
    if (!x || !y) return x + y;
    if (t[x].rnd < t[y].rnd) {
        t[x].r = merge(t[x].r, y);
        PushUp(x); return x;
    } else {
        t[y].l = merge(x, t[y].l);
        PushUp(y); return y;
    }
}
void INS(int val) {  // 在 最后一个 值小于等于 val 的元素后面插入 值为 val 的元素
    int x, y;
    split(rt, val, x, y);
    rt = merge(merge(x, newnode(val)), y);
}
void DEL(int val) {  // 删除 随机一个 值等于 val 的元素，如果不存在则没有影响
    int x, y, z;
    split(rt, val-1, x, y); split(y, val, y, z);
    rt = merge(merge(x, merge(t[y].l, t[y].r)), z);
}
void Build(int a[], int n) {  // 初始序列 a[] ，从 1 开始
    rep(i, 1, n+1) INS(a[i]);
}
int RANK(int val) {  // 查询值为 val 的元素的排名 ( 排名定义为 值比 val 小的元素 的个数 + 1 , 即最前面的 值为 val 的元素 的位置 )
    int x, y, rank;
    split(rt, val-1, x, y);
    rank = t[x].sz + 1;
    rt = merge(x, y);
    return rank;
}
int VAL(int rt, int rank) {  // 查询 rt 对应区间内排名为 rank 的元素的值 val ( rank 相当于位置，具有相同值的元素也有不同的位置 )
    for (;;) {
        if (rank == t[lson].sz + 1) return t[rt].val;
        if (rank <= t[lson].sz) rt = lson;
        else { rank -= t[lson].sz + 1; rt = rson; }
    }
}
int PRE(int val) {  // 返回小于 val 且最大的元素值
    int x, y, pre;
    split(rt, val-1, x, y);
    if (!x) return -INF;  // 若不存在，则返回负无穷
    pre = VAL(x, t[x].sz);
    rt = merge(x, y);
    return pre;
}
int NET(int val) {  // 返回大于 val 且最小的元素值
    int x, y, net;
    split(rt, val, x, y);
    if (!y) return INF;  // 若不存在，则返回正无穷
    net = VAL(y, 1);
    rt = merge(x, y);
    return net;
}
vi vout;
void out(int rt) {
    if (lson) out(lson);
    vout.pb(t[rt].val);
    if (rson) out(rson);
}
void print(int rt) {  // 输出 rt 对应区间
    vout.clear();
    out(rt);
    rep(i, 0, sz(vout)) printf("%d%c", vout[i], " \n"[i==sz(vout)-1]);
}

================================================== Problem Set ==================================================

// cf 159C
// 题意：给一个由子串 t 重复 k 次组成的字符串 s ，每次删去第 p 次出现的字母 ch ，求最终字符串
// 题解：建 26 个字母的 treap ，按顺序插入字母位置，进行删除操作即可。
int Solve() {
    int l = strlen(t), len = 0;
    rep(i, 0, k) rep(j, 0, l) s[len++] = t[j];
    s[len] = '\0';
    rep(i, 0, len) Q[s[i]-'a'].ins(i);
    rep(i, 0, n) {
        int p; char ch[5];
        scanf("%d%s", &p, ch);
        vis[Q[ch[0]-'a'].del(p)] = 1;
    }
    rep(i, 0, len) if (!vis[i]) putchar(s[i]);
    return !puts("");
}
