//文件输入输出
#define IO(x) freopen(x".in", "r", stdin); freopen(x".out", "w", stdout);

//浮点型运算
const db eps = 1e-6;
bool eq(db a, db b) { return fabs(a - b) < eps; }
bool ls(db a, db b) { return a + eps < b; }
bool le(db a, db b) { return eq(a, b) || ls(a, b); }

inline void read(int &x) {
    int f = 1, res = 0; char c = getchar();
    while (!isdigit(c)) c == '-' && (f = -1), c = getchar();
    while (isdigit(c)) res = res * 10 + c - '0', c = getchar();
    x = res * f;
}
