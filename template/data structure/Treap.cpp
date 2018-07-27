// 非旋转可持久化 Treap （待填坑）

// https://www.cnblogs.com/nbwzyzngyl/p/7977369.html

// 非旋转 Treap （功能待完善）

// https://www.cnblogs.com/DriverLao/p/8087423.html

void Init() {
    node_cnt = 0;
    ans.init();
}

#define lson T[u].ch[0]
#define rson T[u].ch[1]

struct Node {
    int key, rnd, sz, rev, ch[2];
    void setval(int val) {
        static int seed = 3312;
        key = val;
        rnd = seed = (int)((ll)seed * 48271 % 2147483647);
        sz = 1; ch[0] = ch[1] = 0;
    }
};
int node_cnt;
Node T[N];
struct Treap {
    int root;
    void init() { root = 0; }
    int newnode(int val) {
        T[++node_cnt].setval(val);
        return node_cnt;
    }
    void update(int u) {
        T[u].sz = T[lson].sz + T[rson].sz + 1;
    }
    void pushdown(int u) {
        if (T[u].rev) {
            T[u].rev ^= 1;
            swap(lson, rson);
            T[lson].rev ^= 1;
            T[rson].rev ^= 1;
        }
    }
    void split(int u, int k, int &x, int &y) {
        pushdown(u);
        if (!k) { x = 0; y = u; return; }
        if (T[u].sz == k) { x = u; y = 0; return ; }
        if (T[lson].sz >= k) split(lson, k, x, lson), y = u;
        else split(rson, k - T[lson].sz - 1, rson, y), x = u;
        update(u);
    }
    int merge(int x, int y) {
        if (!x || !y) return x + y;
        pushdown(x); pushdown(y);
        if (T[x].rnd < T[y].rnd) {
            T[x].ch[1] = merge(T[x].ch[1], y);
            update(x); return x;
        } else {
            T[y].ch[0] = merge(x, T[y].ch[0]);
            update(y); return y;
        }
    }
    void out(int u) {
        pushdown(u);
        if (lson) out(lson);
        printf("%d ", T[u].key);
        if (rson) out(rson);
    }
};
Treap ans;

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
struct Treap {
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
