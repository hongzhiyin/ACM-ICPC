typedef unsigned long long ull;
char s[N];
ull ha[N], p[N];      // ha[i] 表示从 1 到 i 位的字符串映射为数字， p[i] 表示 base 的 i 次方
struct Hash {
    ull base;
    void init(char *s, int len) {       // s[] 从 1 开始
        base = 2333333333333;
        p[0] = 1; ha[0] = 0;
        rep(i, 1, N) p[i] = p[i-1] * base;
        rep(i, 1, len+1) ha[i] = ha[i-1] * base + s[i];
    }
    ull query(int l, int r) { return ha[r] - ha[l-1] * p[r-l+1]; }
};
