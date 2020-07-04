/* ----- 并查集 -----
< 使用 >
    1. 在构造时初始化
*/

struct Disjoint_Set_Union {
    vector <int> fa;

    Disjoint_Set_Union(int n) {
        fa.clear(); fa.resize(n+1);
        for (int i = 0; i <= n; ++i) fa[i] = i;
    }

    int Find(int x) { return x == fa[x] ? x : fa[x] = Find(fa[x]); }

    void Union(int x, int y) { fa[Find(y)] = Find(x); }
};