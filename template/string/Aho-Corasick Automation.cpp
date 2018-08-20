void init() {
    node = -1; obj.newnode();
}

int node;
int trie[N][128], fail[N], isw[N], last[N], que[N];
// N = 单词个数 * 单词长度，第二维视情况而定  last[] 表示上一个是单词结尾的失配位置
struct AhoCorasick {
    int newnode() {
        ++node;
        memset(trie[node], 0, sizeof(trie[node]));
        fail[node] = 0;
        isw[node] = 0;
        return node;
    }
    void insert(char *s, int id) {
        int len = strlen(s), rt = 0;
        rep(i, 0, len) {
            int id = s[i];    // 视情况而定
            if(!trie[rt][id]) trie[rt][id] = newnode();
            rt = trie[rt][id];
        }
        isw[rt] = id;       // 记录单词 id
    }
    void build() {  // 构建失配指针
        que[0] = 0;
        for (int head = 0, tail = 1; head < tail; ++head) {
            int cur = que[head];
            rep(i, 0, 128) {
                int u = trie[cur][i];
                if (u) {
                    int p = fail[cur];
                    while (p && !trie[p][i]) p = fail[p];
                    fail[u] = !cur ? 0 : trie[p][i];
                    last[u] = !cur ? 0 : isw[fail[u]] ? fail[u] : last[fail[u]];
                    que[tail++] = u;
                } else {
                    trie[cur][i] = trie[fail[cur]][i];
                }
            }
        }
    }
    void run(char *s) {     // 匹配单词时，可以把 fail 换成 last ，加快匹配
        int len = strlen(s), rt = 0;
        rep(i, 0, len) {
            int id = s[i];
            while (rt && !trie[rt][id]) rt = fail[rt];
            int tmp = rt = trie[rt][id];
            while (tmp) {
                if (isw[tmp]) cnt[isw[tmp]]++;      // 统计单词出现次数
                tmp = fail[tmp];
            }
        }
    }
};

================================================== Problem Set ==================================================

// poj 2778
// https://blog.csdn.net/morgan_xww/article/details/7834801
// 求不包含所给单词表中的单词且长度为 n 的字符串个数
// AC 自动机 + 矩阵快速幂
// AC 自动机构建状态转移图，通过状态转移构建有向图的邻接矩阵，通过矩阵快速幂计算两点之间长度为 n 的路径数目

int node;
int trie[N][4], fail[N], isw[N], que[N];
struct AhoCorasick {
    int newnode() {
        ++node;
        memset(trie[node], 0, sizeof(trie[node]));
        fail[node] = 0;
        isw[node] = 0;
        return node;
    }
    void insert(char *s) {
        int len = strlen(s), rt = 0;
        rep(i, 0, len) {
            int id = f[s[i]];    // 依题意，只有 4 种字符，映射到 0 ~ 3
            if(!trie[rt][id]) trie[rt][id] = newnode();
            rt = trie[rt][id];
        }
        isw[rt] = 1;       // 标记单词结尾，表明不可转移到此状态
    }
    void build() {  // 构建失配指针
        que[0] = 0;
        for (int head = 0, tail = 1; head < tail; ++head) {
            int cur = que[head];
            isw[cur] |= isw[fail[cur]];
            // 失配指针如果被标记，说明从根节点到当前节点形成的字符串包含了一个不可出现的字符串作为后缀，因此也不可转移到此状态
            rep(i, 0, 4) {
                int u = trie[cur][i];
                if (u) {
                    int p = fail[cur];
                    while (p && !trie[p][i]) p = fail[p];
                    fail[u] = !cur ? 0 : trie[p][i];
                    que[tail++] = u;
                } else {
                    trie[cur][i] = trie[fail[cur]][i];
                }
            }
        }
    }
    void run() {
        rep(i, 0, node+1) rep(j, 0, 4)      // 遍历节点编号，即遍历所有状态
            if (!isw[i] && !isw[trie[i][j]])    // 如果状态转移的两端都合法，则表明两状态之间有一条长度为 1 的有向边
                mat[i][trie[i][j]]++;           // 注意，这里并不需要子节点一定存在，对于不存在的节点，都返回根节点状态
    }
};
AhoCorasick obj;

struct Mat {
    vector< vector<ll> > a;
    Mat() {}
    Mat(int n, int m) { a.resize(n, vector<ll>(m)); }
    Mat operator *(const Mat &b) const {
        int n = sz(a), m = sz(b.a[0]), nm = sz(b.a); Mat r(n, m);
        rep(i, 0, n) rep(j, 0, m) {
            rep(k, 0, nm) r.a[i][j] += a[i][k] * b.a[k][j];    // 取模运算十分耗时，尽可能最后再取模
            r.a[i][j] %= MOD;
        }
        return r;
    }
    Mat operator ^(ll b) {
        int n = sz(a); Mat r(n, n), t = *this;
        rep(i, 0, sz(r.a)) r.a[i][i] = 1;
        for (; b; b >>= 1) {
            if (b & 1) r = r * t;
            t = t * t;
        }
        return r;
    }
};

void Init() {
    f['A'] = 0, f['T'] = 1, f['C'] = 2, f['G'] = 3;
    memset(mat, 0, sizeof(mat));
    node = -1; obj.newnode();
    
    while (n--) {
        scanf("%s", str);
        obj.insert(str);        // 构建字典树，标记不可转移状态
    }
    obj.build();        // 构建失配指针，标记不可转移状态
    obj.run();          // 构建邻接矩阵， mat[i][j] 表示第 i 号状态到第 j 号状态有 mat[i][j] 条长度为 1 的路
}
int Solve() {
    int n = node + 1;
    a = Mat(n, n);
    rep(i, 0, n) rep(j, 0, n) a.a[i][j] = mat[i][j];
    a = a ^ m;          // 长度为 m 的路径矩阵
    int ans = 0;
    rep(i, 0, n) ans += a.a[0][i];     // 从根节点出发到各个状态（包括自己）的长度为 m 的路径总数
    return !printf("%d\n", ans % MOD);
}

----------------------------------------------------------------------------------------------------

// hdu 2243
// https://www.cnblogs.com/kuangbin/p/3159520.html
// 题意：给定一些模式串，求出长度不超过 m 的，包含模式串的字符串个数。
// 本题分两步解决：
// 1. 求长度小于等于 m 的不包含模式串的字符串个数
// 2. 长度小于等于 m 的包含模式串的字符串个数 = 长度小于等于 m 的字符串总数 - 长度小于等于 m 的不包含模式串的字符串个数

// 1. 求长度小于等于 m 的不包含模式串的字符串个数
// 将上题中，表示路径长度为 1 的矩阵，再加一维，并将 n+1 列置 1
// 几何意义：
// 在原本 n 个点的基础上，多加一个点，并添加 n 条从 n 个点连向该点的有向边，并且第 n + 1 个点有自环
// 那么，最终只要求得从第 1 个点走到第 n + 1 个点的，长度为 m + 1 的路径数即可
// 因为，第 1 个点可以先走 k 步到达第 j 个点，然后走 1 步到达第 n + 1 个点，然后剩余步数在第 n + 1 个点空转
// 那么，由于走到第 n + 1 个点有一条长度为 1 的路是一定要走的，所以求得是长度为 m + 1 的路径数
// 第 1 个点有可能第 1 步直接走到第 n + 1 个点，则路径数中包含有从第 1 个点出发走 0 步的情况，本题中需要扣除
// 那么，只需要对上题的长度为 1 的路径矩阵，求 m + 1 次幂，则答案即为 ans = mat[1][n+1] - 1 （代码里点从 0 开始）

// 接着求长度小于等于 m 的字符串总数
// 显然，总数为： 26^1 + 26^2 + ... + 26^m
// 但由于题目要求模数为 2^64 ，不是质数，因此无法用等比数列求和公式加乘法逆元求得
// 于是可以通过矩阵快速幂来求
// f[n] 表示 26^1 + 26^2 + ... + 26^n
// 那么， f[n] = 26 * f[n-1] + 26
// 则： [f[n], 26] = [[26, 1], [0, 1]]^n * [f[0]=0, 26]       矩阵构造形式可以很多样
// 从而求出 f[m] 即为 长度小于等于 m 的字符串总数

// 最终答案两者相减即可

AhoCorasick obj;    // 结构基本同上，注意字符编号和遍历范围
Mat a, b;       // 对 2^64 取模即为 unsigned long long 自然溢出

void Init() {
    while (n--) obj.insert(str);
    obj.build();
    obj.run();
}
int Solve() {
    int n = node + 1;
    a = Mat(n+1, n+1);
    rep(i, 0, n) rep(j, 0, n) a.a[i][j] = mat[i][j];
    rep(i, 0, n+1) a.a[i][n] = 1;       // 添加第 n 个点 （点从 0 开始）
    a = a ^ (m + 1);                // 长度为 m + 1 的路径矩阵，依题意， m 上限会达到 2^31-1 ，再 +1 会溢出，注意读入或强制转换
    ull ans = a.a[0][n]; --ans;     // 从第 0 个点走到第 n 个点的长度为 m + 1 的路径数，再减去从第 0 个点出发走 0 步的路径数 1 条
    b = Mat(2, 2);
    b.a[0][0] = 26; b.a[0][1] = 1; b.a[1][0] = 0; b.a[1][1] = 1;
    b = b ^ m;                      // 矩阵快速幂求等比数列之和
    ull tmp = b.a[0][1] * 26;
    return !printf("%llu\n", tmp - ans);    // unsigned long long 要用 %llu 输出，如果用 %lld 会 WA ，同理也有 %I64u
}

----------------------------------------------------------------------------------------------------

// hdu 4511
// https://www.cnblogs.com/kuangbin/p/3577678.html
// 给定若干路径不允许出现，问从 1 到 n 的最短路
// 通过 AC 自动机得到状态转移。
// 之后 dp[i][j] 表示走到 i 点，状态在 j 的距离。

void run(int n) {
    dp[1][trie[0][1]] = 0;          // 从 1 号节点出发
    int state = node + 1;
    rep(i, 1, n+1) rep(j, 0, state) if (dp[i][j] < LINF) {     // 如果可以走到 i 号节点，且这个时候属于状态 j
        rep(k, i+1, n+1) {    // 遍历当前节点可以走到的下一个节点，且节点编号大于 i
            if (isw[trie[j][k]]) continue;      // 非法状态
            int s = trie[j][k];     // 下一个合法状态编号
            dp[k][s] = min(dp[k][s], dp[i][j] + dist(i, k));
        }
    }
}

void Init() {
    rep(i, 0, 57) rep(j, 0, N) dp[i][j] = LINF;
    
    while (m--) obj.insert(str, k);
    obj.build(n);
    obj.run(n);
}
int Solve() {
    db ans = LINF;
    rep(i, 0, node+1) ans = min(ans, dp[n][i]);     // 遍历处在第 n 个点的所有状态
    if (ans == LINF) return !puts("Can not be reached!");
    return !printf("%.2f\n", ans);
}
