int add(ll a, int b) { if ((a += b) >= MOD) a -= MOD; return a; }
int mul(ll a, int b) { if ((a *= b) >= MOD) a %= MOD; return a; }
struct Mat {
    vector<vi> a;
    Mat() {}
    Mat(int n, int m) { a.resize(n, vi(m)); }
    Mat operator * (Mat &b) {
        int n = sz(a), m = sz(b.a[0]), nm = sz(b.a); Mat r(n, m);
        rep(i, 0, n) rep(j, 0, m) rep(k, 0, nm)
            r.a[i][j] = add(r.a[i][j], mul(a[i][k], b.a[k][j]));
        return r;
        /*  当 r.a[i][j] 的最大值不会溢出时
        rep(i, 0, n) rep(j, 0, m) {
            rep(k, 0, nm) r.a[i][j] += a[i][k] * b.a[k][j];
            r.a[i][j] %= MOD;
        }
        */
    }
    Mat operator ^ (ll b) {
        int n = sz(a); Mat r(n, n), t = *this;
        rep(i, 0, sz(r.a)) r.a[i][i] = 1;
        for (; b; b >>= 1) {
            if (b & 1) r = r * t;
            t = t * t;
        }
        return r;
    }
    void out() {
        for (auto r : a) rep(i, 0, sz(r))
            printf("%d%c", r[i], " \n"[i==sz(r)-1]);
    }
};

// 矩阵快速幂求斐波那契数列第 n 项
// [ f[n], f[n-1] ] = [ [1, 1], [1, 0] ]^(n-1) * [ f[1], f[0] ]

// 斐波那契数列前 n 项和
// Sn = F[n+2] - F[2]

================================================== Problem Set ==================================================

// cf 954F
// 题意：
// 有一个 3 x m 的田野，一开始你在 (2, 1) 位置，
// 如果你在 (i, j) 位置，在不出界的前提下，可以走到 (i+1, j | j-1 | j+1)
// 有 n 段障碍 (a, l, r) ，表示第 a 行，第 l 列到第 r 列不能走
// 询问从 (2, 1) 到达 (2, M) 的方案数
// 题解：
// 离散化，矩阵快速幂，注意障碍物边界的处理
int Solve() {
    rep(i, 0, n) {
        scanf("%lld%lld%lld", &a[i].a, &a[i].l, &a[i].r);
        dis.pb(a[i].l-1); dis.pb(a[i].r);   // 注意，这里离散的是 左边界 - 1 ，目的是为了枚举左端点时还没进入障碍区
    }
    dis.pb(1); dis.pb(m);   // 注意边界也要离散
    sort(all(dis));
    dis.erase(unique(all(dis)), dis.end());
    rep(i, 0, n) {      // 注意，这里是用左边界的值去找离散值，这样就会得到比 左边界 - 1 的离散值大的下一个值
        a[i].dl = lower_bound(all(dis), a[i].l) - dis.begin() + 1;
        a[i].dr = lower_bound(all(dis), a[i].r) - dis.begin() + 1;
    }

    rep(i, 0, n) {      // 因为障碍区有可能覆盖，所以用类似扫描线的方法判断是否在障碍区
        cnt[a[i].a-1][a[i].dl]++;       // 表示进入左边界
        cnt[a[i].a-1][a[i].dr+1]--;     // 表示走出右边界
    }
    
    Mat ans(3, 1);
    ans.a[0][0] = ans.a[2][0] = 0;
    ans.a[1][0] = 1;
    rep(i, 0, 3) row[i] = 0;    // row[i] 表示第 i 行当前是否在障碍区，当 row[i] > 0 时表示在障碍区中
    rep(i, 1, sz(dis)) {
        int di = i + 1;     // di 表示离散后的坐标，从 1 开始
        ll len = dis[i] - dis[i-1];
        Mat tmp(3, 3);
        tmp.a[0][0] = tmp.a[0][1] = 1; tmp.a[0][2] = 0;
        tmp.a[1][0] = tmp.a[1][1] = tmp.a[1][2] = 1;
        tmp.a[2][0] = 0; tmp.a[2][1] = tmp.a[2][2] = 1;
        rep(j, 0, 3) {
            row[j] += cnt[j][di];
            if (row[j]) rep(k, 0, 3) tmp.a[j][k] = 0;   // 如果该行有障碍，则转移矩阵该行都为 0
        }
        ans = (tmp ^ len) * ans;    // 注意矩阵的乘法顺序
    }
    return printf("%lld\n", ans.a[1][0]);
}
