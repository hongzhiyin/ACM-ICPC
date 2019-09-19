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
    void Mul(C *a, C *b, int na, int nb) {
        for (L = 1; L < na + nb - 1; L <<= 1);
        rep(i, na, L) a[i] = C(0, 0);
        rep(i, nb, L) b[i] = C(0, 0);
        if (pre != L) Pre(), pre = L;
        fft(a, 0); fft(b, 0);
        rep(i, 0, L) a[i] = a[i] * b[i];
        fft(a, 1);
    }
} fft;

---

/*  更快的 FFT
【准备】
    1. n 次多项式 a 和 m 次多项式 b ，即 a[i] = 第 i 项系数 ;
    2. N 为大于 n+m+1 的 2 的幂

【使用】
    1. 调用 fft.Mul(a, b, n+1, m+1)
    2. 乘积系数保存在 a[i]
*/

const db pi = acos(-1);
struct C{
    db r, i;
    C () {} C (db r, db i) : r(r), i(i) {}
    C operator + (const C &b) { return C(r + b.r, i + b.i); }
    C operator - (const C &b) { return C(r - b.r, i - b.i); }
    C operator * (const C &b) { return C(r * b.r - i * b.i, i * b.r + r * b.i); }
    C operator * (const db k) { return C(k * r, k * i); }
    C operator ! () { return C(r, -i); }
} x[N|1], y[N|1], z[N|1], w[N|1];

struct FFT {
    int L;
    void fft(C *x, int f) {
        for (int i = 0, j = 0; i < L; ++i) {
            if (i > j) swap(x[i], x[j]);
            for (int l = L>>1; (j^=l) < l; l >>= 1);
        }
        w[0] = C(1, 0);
        for (int i = 2; i <= L; i <<= 1) {
            C g = C(cos(2*pi/i), (f ? -1 : 1) * sin(2*pi/i));
            for (int j = i>>1; j >= 0; j -= 2) w[j] = w[j>>1];
            for (int j = 1; j < i>>1; j+=2) w[j] = w[j-1] * g;
            for (int j = 0; j < L; j += i) {
                C *a = x + j, *b = a + (i>>1);
                for (int l = 0; l < i>>1; ++l){
                    C o = b[l] * w[l];
                    b[l] = a[l] - o;
                    a[l] = a[l] + o;
                }
            }
        }
        if (f) rep(i, 0, L) x[i] = C(x[i].r / L, x[i].i / L);
    }
    void Mul(int *a, int *b, int na, int nb) { 
        for (L = 1; L <= na + nb >> 1; L <<= 1);
        rep(i, 0, L) x[i] = y[i] = C(0, 0);
        rep(i, 0, na+1) (i & 1 ? x[i>>1].i : x[i>>1].r) = a[i];
        rep(i, 0, nb+1) (i & 1 ? y[i>>1].i : y[i>>1].r) = b[i];
        fft(x, 0); fft(y, 0);
        rep(i, 0, L) {
            int j = L - 1 & L - i;
            C tmp = (i & L>>1) ? C(1, 0) - w[i^L>>1] : w[i] + C(1, 0); 
            z[i] = (x[i] * y[i] * 4 - (x[i] - !x[j]) * (y[i] - !y[j]) * tmp) * 0.25;
        }
        fft(z, 1);
        rep(i, 0, na+nb+1) a[i] = i & 1 ? z[i>>1].i + 0.1 : z[i>>1].r + 0.1;
    }
} fft;

---

/*  可取模的 FFT
【准备】
    1. n 次多项式 a 和 m 次多项式 b ，即 a[i] = 第 i 项系数 ;
    2. N 为大于 n+m+1 的 2 的幂

【使用】
    1. 调用 fft.Mul(a, b, n+1, m+1)
    2. 乘积系数保存在 a[i]
*/

const db pi = acos(-1);
struct C {
    db r, i;
    C () {} C (db r, db i) : r(r), i(i) {}
    C operator + (const C &b) { return C(r + b.r, i + b.i); }
    C operator - (const C &b) { return C(r - b.r, i - b.i); }
    C operator * (const C &b) { return C(r * b.r - i * b.i, i * b.r + r * b.i); }
    C operator ! () { return C(r, -i); }
} w[N], A[N], B[N], D[N], E[N];

struct FFTMOD {
    int L, bit, mask;
    void fft(C *p, int n) {
        for (int i = 1, j = 0; i < n - 1; ++i) {
            for (int s = n; j ^= (s >>= 1), ~j & s;);
            if (i < j) swap(p[i], p[j]);
        }
        for (int d = 0; (1 << d) < n; ++d) {
            int m = 1 << d, m2 = m * 2, rm = n >> (d + 1);
            for (int i = 0; i < n; i += m2) rep(j, 0, m) {
                C &p1 = p[i + j + m], &p2 = p[i + j];
                C t = w[rm * j] * p1;
                p1 = p2 - t, p2 = p2 + t;
            }
        }
    }
    void Mul(int *a, int *b, int na, int nb) {
        for (L = 1; L < na + nb - 1; L <<= 1);
        rep(i, 0, na) a[i] = (a[i] % P + P) % P; rep(i, na, L) a[i] = 0;
        rep(i, 0, nb) b[i] = (b[i] % P + P) % P; rep(i, nb, L) b[i] = 0;
        bit = 15; mask = (1 << bit) - 1;
        rep(i, 0, L) w[i] = C(cos(2 * i * pi / L), sin(2 * i * pi / L));
        rep(i, 0, L) {
            A[i] = C(a[i] >> bit, a[i] & mask);
            B[i] = C(b[i] >> bit, b[i] & mask);
        }
        mul(a);
    }
    void mul(int *a) {
        fft(A, L), fft(B, L);
        rep(i, 0, L) {
            int j = (L - i) % L;
            C da = (A[i] - !A[j]) * C(0, -0.5);
            C db = (A[i] + !A[j]) * C(0.5, 0);
            C dc = (B[i] - !B[j]) * C(0, -0.5);
            C dd = (B[i] + !B[j]) * C(0.5, 0);
            D[j] = da * dd + da * dc * C(0, 1);
            E[j] = db * dd + db * dc * C(0, 1);
        }
        fft(D, L), fft(E, L);
        rep(i, 0, L) {
            ll da = (ll)(D[i].i / L + 0.5) % P;
            ll db = (ll)(D[i].r / L + 0.5) % P;
            ll dc = (ll)(E[i].i / L + 0.5) % P;
            ll dd = (ll)(E[i].r / L + 0.5) % P;
            a[i] = ((dd << (bit * 2)) + ((db + dc) << bit) + da) % P;
        }
    }
} fft;
