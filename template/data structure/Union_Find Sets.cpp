void Init(int n) { rep(i, 0, n) fa[i] = i; }

int Find(int x) { return fa[x] == x ? x : fa[x] = Find(fa[x]); }

void Union(int x, int y) { fa[Find(y)] = Find(x); }

void Split(int a, int b)
{
    int Fa = Find(a), Fb = b;
    int tmp = to[a]; to[a] = to[b]; to[b] = tmp;
    while (Find(b) == Fa) {
        fa[b] = Fb;
        b = to[b];
    }
}

================================================== Problem Set ==================================================

// poj 1182
// 通过并查集判断发生事件是否矛盾
// https://blog.csdn.net/jxust_tj/article/details/43668901

// 在某一条件下，枚举 x 会出现的所有情况，
// 然后把 x 处在这些情况下，其他必然出现的情况，都分到同一集合
// 例如，在 d = 1 的情况下，会出现 x 属于 A ， x 属于 B ， x 属于 C 三种情况
// 而这三种情况又各自对应 y 必然会出现的所有情况
// 例如，在 d = 1 ， x 属于 A 的情况下，必然出现 y 属于 A 的情况。
// 这样，在每一个条件下，
// 就可将某一元素会出现的所有情况与其所对应的必然会出现的其他情况合并到同一集合下
// 集合中的元素表示：要么同时发生，要么同时不发生
// 这样，在判断是否矛盾时，只要查看互斥的两种情况是否属于同一集合下即可
// 而情况的编号，可以设置一个偏移量 N 等于元素种数
// 这样，对于编号 x + k * N 就表示 x 出现了第 k 种情况
// 假设，当 x 出现第 k 种情况时，必然会使 y 出现第 p 种情况
// 那么就可以将 x + k * N 与 y + p * N 合并到同一集合

int Solve() {
    int ans = 0;
    while (k--) {
        int d, x, y;
        scanf("%d%d%d", &d, &x, &y);
        if (x > n || y > n) { ans++; continue; }
        if (d == 1) {
            // 因为一次性将 x 的三种情况及其对应情况都加入集合，所以在判断时，只需要取 x 的一种情况来判断
            if (find(x) == find(y+n) || find(x) == find(y + 2*n)) {
                ans++;
            } else {
                Union(x, y);
                Union(x+n, y+n);
                Union(x+2*n, y+2*n);
            }
        } else {
            if (find(x) == find(y) || find(x) == find(y+2*n)) {
                ans++;
            } else {
                Union(x, y+n);
                Union(x+n, y+2*n);
                Union(x+2*n, y);
            }
        }
    }
    return !printf("%d\n", ans);
}
