/*
【平衡树思想】
0. 无论是以序列位置为排序关键字，还是以值为排序关键字的二叉平衡树，都想象成一个长条的数组，然后对其分裂与合并。
*/

// 非旋转可持久化 Treap （待填坑）

// https://www.cnblogs.com/nbwzyzngyl/p/7977369.html

// 非旋转 Treap （功能待完善）
// https://www.cnblogs.com/DriverLao/p/8087423.html

// 针对序列操作
// 二叉搜索树按序列排序，左子树结点表示在序列中位置在根结点前面，右子树反之。
// 待填坑 http://bailian.openjudge.cn/practice/4090/
#define lson t[rt].l
#define rson t[rt].r
int rt, no;
struct Node { int l, r, val, rnd, sz, rev; } t[N];
void Clear() { no = 0; }
int newnode(int val) { t[++no] = (Node){ 0, 0, val, rand(), 1, 0 }; return no; }
void PushUp(int rt) { t[rt].sz = t[lson].sz + t[rson].sz + 1; }
void PushDown(int rt) {
    if (t[rt].rev) {
        t[rt].rev = 0;
        swap(lson, rson);
        t[lson].rev ^= 1;
        t[rson].rev ^= 1;
    }
}
void split(int rt, int k, int &x, int &y) {
    PushDown(rt);
    if (!k) { x = 0; y = rt; return ; }
    if (t[rt].sz == k) { x = rt; y = 0; return ; }
    if (t[lson].sz >= k) { split(lson, k, x, lson); y = rt; }
    else { split(rson, k-t[lson].sz-1, rson, y); x = rt; }
    PushUp(rt);
}
int merge(int x, int y) {
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
vi vout;
void out(int rt) {
    PushDown(rt);
    if (lson) out(lson);
    vout.pb(t[rt].val);
    if (rson) out(rson);
}


// 旋转 Treap
void Init() {
    treap_cnt = 1;
    T[0].key = T[0].pri = T[0].sz = T[0].son[0] = T[0].son[1] = 0;
}

struct Node {
    int key, pri, sz, son[2];
    void setval(int x) {
        static int seed = 3312;
        key = x;
        pri = seed = (int)((ll)seed * 48271 % 2147483647);
        sz = 1;
        son[0] = son[1] = 0;
    }
};
int treap_cnt;    // 在 Init() 里初始化，通过一个 cnt 和 一个 T[N] 给多个 Treap 分配节点
Node T[N];
struct Treap {		// 适合集合查找第 k 大元素
    int root;
    void init() { root = 0; }
    void rotate(int &x, int p) {
        int y = T[x].son[!p];
        T[x].son[!p] = T[y].son[p];
        T[y].son[p] = x;
        T[y].sz = T[x].sz;
        T[x].sz = T[T[x].son[0]].sz + 1 + T[T[x].son[1]].sz;
        x = y;
    }
    // 执行插入和删除操作前要用 find(ans.root, x) 检验操作是否合法
    void ins(int &x, int val) {     // 往集合中插入值 val，调用方法：ans.ins(ans.root, val)
        if (x == 0) {
            T[x = treap_cnt++].setval(val);
        } else {
            ++T[x].sz;
            int p = val > T[x].key;
            ins(T[x].son[p], val);
            if (T[x].pri > T[T[x].son[p]].pri)
                rotate(x, !p);
        }
    }
    void del(int &x, int val) {     // 从集合中删除值 val
        if (T[x].key == val) {
            if (T[x].son[0] && T[x].son[1]) {
                --T[x].sz;
                int p = T[T[x].son[0]].pri < T[T[x].son[1]].pri;
                rotate(x, p);
                del(T[x].son[p], val);
            } else {
                if (!T[x].son[0]) x = T[x].son[1];
                else x = T[x].son[0];
            }
        } else {
            --T[x].sz;
            int p = T[x].key < val;
            del(T[x].son[p], val);
        }
    }
    int findKth(int &x, int k) {    // 查找集合中第 k 小的元素，返回值为对应元素的编号，若不存在，则返回 -1
        if (k <= 0 || x == 0 || k > T[x].sz) return -1;
        if (k == T[T[x].son[0]].sz + 1) return x;
        if (k > T[T[x].son[0]].sz + 1)
            return findKth(T[x].son[1], k - T[T[x].son[0]].sz - 1);
        return findKth(T[x].son[0], k);
    }
    int find(int &x, int val) {     // 查找集合中值为 val 的元素，返回值为对应元素的编号，若不存在，则返回 -1
        if (x == 0) return -1;
        if (val == T[x].key) return x;
        return find(T[x].son[T[x].key < val], val);
    }
    int Count(int &x, int val) {    // 查找集合中小于值 val 的元素个数，返回值为元素个数，同时也表示 val 是集合中第 Count+1 小的元素
        if (x == 0) return 0;
        if (val < T[x].key) return Count(T[x].son[0], val);
        if (val == T[x].key) return T[T[x].son[0]].sz;
        return T[x].sz - T[T[x].son[1]].sz + Count(T[x].son[1], val);
    }
    void Merge(int &src) {          // 把根为 src 的 treap 合并到根为 root 的本 treap 中
        if (T[src].son[0]) Merge(T[src].son[0]);
        if (T[src].son[1]) Merge(T[src].son[1]);
        ins(root, T[src].key);
    }
};

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
