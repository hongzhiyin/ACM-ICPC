// 读取所需字符   // islower(), isupper(), isalpha(), isdigit(), isalnum()
inline void readchar(char &c) { do c = getchar(); while (!isdigit(c)); }

// 读取整数
inline void readint(int &x) {
    int f = 1, res = 0; char c = getchar();
    while (!isdigit(c)) c == '-' && (f = -1), c = getchar();
    while (isdigit(c)) res = res * 10 + c - '0', c = getchar();
    x = res * f;
}

// 取模加，取模乘      // 如果保证不会出现负数的情况，就可以省去两次 MOD 操作
inline ll add(ll a, ll b) { return ((a + b) % MOD + MOD) % MOD; }
inline ll mul(ll a, ll b) { return (a * b % MOD + MOD) % MOD; }

// 快速乘，快速幂
ll mulmod(ll a, ll b) { ll res = 0; for(a %= MOD; b; b >>= 1) { if (b & 1) res = add(res, a); a = add(a, a); } return res; }
ll powmod(ll a, ll b) { ll res = 1; for(a %= MOD; b; b >>= 1) { if (b & 1) res = mul(res, a); a = mul(a, a); } return res; }

// gcd
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

// 文件输入输出
#define IO(x) freopen(x".in", "r", stdin); freopen(x".out", "w", stdout);

// 浮点型运算
const db eps = 1e-7;
inline bool eq(db a, db b) { return fabs(a - b) < eps; }
inline bool ls(db a, db b) { return a + eps < b; }
inline bool le(db a, db b) { return eq(a, b) || ls(a, b); }


