https://blog.csdn.net/Stupid_Turtle/article/details/80445998

/*
【可持久化线段树思想】
1. 每一个版本的线段树其实代表一条链，通过 rt[] 标识根节点。（如果有初始版本，则调用 Build() 先生成一棵二叉树）
2. 参数中的 y 代表所依赖的版本， x 代表正在生成的新版本，每次生成新版本，即为复制依赖版本的一条链，并稍加修改
3. 结点空间 t[] ，通过 ++no 申请新的结点， t[0] 用于在尚未有依赖版本的结点时，所复制的结点，相当于新建结点，对 t[0] 可能需要初始化
*/

#define lson l, m, t[y].l
#define rson m + 1, r, t[y].r
int rt[N], no;
struct Node { int l, r, val; } t[N<<5];
void Clear() {
    no = 0;
    t[0].l = t[0].r = 0;
}
void PushUp(int rt) {
    t[rt].val = op(t[t[rt].l].val, t[t[rt].r].val);
}
void Build(int &x, int l, int r) {
    x = ++no;
    if (l == r) { t[x].val = a[l]; return; }
    int m = (l + r) >> 1;
    Build(t[x].l, l, m); Build(t[x].r, m + 1, r);
}
void Upd(int &x, int pos, int val, int l, int r, int y) {
    t[x=++no] = t[y];
    if (l == r) { t[x].val = val; return; }
    int m = (l + r) >> 1;
    if (pos <= m) Upd(t[x].l, pos, val, lson);
    else Upd(t[x].r, pos, val, rson);
    PushUp(x);
}
