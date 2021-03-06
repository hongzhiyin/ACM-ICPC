/*
时间复杂度 : O(n)
准备 :
    base : 基数 ; mod : 模数
输入 :
    s : 待求哈希值的字符串
输出 :
    pair<ull, ull> : 双哈希值
注意 :
*/
typedef unsigned long long ull;
ull ha[2], base[] = {123, 131}, mod = 19260817;
pair<ull, ull> Hash(char *s) {
    int len = strlen(s);
    ha[0] = ha[1] = 0;
    rep(i, 1, len+1) ha[0] = ha[0] * base[0] + s[i];
    rep(i, 1, len+1) ha[1] = (ha[1] * base[1] + s[i]) % mod;
    return mp(ha[0], ha[1]);
}

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

================================================== Problem Set ==================================================

// poj 3274
// 闭散列碰撞检测，也可用 map 实现，但效率可能会低
while (M[key] != -1) {
    // 判断是发生碰撞还是实际映射对象相同
    if (check()) { ...; break; }    // 实际映射对象相同
    else key++;                     // 发生碰撞
}
if (M[key] == -1) M[key] = val;       // 没有发生碰撞
