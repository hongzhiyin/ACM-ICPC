/*
【函数功能】
void Init(int n)     : 初始化大小为 n 的树状数组
T Sum(int x)         : 返回前 x 个元素之和
T Qry(int l, int r)  : 返回区间 [l, r] 内元素之和
void Add(int x, T d) : 第 x 个元素加上 d

【注意事项】
1. 下标从 1 开始
2. 如果下标过大，需要离散化
*/

ll t[N]; // map <int, int> t;

ll Sum(int x) { ll ret = 0; for (; x > 0; x -= x&-x) ret += t[x]; return ret; }

void Add(int x, ll d) { for (; x <= ?; x += x&-x) t[x] += d; }

ll Qry(int l, int r) { return Sum(r) - Sum(l-1); }
