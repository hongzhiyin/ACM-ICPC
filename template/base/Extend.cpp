//文件输入输出
#define IO(x) freopen(x".in", "r", stdin); freopen(x".out", "w", stdout);

//浮点型运算
const db eps = 1e-6;
bool eq(const db &a, const db &b) { return fabs(a - b) < eps; }
bool ls(const db &a, const db &b) { return a + eps < b; }
bool le(const db &a, const db &b) { return eq(a, b) || ls(a, b); }
