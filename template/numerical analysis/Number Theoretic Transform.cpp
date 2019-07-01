/*
【使用】
  1. 声明一个 C ，无须初始化，调用 mul(A, B, &C);
  2. 不传 &C 时，调用 mul(A, B); 等价于 A *= B;

【注意】
  1. mxlen : 计算过程中多项式的最大长度
  2. N 取大于 mxlen 的 2 的幂次
  3. 模数通常为 : 998244353, 1004535809, 469762049, 即 k * 2 ^ x + 1
*/

ll qpow(ll a, ll b) { ll r = 1; for (a %= MOD; b; a = a * a % MOD, b >>= 1) if (b & 1) r = r * a % MOD; return r; }

#define T int
#define vT vector<T>
struct NTT {
    vT aa, bb;
    int mxlen = 1000000;
    T w[2][N*2+5], rev[N*2+5], tmp;
    void ntt(vT &A, int m, int op) {
        int n = 1<<m; T w0 = qpow(3, (MOD-1)/n);
        w[0][0] = w[1][0] = 1;
        rep(i, 1, n) w[0][i] = w[1][n-i] = (ll)w[0][i-1] * w0 % MOD;
        rep(i, 1, n) rev[i] = (rev[i>>1] >> 1) | (i & 1) << (m-1);
        rep(i, 0, n) if (i < rev[i]) swap(A[i], A[rev[i]]);
        for (int i = 1; i < n; i <<= 1)
            for (int j = 0, t = n/(i<<1); j < n; j += i<<1)
                for (int k = j, l = 0; k < j+i; k++, l += t) {
                    T x = A[k], y = (ll)w[op][l] * A[k+i] % MOD;
                    A[k] = (x+y) % MOD, A[k+i] = (x-y+MOD) % MOD;
                }
        if (op) {
            tmp = qpow(n, MOD-2);
            rep(i,0,n) A[i] = (ll)A[i] * tmp % MOD;
        }
    }
    vT& mul(vT &A, vT &B, vT *C = NULL, int op = 0) {
        int lena = sz(A), lenb = sz(B), len = 1, L = 0;
        aa = A, bb = B;
        while (len < 2 * max(lena, lenb)) len <<= 1, ++L;
        aa.resize(len), bb.resize(len);
        if (op) reverse(all(bb));
        ntt(aa, L, 0), ntt(bb, L, 0);
        if (!C) C = &A;
        (*C).resize(len);
        rep(i, 0, len) (*C)[i] = (ll)aa[i] * bb[i] % MOD;
        ntt(*C, L, 1); 
        if (op) reverse(all(*C));
        if (len-1 > mxlen) (*C).resize(mxlen+1); 
        return *C;
    }
} obj;
