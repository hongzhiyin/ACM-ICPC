/*
【使用方法】
1. 多项式系数按 a[i] 表示 x ^ i 的系数存在两个 vector 里
2. 调用 vi Mul(vi &x, vi &y)
3. 返回值即为乘积结果多项式的各项系数，规则与 a[i] 同理
*/

const db PI = acos(-1);
struct C {
    double r, i;
    C () { r = i = 0; }
    C (db r, db i) : r(r), i(i) {}
    C operator + (const C &p) const { return C(r + p.r, i + p.i); }
    C operator - (const C &p) const { return C(r - p.r, i - p.i); }
    C operator * (const C &p) const { return C(r*p.r - i*p.i, r*p.i + i*p.r); }
};
void fft(vector<C> &x, int rev) {
    int n = sz(x), i, j, k, t;
    for (i = 1; i < n; ++i) {
        for (j = 0, k = n >> 1, t = i; k; k >>= 1, t >>= 1)
            j = (j << 1) | (t & 1);
        if (i < j) swap(x[i], x[j]);
    }
    for (int s = 2, ds = 1; s <= n; ds = s, s <<= 1) {
        C w = C(1, 0), t;
        C wn = C(cos(2 * rev * PI / s), sin(2 * rev * PI / s));
        for (k = 0; k < ds; ++k, w = w * wn)
            for (i = k; i < n; i += s) {
                t = w * x[i + ds];
                x[i + ds] = x[i] - t;
                x[i] = x[i] + t;
            }
    }
    if (rev == -1) for (i = 0; i < n; ++i) x[i].r /= n;
}
vi Mul(vi &x, vi &y) {
    int L = 1;
    while (L < sz(x) + sz(y)) L <<= 1;
    vector<C> A(L), B(L);
    rep(i, 0, sz(x)) A[i] = C(x[i], 0);
    rep(i, 0, sz(y)) B[i] = C(y[i], 0);
    fft(A, 1), fft(B, 1);
    rep(i, 0, L) A[i] = A[i] * B[i];
    fft(A, -1);
    vi ret(L);
    rep(i, 0, L) ret[i] = (int)(A[i].r + 0.5);
    return ret;
}
