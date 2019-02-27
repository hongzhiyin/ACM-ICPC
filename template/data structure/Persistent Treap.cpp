// https://www.cnblogs.com/nbwzyzngyl/p/7977369.html
// 基本与非持久化版本相同，修改部分在注释中用 [ 可持久化 ] 注明

// 针对有序可重集合操作
// 二叉搜索树按 !! 元素值 !! 排序，左子树结点表示所有元素值比根结点元素值小的结点，右子树反之。

#define lson t[rt].l
#define rson t[rt].r
int rt[N], no;  // [ 可持久化 ] rt ==> rt[N]
struct Node { int l, r, val, rnd, sz; } t[N<<5];  // t[N] ==> t[N<<5]
void Clear() {
    rt[0] = no = 0;  // [ 可持久化 ] rt ==> rt[0]
    t[0] = (Node){ 0, 0, 0, rand(), 0 };
}
int newnode(int val) { t[++no] = (Node){ 0, 0, val, rand(), 1 }; return no; }
int copynode(int rt) { t[++no] = t[rt]; return no; }  // [ 可持久化 ] 增加 copynode() , 用于 split() 中复制结点
void PushUp(int rt) { t[rt].sz = t[lson].sz + t[rson].sz + 1; }
void split(int rt, int k, int &x, int &y) {  // 将 rt 对应的一段区间分成元素值 小于等于 k 和 大于 k 的两段，根结点分别为 x 和 y
    if (!rt) { x = y = 0; return ; }
    if (t[rt].val <= k) { x = copynode(rt); split(t[x].r, k, t[x].r, y); PushUp(x); }  // [ 可持久化 ] rt ==> x
    else { y = copynode(rt); split(t[y].l, k, x, t[y].l); PushUp(y); }  // [ 可持久化 ] rt ==> y 因此这里也不能用 lson , rson
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
// [ 可持久化 ] 更新操作的函数参数需要使用 &rt
void INS(int &rt, int val) {  // 在 最后一个 值小于等于 val 的元素后面插入 值为 val 的元素
    int x, y;
    split(rt, val, x, y);
    rt = merge(merge(x, newnode(val)), y);
}
void DEL(int &rt, int val) {  // 删除 随机一个 值等于 val 的元素，如果不存在则没有影响
    int x, y, z;
    split(rt, val-1, x, y); split(y, val, y, z);
    rt = merge(merge(x, merge(t[y].l, t[y].r)), z);
}
void Build(int a[], int n) {  // 初始序列 a[] ，从 1 开始
    rep(i, 1, n+1) INS(rt[0], a[i]);  // [ 可持久化 ] rt ==> rt[0]
}
// [ 可持久化 ] 查询操作的函数参数只需要用 rt ，并且复制出来的链不需要合并，因为和原链是一样的，相当于丢弃了这条链
int RANK(int rt, int val) {  // 查询值为 val 的元素的排名 ( 排名定义为 值比 val 小的元素 的个数 + 1 , 即最前面的 值为 val 的元素 的位置 )
    int x, y;
    split(rt, val-1, x, y);
    return t[x].sz + 1;
}
int VAL(int rt, int rank) {  // 查询 rt 对应区间内排名为 rank 的元素的值 val ( rank 相当于位置，具有相同值的元素也有不同的位置 )
    for (;;) {
        if (rank == t[lson].sz + 1) return t[rt].val;
        if (rank <= t[lson].sz) rt = lson;
        else { rank -= t[lson].sz + 1; rt = rson; }
    }
}
int PRE(int rt, int val) {  // 返回小于 val 且最大的元素值
    int x, y;
    split(rt, val-1, x, y);
    if (!x) return -INF;  // 若不存在，则返回负无穷
    return VAL(x, t[x].sz);
}
int NET(int rt, int val) {  // 返回大于 val 且最小的元素值
    int x, y;
    split(rt, val, x, y);
    if (!y) return INF;  // 若不存在，则返回正无穷
    return VAL(y, 1);
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
