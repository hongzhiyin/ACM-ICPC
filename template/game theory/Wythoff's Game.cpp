// 有两堆各若干个物品，两个人轮流从任一堆取至少一个或同时从两堆中取同样多的物品，规定每次至少取一个，多者不限，最后取光者得胜。

// 必败态性质：

// 第 k 个必败态:
ak = (int)(k * (1 + √5) / 2)
bk = ak + k 

// 必败态判断：

if (a > b) swap(a, b);
int k = b - a;
if ((int)(k * (1 + sqrt(5)) / 2) == a) puts("LOSE");
else puts("WIN");

// 非必败态转化为必败态：

// 必败态预处理，loss[i] 表示第 i 个必败态
// posa[i] 表示必败态 (x, y) 中，当 x == i 时，该必败态在 loss[] 中的位置，不存在则为 -1，posb[] 同理
memset(posa, -1, sizeof(posa));
memset(posb, -1, sizeof(posb));
rep(k, 0, N) {
    int a, b;
    a = (int)(k * (1 + sqrt(5)) / 2);
    b = a + k;
    loss[k] = mp(a, b);
    posa[a] = posb[b] = k;
}

// a, b 为某非必败态，x, y 为转化到的必败态
if (a > b) swap(a, b);
int k = b - a;
int x, y;
if (a > loss[k].fi) {
    x = loss[k].fi; y = loss[k].se;
    printf("%d %d\n", x, y);
}
if (posa[a] != -1 && y > a + posa[a]) {
    x = a; y = a + posa[a];
    printf("%d %d\n", x, y);
}
if (posb[b] != -1 && x > b - posb[b]) {
    x = b - posb[b]; y = b;
    printf("%d %d\n", x, y);
}
if (posb[a] != -1) {
    x = a - posb[a]; y = a;
    printf("%d %d\n", x, y);
    /// 怀疑要判重，但是 A 了
}

// 参考博客：https://blog.csdn.net/Jason_crawford/article/details/52129969
// 博客里分类 4 里的情况 1 其实与分类 1 重复了。
