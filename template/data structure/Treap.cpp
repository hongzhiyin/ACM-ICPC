struct Node {
    int key, pri, sz, son[2];
    void setval(int x, int z = 1) {
        static int seed = 3312;
        key = x;
        pri = seed = (int)((ll)seed * 48271 % 2147483647);
        sz = z;
        son[0] = son[1] = 0;
    }
};
int cnt;    // 在 Init() 里初始化，通过一个 cnt 和 一个 T[N] 给多个 Treap 分配节点
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
            T[x = cnt++].setval(val);
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
};
