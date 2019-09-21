/*
< 准备 >
    1. n 次多项式 a 和 m 次多项式 b ，即 a[i] = 第 i 项系数 ;
    2. N 为大于 n+m+1 的 2 的幂

< 使用 >
    1. 调用 ntt.Mul(a, b, n+1, m+1)
    2. 乘积系数保存在 a[i]

< 注意 >
    1. 传入的 a 和 b 数组都会改变， a 为乘积系数， b 未做逆变换，
    .. 可用 memcpy(dest, src, sizeof(type) * len) 复制临时数组。
    2. 求多项式 a 的平方不可以直接用 fft.Mul(a, a, n+1, n+1) ，
    .. 要删除或修改 Mul() 里有关 b 的部分。
    3. NTT 的模数通常为 : 998244353, 1004535809, 469762049, 即 P = k * 2 ^ x + 1
*/

struct NTT {
    static const int G = 3, P = 998244353;
    int L, pre = -1, w[2][N], rev[N];
    void fft(int *a, int f) {
        rep(i, 0, L) if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int i = 1; i < L; i <<= 1)
            for (int j = 0, t = L / (i<<1); j < L; j += i<<1)
                for (int k = 0, l = 0, x, y; k < i; ++k, l += t)
                    x = (ll)w[f][l] * a[j+k+i] % P, y = a[j+k], a[j+k] = (y+x) % P, a[j+k+i] = (y-x+P) % P;
        if (f) for (int i = 0, x = qpow(L, P-2); i < L; ++i) a[i] = (ll)a[i] * x % P;
    }
    void Pre() {
        int d = __builtin_ctz(L);
        w[0][0] = w[1][0] = 1;
        for (int i = 1, x = qpow(G, (P-1) / L), y = qpow(x, P-2); i < L; i++) {
            rev[i] = (rev[i>>1] >> 1) | ((i&1) << (d-1));
            w[0][i] = (ll)x * w[0][i-1] % P, w[1][i] = (ll)y * w[1][i-1] % P;
        }
    }
    void Mul(int *a, int *b, int na, int nb) {
        for (L = 1; L < na + nb - 1; L <<= 1);
        rep(i, na, L) a[i] = 0;
        rep(i, nb, L) b[i] = 0;
        if (pre != L) Pre(), pre = L;
        fft(a, 0), fft(b, 0);
        rep(i, 0, L) a[i] = (ll)a[i] * b[i] % P;
        fft(a, 1);
    }
} ntt;
