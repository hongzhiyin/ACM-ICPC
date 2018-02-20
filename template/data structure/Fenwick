struct Fenwick {    //注意下标从 1 开始，以及可能需要离散化操作
    int n, tree[N];

    int Lowbit(int x) {
        return x & -x;
    }

    void Init(int n) {
        memset(tree, 0, sizeof(tree));
        this -> n = n;
    }

    int Sum(int x) {
        int ret = 0;
        while (x > 0) {
            ret += tree[x];
            x -= Lowbit(x);
        }
        return ret;
    }

    void Add(int x, int d) {
        while (x <= n) {
            tree[x] += d;
            x += Lowbit(x);
        }
    }
};
