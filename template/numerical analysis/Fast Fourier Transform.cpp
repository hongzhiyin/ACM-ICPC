/*
【准备】
    1. n 次多项式 a 和 m 次多项式 b ，即 a[i] = C( 第 i 项系数 , 0 );
    2. N 为大于 n+m+1 的 2 的幂

【使用】
    1. 调用 fft.Mul(a, b, n+1, m+1)
    2. 乘积系数保存在 a[i].r ，输出需取整，即 (int)(a[i].r + 0.5)
*/

const db pi = acos(-1);
struct C {
    db r, i;
    C () {} C (db r, db i) : r(r), i(i) {}
    C operator + (const C &b) { return C(r + b.r, i + b.i); }
    C operator - (const C &b) { return C(r - b.r, i - b.i); }
    C operator * (const C &b) { return C(r * b.r - i * b.i, r * b.i + i * b.r); }
} a[N], b[N], w[2][N];

struct FFT{
    int L, pre = -1, na, nb, rev[N];
    void fft(C *a, int f) {
        C x, y;
        rep(i, 0, L) if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int i = 1; i < L; i <<= 1)
            for (int j = 0, t = L/(i<<1); j < L; j += i<<1)
                for (int k = 0, l = 0; k < i; k++, l += t) 
                    x = w[f][l] * a[j+k+i], y = a[j+k], a[j+k] = y+x, a[j+k+i] = y-x;
        if (f) rep(i, 0, L) a[i].r /= L;
    }
    void Pre() {
        int d = __builtin_ctz(L);
        rep(i, 0, L) {
            rev[i] = (rev[i>>1] >> 1) | ((i&1) << (d-1));
            w[1][i] = w[0][i] = C(cos(2*pi*i/L), sin(2*pi*i/L));
            w[1][i].i = -w[1][i].i;
        }
    }
    void Mul(C *a, C *b, int na, int nb) { // [0, na)
        for (L = 1; L < na + nb - 1; L <<= 1);
        rep(i, na, L) a[i] = C(0, 0);
        rep(i, nb, L) b[i] = C(0, 0);
        if (pre != L) Pre(), pre = L;
        fft(a, 0); fft(b, 0);
        rep(i, 0, L) a[i] = a[i] * b[i];
        fft(a, 1);
    }
} fft;
