/*
< 准备 >
    1. a[] 为待转换的全排列，从 1 开始
    2. n 表示全排列长度
    3. x 表示待转换的全排列的排名
    
< 使用 >
    1. 调用 Cantor_Expansion(a, n) ，得
    .. 返回值： 全排列 a 在所有相同长度全排列中的字典序排名，从 1 开始
    2. 调用 Reverse_Cantor_Expansion(x, n, b) ，得
    .. x 对应的全排列保存在数组 b 中 
*/

#define ls rt << 1
#define rs rt << 1 | 1
#define lson l, m, ls
#define rson m + 1, r, rs
int t[N<<2];
struct Seg {
    void build(int l, int r, int rt) {
        if (l == r) { t[rt] = 0; return ; }
        int m = (l + r) >> 1;
        build(lson); build(rson);
        t[rt] = t[ls] + t[rs];
    }
    int qry(int y, int l, int r, int rt) {
        if (l == r) return l;
        int m = (l + r) >> 1, len = m - l + 1;
        if (len - t[ls] >= y) return qry(y, lson);
        return qry(y - (len - t[ls]), rson);
    }
    void upd(int p, int l, int r, int rt) {
        if (l == r) { t[rt]++; return ; }
        int m = (l + r) >> 1;
        if (p <= m) upd(p, lson); else upd(p, rson);
        t[rt] = t[ls] + t[rs];
    }
    int sum(int p, int l, int r, int rt) {
        if (l == r) return t[rt];
        int m = (l + r) >> 1;
        if (p <= m) return sum(p, lson);
        return t[ls] + sum(p, rson);
    }
} seg;

void Reverse_Cantor_Expansion(int x, int n, int b[]) {
    x--;
    seg.build(1, n, 1);
    int y, jc = 1; rep(i, 1, n+1) jc *= i;
    rep(i, 1, n+1) {
        jc /= n - i + 1;
        y = x / jc; x %= jc;
        b[i] = seg.qry(y + 1, 1, n, 1);
        seg.upd(b[i], 1, n, 1);
    }
}

int Cantor_Expansion(int a[], int n) {
    seg.build(1, n, 1);
    int res = 1, jc = 1;
    per(i, 1, n+1) {
        res = (res + 1ll * jc * seg.sum(a[i], 1, n, 1)) % MOD;
        jc = 1ll * jc * (n - i + 1) % MOD;
        seg.upd(a[i], 1, n, 1);
    }
    return res;
}
