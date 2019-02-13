/*
【复杂度】
预处理 : O( log_{mod}^{n} ) // 底数 : p ; 真数 : n
计算   : O( p )

【注意事项】
1. 记得先用 lucas_ini() 初始化
2. 模数 p 必须是质数
*/

inline int add(ll a, int b) { if ((a += b) >= p) a -= p; return a; }
inline int mul(ll a, int b) { if ((a *= b) >= p) a %= p; return a; }

int p, jc[N], ijc[N], inv[N];  // jc : 阶乘 ; inv : 逆元 ; ijc : 阶乘的逆元
void lucas_ini() {
    jc[0] = 1; rep(i, 1, p) jc[i] = mul(jc[i-1], i);
    inv[1] = 1; rep(i, 2, p) inv[i] = mul(inv[p%i], p - p / i);
    ijc[0] = 1; rep(i, 1, p) ijc[i] = mul(ijc[i-1], inv[i]);
}
int C(int a, int b) { return a < b ? 0 : mul(jc[a], mul(ijc[b], ijc[a-b])); }
int lucas(ll a, ll b) { return !b ? 1 : mul(C(a % p, b % p), lucas(a / p, b / p)); }
