// 读取所需字符   // islower(), isupper(), isalpha(), isdigit(), isalnum()
inline void readchar(char &c) { do c = getchar(); while (!isdigit(c)); }

// 输入输出
template <class T>
inline void read(T &x) {
    int f = 1, r = 0; char c = getchar();
    while (c < '0' || '9' < c) c == '-' && (f = -1), c = getchar();
    while ('0' <= c && c <= '9') r = r * 10 + c - '0', c = getchar();
    x = r * f;
}

template <class T>
inline void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    char s[50]; int i = 0;
    while (x || !i) s[i++] = x % 10 + '0', x /= 10;
    while (i--) putchar(s[i]);
}

// 取模加，取模乘
inline int add(int a, int b) { return (a += b) >= MOD ? a - MOD : a; }
inline int mul(int a, int b) { return 1ll * a * b % MOD; }

// 快速乘，快速幂
int qmul(ll a, ll b) {
    int r = 0;
    for (a %= MOD; b; a = (a + a) % MOD, b >>= 1)
        if (b & 1) r = (r + a) % MOD;
    return r;
}
int qpow(ll a, ll b) {
    int r = 1;
    for (a %= MOD; b; a = a * a % MOD, b >>= 1)
        if (b & 1) r = r * a % MOD;
    return r;
}

// 字符串映射
int cnt = 0;
map <string, int> id;
int ID(string s) { return id.count(s) ? id[s] : id[s] = cnt++; }

// gcd
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
db fgcd(db a, db b) { return b > eps ? fgcd(b, fmod(a, b)) : a; }  // eps = 1e-2

// 文件输入输出
#define IO(x) freopen(x".in", "r", stdin); freopen(x".out", "w", stdout);

// 浮点型运算
const db eps = 1e-7;
inline bool eq(db a, db b) { return fabs(a - b) < eps; }
inline bool ls(db a, db b) { return a + eps < b; }
inline bool le(db a, db b) { return eq(a, b) || ls(a, b); }

// 大随机数
ll myrand() { return (ll)rand() << 32 ^ (ll)rand() << 16 ^ rand(); }

// GCC 内建函数
int __builtin_ffs (unsigned int x)      // 返回右起第一个 1 的位置，从 1 开始，如果 x = 0 ，返回 0 。
int __builtin_clz (unsigned int x)      // 返回前导 0 的个数，如果 x = 0 ，结果未定义。
int __builtin_ctz (unsigned int x)      // 返回末尾 0 的个数，如果 x = 0 ，结果未定义。
int __builtin_popcount (unsigned int x) // 返回 1 的个数。
int __builtin_parity (unsigned int x)   // 返回 1 的个数的奇偶性，奇为 1 ，偶为 0 。
// x 若为 unsigned long long 类型，只需要在函数名后加 ll 即可，如 int __builtin_ffsll (unsigned long long x)

// 访问数组负数下标
int tmp[N<<1], *a = tmp + N;  // 使用 a[x] 和 a[-x]
