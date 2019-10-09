inline int add(int a, int b) { return (a += b) >= MOD ? a - MOD : a; }
inline int mul(int a, int b) { return 1ll * a * b % MOD; }
struct Mat {
    int n, a[M][M];
    Mat () {}
    Mat (int _n) { n = _n; rep(i, 0, n) rep(j, 0, n) a[i][j] = 0; }
    Mat operator * (Mat b) {
        Mat r(n);
        /*
        rep(i, 0, n) rep(j, 0, n) rep(k, 0, n)
            r.a[i][j] = add(r.a[i][j], mul(a[i][k], b.a[k][j]));
        return r;
        */
        //  当 r.a[i][j] 的最大值不会溢出时
        rep(i, 0, n) rep(j, 0, n) {
            ll tmp = 0;
            rep(k, 0, n) tmp += 1ll * a[i][k] * b.a[k][j];
            r.a[i][j] = tmp % MOD;
        }
        return r;
    }
    Mat operator + (Mat b) {
        Mat r(n);
        rep(i, 0, n) rep(j, 0, n) r.a[i][j] = add(a[i][j], b.a[i][j]);
        return r;
    }
    Mat operator ^ (ll b) {
        Mat r(n), t = *this;
        rep(i, 0, n) r.a[i][i] = 1;
        for (; b; b >>= 1) {
            if (b & 1) r = r * t;
            t = t * t;
        }
        return r;
    }
    void out() {
        rep(i, 0, n) rep(j, 0, n) printf("%d%c", a[i][j], " \n"[i==n-1]);
    }
};

// vector 版本
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
