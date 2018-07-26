//文件输入输出
#define IO(x) freopen(x".in", "r", stdin); freopen(x".out", "w", stdout);

//浮点型运算
const db eps = 1e-6;
bool eq(db a, db b) { return fabs(a - b) < eps; }
bool ls(db a, db b) { return a + eps < b; }
bool le(db a, db b) { return eq(a, b) || ls(a, b); }

inline int read() {
    int k = 0, f = 1; char c = getchar();
    while (c < '0' || c > '9') c == '-' && (f = -1), c = getchar();
    while ('0' <= c && c <= '9') k = k * 10 + c - '0', c = getchar();
    return k * f;
}
