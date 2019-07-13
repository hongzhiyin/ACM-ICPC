# Problem Set / 例题集

[TOC]

<div STYLE="page-break-after: always;"></div>
## Data structures / 数据结构

### 线段树

**例题 : 1083C** 

**题意**

一颗 n 个节点的树，每个节点有一个权值，这些权值构成 0 到 n-1 的排列， q 次询问，每次可能交换两个节点的权值，也可能询问，当前这棵树中，存在某条路径，使得 mex( 路径上的权值 ) 最大。 mex 即集合中未出现的最小非负整数。

**题解**

权值线段树维护，线段树每个节点表示一段权值区间，节点的值表示包含这段权值区间内所有元素的最短路径的两个端点。

询问时，用二分的方式尽可能合并区间，最终区间右端点即为答案。

合并区间时，用 LCA 和路径长度判断两段区间对应的两条路径是否可以合并成一条路径。

**代码**

```c++
/* <<head>> */
const int N = (int)2e5+7;

// ------- 变量 ------- //

int n, p[N], fa[N];
vi e[N];

// ------- 函数 ------- //

int sz[N], son[N], dep[N];
inline void dfs_1(int u) {
    sz[u] = 1;
    son[u] = 0;  // son[u] 表示 u 的重儿子
    for (auto v : e[u]) {
        dep[v] = dep[u] + 1;
        dfs_1(v);
        if (sz[son[u]] < sz[v]) son[u] = v;
        sz[u] += sz[v];
    }
}

int top[N];
inline void dfs_2(int u, int peak) {
    top[u] = peak;  // top[u] 表示 u 所属的重链中，深度最小的节点
    if (son[u]) dfs_2(son[u], peak);
    for (auto v : e[u]) if (v != son[u]) dfs_2(v, v);
}

inline int LCA(int u, int v) {  // 在若干条重链上转移求 LCA
    for (; top[u] != top[v]; u = fa[top[u]])  // 直到两点属于同一条链
        if (dep[top[u]] < dep[top[v]]) swap(u, v);  // 选择深度大的节点上跳
    return dep[u] > dep[v] ? v : u;
}

inline int dis(int u, int v) {
    int lca = LCA(u, v);
    return dep[u] - dep[lca] + dep[v] - dep[lca];
}

#define ls rt << 1
#define rs rt << 1 | 1
#define lson l, m, ls
#define rson m + 1, r, rs
pii t[N<<2];
inline pii merge(int u, int v, int w) {  // 利用端点距离判断三个端点是否在同一路径上
    if (!u || !v || !w) return mp(0, 0);
    int uv = dis(u, v), uw = dis(u, w), vw = dis(v, w);
    if (uv == uw + vw) return mp(u, v);
    if (uw == uv + vw) return mp(u, w);
    if (vw == uv + uw) return mp(v, w);
    return mp(0, 0);
}

inline pii op(pii a, pii b) {  // 合并路径 a 和路径 b
    if (a.fi == -1) return b;  // 询问时使用 mp(-1, -1) 表示初始路径
    a = merge(a.fi, a.se, b.fi);  // 轮流考察 b 的两端点是否和 a 在同一路径上
    a = merge(a.fi, a.se, b.se);
    return a;
}

inline void upd(int pos, int val, int l, int r, int rt) {
    if (l == r) { t[rt] = mp(val, val); return ; }  // 单个权值所属路径即为本节点
    int m = l + r >> 1;
    if (pos <= m) upd(pos, val, lson);
    else upd(pos, val, rson);
    t[rt] = op(t[ls], t[rs]);
}

pii rang; int ans;
inline int qry(int l, int r, int rt) {
    pii tmp = op(rang, t[rt]);  // 尝试合并当前权值区间 [l, r]
    // 若可合并，更新答案，返回 1 表示当前权值区间可完全合并，处在同一条路径上
    if (tmp.fi) { rang = tmp; ans = r; return 1; }
    if (l == r) return 0;
    int m = l + r >> 1;
    if (qry(lson)) qry(rson);
    return 0;
}

void Init() {
    rep(i, 1, n+1) scanf("%d", p+i), p[i]++;
    rep(i, 2, n+1) {
        scanf("%d", fa+i);
        e[fa[i]].pb(i);
    }
}

int Solve() {
    // 重链剖分求 LCA
    dfs_1(1);
    dfs_2(1, 1);

    rep(i, 1, n+1) upd(p[i], i, 1, n, 1);  // 权值 p[i] 所属路径即为节点 i
    int q; scanf("%d", &q);
    while (q--) {
        int op; scanf("%d", &op);
        if (op == 1) {
            int u, v; scanf("%d%d", &u, &v);
            swap(p[u], p[v]);
            upd(p[u], u, 1, n, 1);
            upd(p[v], v, 1, n, 1);
        } else {
            rang = mp(-1, -1);  // 可属于同一条路径上的最大权值区间
            qry(1, n, 1);
            printf("%d\n", ans);
        }
    }
    return 0;
}

// ------- main ------- //

int main ()
{
    while (~scanf("%d", &n)) {
        Init();
        Solve();
    }
    return 0;
}
```






<div STYLE="page-break-after: always;"></div>
## Divide and conquer / 分治

### 矩阵搜索

**例题 : CF677D** 

**题意** 

给定一个 n * m 的矩阵，起点在 (1, 1) ，终点为 p ，走到 x 前需要先走过 x-1 ，求走到终点的最短距离。

**题解** 

如果当前 x 的数量小于 sqrt(nm) ，就暴力用 dp 转移

否则对全图进行 bfs 

总复杂度为 O( nm * sqrt(nm) )

**证明** 

bfs 复杂度：

n * m 的矩阵里，最多只有 sqrt(nm) 个元素的个数大于 sqrt(nm) ，所以最多只会做 O( sqrt(nm) ) 次 bfs ，即复杂度为 O( nm * sqrt(nm) ) 。

dp 复杂度：

Sum( cnt[x] * cnt[x+1] ) <= Sum( cnt[x] * sqrt(nm) ) <= nm * sqrt(nm) ，所以复杂度也为 O( nm * sqrt(nm) ) 。

所以总复杂度即为 O( nm * sqrt(nm) )

**代码** 

```c++
/* <<head>> */
const int N = 3e2+7;

// ------- 变量 ------- //

int n, m, p;
vector <pii> v[N*N];
int dp[N][N];
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

// ------- 函数 ------- //

inline bool check(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

int inq[N][N], dis[N][N];
void bfs(int id) {
    memset(inq, 0, sizeof(inq));
    memset(dis, 0x3f, sizeof(dis));
    queue <pii> Q;
    for (auto o : v[id]) {
        Q.push(o);
        dis[o.fi][o.se] = dp[o.fi][o.se];
    }
    while (!Q.empty()) {
        auto fron = Q.front(); Q.pop();
        int x = fron.fi, y = fron.se;
        inq[x][y] = 0;
        rep(i, 0, 4) {
            int tx = x + dx[i], ty = y + dy[i];
            if (!check(tx, ty)) continue;
            if (dis[x][y] + 1 < dis[tx][ty]) {
                dis[tx][ty] = dis[x][y] + 1;
                if (!inq[tx][ty]) {
                    inq[tx][ty] = 1;
                    Q.push(mp(tx, ty));
                }
            }
        }
    }
    for (auto o : v[id+1])
        dp[o.fi][o.se] = dis[o.fi][o.se];
}

void Init() {
    rep(i, 1, p+1) v[i].clear();
    memset(dp, 0x3f, sizeof(dp));

    rep(i, 1, n+1) rep(j, 1, m+1) {
        int x; scanf("%d", &x);
        v[x].pb(mp(i, j));
        if (x == 1) dp[i][j] = i - 1 + j - 1;
    }
}

int Solve() {
    int lv = sqrt(n * m);
    rep(i, 1, p) {
        if (sz(v[i]) <= lv) {
            for (auto x : v[i]) for (auto y : v[i+1])
                dp[y.fi][y.se] = min(dp[y.fi][y.se], dp[x.fi][x.se] + abs(x.fi - y.fi) + abs(x.se - y.se));
        } else {
            bfs(i);
        }
    }
    return printf("%d\n", dp[v[p][0].fi][v[p][0].se]);
}

// ------- main ------- //

int main ()
{
    while (~scanf("%d%d%d", &n, &m, &p)) {
        Init();
        Solve();
    }
    return 0;
}
```



---

<div STYLE="page-break-after: always;"></div>
## Dynamic programming / 动态规划

### 背包DP

**例题 : CF808E** 

**题意**

n 个物品，每个物品有价值和体积，体积只有 1 2 3 三种，求放入体积为 m 的背包中，价值和最大。

**题解**

先按单位价值从大到小排序，然后用每个物品更新答案，但是更新答案的区间就只需要在上界 $min(V, m)$  到下界 $max( cur, min(V, m) - (mx-1)^2 )$ 的范围内。

**代码**

```c++
/* <<<head>>> */
const int N = 3e5+7;

// ------- 变量 ------- //

struct node {
    int w, c;
    db v;
    node () {}
    node (int w, int c) : w(w), c(c) {
        v = (db)c / w;
    }
    bool operator < (const node &rhs) const {
        return v > rhs.v;
    }
} a[N];

int n, m;
ll dp[N];

// ------- 函数 ------- //

void Init() {
    rep(i, 1, n+1) {
        int w, c; scanf("%d%d", &w, &c);
        a[i] = node(w, c);
    }
    sort(a + 1, a + n + 1);
}

int Solve() {
    int V = 0;
    ll ans = 0;
    rep(i, 1, n+1) {
        V = min(V + a[i].w, m);
        per(j, max(V-4, a[i].w), V+1) {
            dp[j] = max(dp[j], dp[j-a[i].w] + a[i].c);
            ans = max(ans, dp[j]);
        }
    }
    return printf("%I64d\n", ans);
}

// ------- main ------- //

int main ()
{
    while (~scanf("%d%d", &n, &m)) {
        Init();
        Solve();
    }
    return 0;
}
```



---



### 概率DP

**例题 : CF601C** 

**题意** 

m 个人， n 场比赛，每场比赛的得分等于该场比赛的名次，总得分等于各场比赛得分之和，总名次等于总得分严格小于自己的人数加一，已知其中一个人每场比赛的名次，求其期望的总名次。

**题解** 
$$
dp[i][j]\ 表示在剩下的\ m-1\ 个人中，前\ i\ 场比赛得分为\ j\ 的人数期望。\\
sum[i][j]\ 表示\ dp[i][j]\ 的前缀和。 \\
dp[i][j] = (sum[i-1][j-1] - sum[i-1][j-m-1] - dp[i-1][j-a[i]]) / (m - 1)
$$
转移的含义：

因为一场比赛得分为 1 到 m 分，所以若前 i 场得了 j 分，则前 i-1 场要得 j-m-1 到 j-1 分，这部分的人数都能转移过来。

但要扣去前 i-1 场得分为 j-a[i] 的人数，因为自己得了 a[i] 分，所以他们肯定得不了 a[i] 分。

最后除以 m-1 表示的是，转移过来的那些人，每个人在第 i 场得的分数都有 m-1 种选择，所以相当于把人分成 m-1 份，每次转移就把其中 1 / m-1 份转移了过来。

**代码** 

```c++
/* <<head>> */
const int N = (int)1e2+7;

// ------- 变量 ------- //

int n, m;
int a[N];
db dp[N][N*1007], sum[N][N*1007];
int score;

// ------- 函数 ------- //

void Init() {
    score = 0;

    rep(i, 1, n+1) scanf("%d", a+i);
    rep(i, 1, n+1) score += a[i];
}

int Solve() {
    if (m == 1) return puts("1");
    rep(j, 1, m+1) dp[1][j] = (j <= m);
    dp[1][a[1]] = 0;
    rep(j, 1, n*m+1) sum[1][j] = sum[1][j-1] + dp[1][j];
    rep(i, 2, n+1) rep(j, 1, n*m+1) {
        dp[i][j] = (sum[i-1][j-1] - sum[i-1][max(0, j-m-1)] - dp[i-1][max(0, j-a[i])]) / (m - 1);
        sum[i][j] = sum[i][j-1] + dp[i][j];
    }
    return printf("%.12f\n", sum[n][score-1] + 1);
}

// ------- main ------- //

int main ()
{
    while (~scanf("%d%d", &n, &m)) {
        Init();
        Solve();
    }
    return 0;
}
```



---



### 区间DP

**例题 : CF1107E** 

**题意** 

给定又给 01 串，每次可消除一段连续的 1 或连续的 0 ，消除的价值为 a[ 消除的长度 ] ，求将整个串消除完的最大价值。

**题解**

dfs(l, r, k) 表示将 l - k +1 到 r 这段区间消除掉所能获得的最大价值。

l 和 r 表示端点， k 表示在 l 端点前，有一段长为 k-1 的与 s[l] 字符相同的字符串。

转移：

1. 把和 l 粘连的那一段，连同 l 一起删掉，则

   dfs(l, r, k) = a[k] + dfs(l+1, r, 1)

2. 在 l+1 到 r 中找到一个点 i ， 且 s[i] = s[l] ，把 l+1 到 i-1 的区间删掉，则

   dfs(l, r, k) = dfs(l+1, i-1, 1) + dfs(i, r, k+1)

**代码**

```c++
/* <<head>> */
const int N = (int)1e2+7;

// ------- 变量 ------- //

int n, a[N];
char s[N];
ll dp[N][N][N];

// ------- 函数 ------- //

ll dfs(int l, int r, int k) {
    if (~dp[l][r][k]) return dp[l][r][k];
    if (l == r) return a[k];
    if (l > r) return 0;
    ll res = a[k] + dfs(l+1, r, 1);
    rep(i, l+1, r+1) if (s[l] == s[i]) res = max(res, dfs(l+1, i-1, 1) + dfs(i, r, k+1));
    return dp[l][r][k] = res;
}

void Init() {
    memset(dp, -1, sizeof(dp));

    rep(i, 1, n+1) scanf("%d", a+i);
}

int Solve() {
    return printf("%lld\n", dfs(1, n, 1));
}

// ------- main ------- //

int main ()
{
    while (~scanf("%d%s", &n, s + 1)) {
        Init();
        Solve();
    }
    return 0;
}

```



---



### 数位DP

**模板**

```c++
// 如果多组数据不影响 dp[][] ，就放在 while() 外面
memset(dp, -1, sizeof(dp));

int dp[ 数位长度 ][ 状态数 ], num[ 数位长度 ];

// pos ：当前枚举位， state ：当前状态， limit ：当前枚举位是否有限制
T dfs(int pos, int state, bool limit) {
    
    // 枚举完毕，判断状态合法性，返回相应值
    if (pos == -1) return check(state);
    
    // 记忆化搜索
    if (!limit && dp[pos][state] != -1) return dp[pos][state];
    
    // 确定上界
    int up = limit ? num[pos] : 9;
    
    T ans = 0;
    rep(i, 0, up+1) {
        
        // 状态非法
        if (!check(state, i)) continue;
        
        // 累加贡献
        ans += dfs(pos-1, change(state, i), limit && i==num[pos]);
    }
    return limit ? ans : dp[pos][state] = ans;
}

ll digit(ll x) {
    int pos = 0;
    while (x) {
        num[pos++] = x % 10;
        x /= 10;
    }
    return dfs(pos-1, state, true);
}
```



**笔记**

1. dfs 的返回值为题目所求，如方案数，以及通过方案数转移得到的量，如权值和，立方和等，可能是个结构体。
2. dfs 的 state 参数为题目的约束条件，同时要考虑是否适合 dp 数组存储。



**例题 : CF1073E** 

**题意**

求 l 到 r 中，所有 各位数字种类数不超过 k 的数字 之和。

**题解**

mask 记录当前数字的各位数字种类数

first 用于防止将前导零计算进种类数

res.fi 表示满足条件的数字个数

res.se 表示满足条件的数字的总和

**代码**

```c++
/* <<head>> */
const int MOD = (int)998244353;
const int N = (int)1e6+7;

// ------- 变量 ------- //

ll l, r, pw[19];
int k;

// ------- 函数 ------- //

inline int add(ll a, ll b) { if ((a += b) >= MOD) a -= MOD; return a; }
inline pii add(pii a, pii b) { return mp(add(a.fi, b.fi), add(a.se, b.se)); }
inline int mul(ll a, ll b) { if ((a *= b) >= MOD) a %= MOD; return a; }

bool check(int state) { return __builtin_popcount(state) <= k; }
bool check(int state, int i) { return check(state | (1 << i)); }

pii dp[20][1<<10]; int num[20];
pii dfs(int pos, int mask, bool first, bool limit) {
    if (pos == -1) { return mp(check(mask), 0); }
    if (!limit && dp[pos][mask].fi != -1) return dp[pos][mask];
    int up = limit ? num[pos] : 9;
    pii ans = mp(0, 0);
    rep(i, 0, up+1) {
        pii res;
        if (!i && first) res = dfs(pos-1, mask, 1, limit && i==num[pos]);
        else {
            if (!check(mask, i)) continue;
            res = dfs(pos-1, mask | (1 << i), 0, limit && i==num[pos]);
        }
        ans.fi = add(ans.fi, res.fi);
        ans.se = add(ans.se, add(res.se, mul(res.fi, mul(i, pw[pos]))));
    }
    return limit ? ans : dp[pos][mask] = ans;
}

int digit(ll x) {
    int pos = 0;
    while (x) {
        num[pos++] = x % 10;
        x /= 10;
    }
    return dfs(pos-1, 0, 1, 1).se;
}

void Init() {
    memset(dp, -1, sizeof(dp));
    pw[0] = 1;
    rep(i, 1, 19) pw[i] = mul(pw[i-1], 10);
}

int Solve() {
    return printf("%d\n", add(digit(r), MOD-digit(l-1)));
}

// ------- main ------- //

int main ()
{
    while (~scanf("%lld%lld%d", &l, &r, &k)) {
        Init();
        Solve();
    }
    return 0;
}
```



---



### 斜率优化

**例题 : POJ1180** 

**题意** 

N 个任务，按顺序执行。

执行第 i 个任务所需时间 Ti 。

可以把任务分成若干批，每批连续的若干个任务。

每批任务开始前需 S 的启动时间，故执行一批任务所需时间为 S 加上每个任务所需时间之和。

同一批任务同一时刻完成，即该批任务全部执行完毕。

每个任务的费用为完成时刻乘以费用系数 Ci

请规划分组方案，使得总费用最小。

**题解**

$$
\large F[i]=\mathop{min}\limits_{0\le j<i}\{F[j]+sumT[i]*(sumC[i]-sumC[j])+S*(sumC[N]-sumC[j])\}
$$

F[i] 表示把前 i 个任务分成若干批执行的最小费用。

第 j + 1 到 i 个任务在同一批内完成。

sumC 和 sumT 表示 C 和 T 的前缀和。

sumT 是忽略机器的启动时间时，这批任务的完成时刻。

启动时间 S 会对第 j + 1 个之后的所有任务产生影响。—— “费用提前计算”

**斜率优化**

状态转移方程变形：$\large y = kx+b$

（仅与 j 有关的项）=（i ，j 的乘积项）+（常数、仅与 i 有关的项）

$$
\large F[j]=(S+sumT[i])*sumC[j]+F[i]-sumT[i]*sumC[i]-S*sumC[N]
$$

点坐标：( sumC[j] , F[j] )

斜率：S + sumT[i]

截距：F[i] - sumT[i] \* sumC[i] - S \* sumC[N]

斜率固定，求经过哪个点，使得截距最小。

**特征**

- 横坐标单调递增 —— 点出现在凸壳最右端

- 斜率单调递增 —— 维护线段斜率大于直线斜率的线段

所以，维护凸壳上 “连接相邻两点的线段的斜率” 大于 S + sumT[i] 的部分，则凸壳最左端顶点为最优决策。

**维护**

单调队列 Q

1. 检查队首两个元素，若斜率 $(F[Q[l+1]]-F[Q[l]])/(sumC[Q[l+1]]-sumC[Q[l]]) \le S + sumT[i]$ ，则队首出队，继续检查队首元素。
2. 取队首为最优决策，计算出 $F[i]$ 。
3. 新决策 i 插入队尾，若队尾三个元素不满足下凸性，则中间元素出队，继续检查队尾元素。

**代码**

```c++
/* <<head>> */
const int N = (int)1e6+7;

// -------------------------------------- 变量 -------------------------------------- //

int n, s, t[N], c[N];
ll sumT[N], sumC[N];
ll dp[N];

// -------------------------------------- 函数 -------------------------------------- //

void Init() {
    rep(i, 1, n+1) scanf("%d%d", t+i, c+i);
    rep(i, 1, n+1) {
        sumT[i] = sumT[i-1] + t[i];
        sumC[i] = sumC[i-1] + c[i];
    }
}

struct P {
    ll x, y;
    P () {} P (ll x, ll y) : x(x), y(y) {}
    P operator - (const P &rhs) const { return P(x - rhs.x, y - rhs.y); }
    
    // 叉积可能爆 long long ，返回叉积是否大于 0
    bool operator ^ (const P &rhs) const { return (db)x * rhs.y > (db)y * rhs.x; }
};
#define X(i) (sumC[i])      // 点的横坐标
#define Y(i) (dp[i])        // 点的纵坐标
#define K(i) (s + sumT[i])  // 直线斜率

int Solve() {
    dp[0] = 0;        // 0 个任务费用为 0
    deque <P> Q; Q.pb(P(X(0), Y(0)));    // 设置初值
    rep(i, 1, n+1) {
        // 队首斜率 小于 直线斜率
        while (sz(Q) > 1 && (Q[1].y - Q[0].y) < (Q[1].x - Q[0].x) * K(i)) Q.pop_front();
        
        // dp[i] 通过 dp[j] 的转移式
        dp[i] = Q[0].y - K(i) * Q[0].x + sumT[i] * sumC[i] + s * sumC[n];
        
        // 第 i 个结点待入队
        P a(X(i), Y(i));
        
        // 队尾元素是否下凸
        while (sz(Q) > 1 && !((Q[sz(Q)-2] - a) ^ (Q.back() - a))) Q.pop_back();
        
        // 第 i 个结点入队
        Q.pb(a);
    }
    return printf("%lld\n", dp[n]);
}

// -------------------------------------- main -------------------------------------- //

int main ()
{
    while (~scanf("%d%d", &n, &s)) {
        Init();
        Solve();
    }
    return 0;
}
```



---



**例题 2 : BZOJ2726** 

**题意**

同 “ 例题 ” ，但 T 可能为负数。

**题解**

$$
\large F[j]=(S+sumT[i])*sumC[j]+F[i]-sumT[i]*sumC[i]-S*sumC[N]
$$

**特征**

- 横坐标单调递增 —— 点出现在凸壳最右端

- 直线斜率不具有单调性 —— 维护整个凸壳，二分查找答案

**维护**

单调队列 Q

1. 二分查找最优决策，左侧线段斜率比直线斜率小，右侧线段斜率比直线斜率大。
3. 新决策 i 插入队尾，若队尾三个元素不满足下凸性，则中间元素出队，继续检查队尾元素。

**代码**

```c++
/* <<head>> */
const int N = (int)1e6+7;

// -------------------------------------- 变量 -------------------------------------- //

int n, s, t[N], c[N];
ll sumT[N], sumC[N];
ll dp[N];

// -------------------------------------- 函数 -------------------------------------- //

void Init() {
    rep(i, 1, n+1) scanf("%d%d", t+i, c+i);
    rep(i, 1, n+1) {
        sumT[i] = sumT[i-1] + t[i];
        sumC[i] = sumC[i-1] + c[i];
    }
}

struct P {
    ll x, y;
    P () {} P (ll x, ll y) : x(x), y(y) {}
    P operator - (const P &rhs) const { return P(x - rhs.x, y - rhs.y); }
    
    // 叉积可能爆 long long ，返回叉积是否大于 0
    bool operator ^ (const P &rhs) const { return (db)x * rhs.y > (db)y * rhs.x; }
};
#define X(i) (sumC[i])      // 点的横坐标
#define Y(i) (dp[i])        // 点的纵坐标
#define K(i) (s + sumT[i])  // 直线斜率

int Solve() {
    dp[0] = 0;        // 0 个任务费用为 0
    deque <P> Q; Q.pb(P(X(0), Y(0)));    // 设置初值
    rep(i, 1, n+1) {
        // 二分查找最优决策，左侧线段斜率比直线斜率小，右侧线段斜率比直线斜率大
        int L = 0, R = sz(Q) - 1;
        while (L < R) {
            int M = (L + R) >> 1;
            if (Q[M+1].y - Q[M].y <= K(i) * (Q[M+1].x - Q[M].x)) L = M + 1;
            else R = M;
        }
        
        // 点 Q[L] 为最优决策点，转移获得 dp[i]
        dp[i] = Q[L].y - K(i) * Q[L].x + sumT[i] * sumC[i] + s * sumC[n];
        
        // 第 i 个结点待入队
        P a(X(i), Y(i));
        
        // 队尾元素是否下凸
        while (sz(Q) > 1 && !((Q[sz(Q)-2] - a) ^ (Q.back() - a))) Q.pop_back();
        
        // 第 i 个结点入队
        Q.pb(a);
    }
    return printf("%lld\n", dp[n]);
}

// -------------------------------------- main -------------------------------------- //

int main ()
{
    while (~scanf("%d%d", &n, &s)) {
        Init();
        Solve();
    }
    return 0;
}
```



---



**例题 3 : CF311B** 

**题意**

有一些猫，放在一些位置，人走到每个猫的时间已知，各只猫出现的时间已知，假设派出一个人，可以自由安排其出发时间，接收沿途已经出现的猫，猫等待的时间是被接收的时间减去出现的时间。现有 P 个人，问所有猫的总等待时间最小是多少。

**题解**
$$
f[i][j]=min(f[i−1][k]+a[j]∗(j−k)+(sum[j]−sum[k]))
$$

**代码**

```c++
/* <<head>> */
const int N = (int)1e5+7;

// ------- 变量 ------- //

int n, m, p;
int d[N], h[N], t[N];
ll dp[107][N], a[N], sum[N];

// ------- 函数 ------- //

void Init() {
    memset(dp, 0x3f, sizeof(dp));

    rep(i, 2, n+1) scanf("%d", d+i);
    rep(i, 1, m+1) scanf("%d%d", h+i, t+i);
    
    rep(i, 3, n+1) d[i] += d[i-1];
    rep(i, 1, m+1) a[i] = t[i] - d[h[i]];
    sort(a + 1, a + m + 1);
    
    rep(i, 1, m+1) sum[i] = sum[i-1] + a[i];

}

struct P {
    ll x, y;
    P () {} P (ll x, ll y) : x(x), y(y) {}
    P operator - (const P &rhs) const { return P(x - rhs.x, y - rhs.y); }
    bool operator ^ (const P &rhs) const { return (db)x * rhs.y > (db)y * rhs.x; }
};
#define X(i) (i)
#define Y(i, j) (dp[i][j]+sum[j])
#define K(i) (a[i])

int Solve() {
    rep(i, 0, p+1) dp[i][0] = 0;
    rep(i, 1, p+1) {
        // 斜率优化的单调队列针对 i-1 那一行
        deque <P> Q; Q.pb(P(X(0), Y(i-1, 0)));
        rep(j, 1, m+1) {
            while (sz(Q) > 1 && (Q[1].y - Q[0].y) < (Q[1].x - Q[0].x) * K(j)) Q.pop_front();
            // 前 j 只猫都让前 i-1 个人接
            dp[i][j] = min(dp[i-1][j], Q[0].y - K(j) * Q[0].x + a[j] * j - sum[j]);
            // 第 i-1 行第 j 列的 dp 值加入单调队列
            P aa(X(j), Y(i-1, j));
            while (sz(Q) > 1 && !((Q[sz(Q)-2] - aa) ^ (Q.back() - aa))) Q.pop_back();
            Q.pb(aa);
        }
    }
    return printf("%lld\n", dp[p][m]);
}

// ------- main ------- //

int main ()
{
    while (~scanf("%d%d%d", &n, &m, &p)) {
        Init();
        Solve();
    }
    return 0;
}
```



---



### 括号匹配

**例题 : CF466D** 

**题意**

给定一个长度为 n 的序列，每次操作可以将一个区间的值全部加一，但是不能有某个端点同时作为两个区间的左端点或右端点（可以既做左端点，又做右端点），问有多少种方案可以使得所有数字变成 h 。

**题解**

dp[i]\[j] 表示前 i 个数里，有 j 个待匹配的左括号。

对于第 i 个数，有五种情况：

1. 不做端点
2. 自成一个区间，既做左端点，又做右端点
3. 做后面一个区间的左端点
4. 做前面一个区间的右端点
5. 既做前面一个区间的右端点，又做后面一个区间的左端点

**代码**

```c++
/* <<head>> */
const int MOD = (int)1e9+7;
const int N = (int)2e3+7;

// ------- 变量 ------- //

int n, h;
int a[N], dp[N][N];

// ------- 函数 ------- //

void Init() {
    memset(dp, 0, sizeof(dp));
    rep(i, 1, n+1) scanf("%d", a+i);
}

inline int add(ll a, int b) { if ((a += b) >= MOD) a -= MOD; return a; }
inline int mul(ll a, int b) { if ((a *= b) >= MOD) a %= MOD; return a; }

int Solve() {
    dp[0][0] = 1;  // 前 0 个数，有 0 个待匹配的左括号，方案数为 1
    
    // 向前 dp ，考虑 dp[i][j] 从哪些地方转移而来
    rep(i, 1, n+1) rep(j, 0, i+1) {
        // 因为当前要计算的是 dp[i][j] ，所以要根据不同情况选择前一个状态 : j, j-1, j+1
        
        // 情况 1 : a[i] 要被 j 个区间覆盖，所以需要 a[i] + j == h
        /* -- */ if (a[i] + j == h) dp[i][j] = add(dp[i][j], dp[i-1][j]);
        
        // 情况 2 : a[i] 被前 j 个区间覆盖，又被自己的区间覆盖
        /* [] */ if (a[i] + j + 1 == h) dp[i][j] = add(dp[i][j], dp[i-1][j]);
        
        // 情况 3 : a[i] 被前 j-1 个区间覆盖，又被自己新开的区间覆盖
        /* [  */ if (j && a[i] + j == h) dp[i][j] = add(dp[i][j], dp[i-1][j-1]);
        
        // 情况 4 : a[i] 被前 j+1 个区间覆盖
        /*  ] */ if (a[i] + j + 1 == h) dp[i][j] = add(dp[i][j], mul(j+1, dp[i-1][j+1]));
        
        // 情况 5 : a[i] 被前 j 个区间覆盖，又被自己新开的区间覆盖
        /* ][ */ if (a[i] + j + 1 == h) dp[i][j] = add(dp[i][j], mul(j, dp[i-1][j]));
    }
    return printf("%d\n", dp[n][0]);
}

// ------- main ------- //

int main ()
{
    while (~scanf("%d%d", &n, &h)) {
        Init();
        Solve();
    }
    return 0;
}
```



------



**例题 2 : CF626F** 

**题意**

给定 n 个数，分为若干组，求每组极差之和不超过 k 的方案数。

**题解**

dp[i]\[j]\[k] 表示前 i 个数里，有 j 个待匹配的左括号，目前极差之和为 k 。

对于第 i 个数，有四种情况：

1. 在前面一个集合中，不是第一个元素，也不是最后一个元素
2. 自成一个集合，既是第一个元素，又是最后一个元素
3. 做后面一个集合的第一个元素
4. 做前面一个集合的最后一个元素

**代码**

```c++
/* <<head>> */
const int MOD = (int)1e9+7;
const int N = (int)200+7;

// ------- 变量 ------- //

int n, kk;
int a[N], dp[N][N][1007];

// ------- 函数 ------- //

inline int add(ll a, int b) { if ((a += b) >= MOD) a -= MOD; return a; }
inline int mul(ll a, int b) { if ((a *= b) >= MOD) a %= MOD; return a; }

void Init() {
    memset(dp, 0, sizeof(dp));

    rep(i, 1, n+1) scanf("%d", a+i);
    sort(a + 1, a + n + 1);
}

int Solve() {
    dp[0][0][0] = 1;  // 前 0 个数，有 0 个待匹配的左括号，极差之和为 0 的方案数为 1
    
    // 向后 dp ，确定 dp[i][j][k] ，向后能转移给哪些地方
    rep(i, 0, n) rep(j, 0, i+1) rep(k, 0, kk+1) { // i 从 0 到 n-1
        
        // 在前 i 个数里，有 j 个待匹配的左括号，所以 a[i+1] 与 a[i] 一定贡献 j 个差值
        int cha = a[i+1] - a[i], tk = k + j * cha;
        if (tk > kk) continue;
        
        // 凡是涉及第 i+1 个从前面 j 个集合中选一个的，方案数都需要乘 j （第 1 种和第 4 种）
        /* -- */ dp[i+1][j][tk] = add(dp[i+1][j][tk], mul(j, dp[i][j][k]));
        /* [] */ dp[i+1][j][tk] = add(dp[i+1][j][tk], dp[i][j][k]);
        /* [  */ dp[i+1][j+1][tk] = add(dp[i+1][j+1][tk], dp[i][j][k]);
        /*  ] */ if (j) dp[i+1][j-1][tk] = add(dp[i+1][j-1][tk], mul(j, dp[i][j][k]));
    }
    int ans = 0;
    rep(i, 0, kk+1) ans = add(ans, dp[n][0][i]);
    return printf("%d\n", ans);
}

// ------- main ------- //

int main ()
{
    while (~scanf("%d%d", &n, &kk)) {
        Init();
        Solve();
    }
    return 0;
}
```



------



### 分割问题

设 $f(n)$ 表示用 $n$ 个图形，最多可以分割出的区域数量。

设 $g(n)$ 表示用第 $n$ 个图形，最多可以增加出的区域数量。

即，
$$
f(n) = f(n-1) + g(n)
$$
且，
$$
f(0) = 1
$$
则，
$$
\large f(n) = 1 + \sum_{i=1}^{n}g(i)
$$


#### 直线分割平面

第 $n$ 条直线，要增加最多的分割区域，

必须与前 $n-1$ 条直线相交，形成 $n-1$ 个交点，

这些交点将第 $n$ 条直线分为 $2$ 条射线与 $n-2$ 条线段，

每条射线与线段将区域一分为二，即增加了 $g(n) = 2 + (n - 2) = n$ 个区域。

所以：
$$
\begin{align}
f(n) &= 1 + \sum_{i=1}^ng(i)\\
&= 1 + \frac{n(1+n)}{2}
\end{align}
$$


#### 折线分割平面

折线：由同一端点射出的 $2$ 条射线

第 $n$ 条折线，要增加最多的分割区域，

必须与前 $n-1$ 条折线相交，即与 $2(n-1)$ 条射线相交，

第 $n$ 条折线有 $2$ 条射线，形成 $4(n-1)$ 个交点，

这些交点将第 $n$ 条折线分为 $2$ 条射线与 $4(n-1)$ 条线段，

每条射线与每条线段增加 $1$ 个区域，但位于端点的两条线段只能增加 $1$ 个区域,

即，总增加区域数为 $g(n) = 2 + 4 (n-1) - 1 = 4n-3$ 

所以：
$$
\begin{align}
f(n) &= 1 + \sum_{i=1}^ng(i)\\
&= 1 + \sum_{i=1}^{n}(4i-3)\\
&= 1 - 3n + 4\sum_{i=1}^ni\\
&= 1 - 3n + 4 * \frac{n(1+n)}{2}\\
&= 1 - 3n + 2n(1+n)\\
&= 2n^2-n+1
\end{align}
$$


#### 封闭曲线分割平面

问题定义：

平面上 $n$ 条封闭曲线，任意两条封闭曲线恰好相交于两点，且任何三条曲线不相交于同一点，求这 $n$ 条曲线把平面分割成的区域总数。



第 $n$ 条封闭曲线，与前 $n-1$ 条封闭曲线相交，形成 $2(n-1)$ 个交点，

这些交点将第 $n$ 条封闭曲线分为 $2(n-1)$ 条线段，

每条线段将增加 $1$ 个区域，即增加了 $g(n) = 2(n - 1)  = 2n - 2$ 个区域。

注意：当 $n=1$ 时，虽然没有交点，但存在 $1$ 条线段，即 $g(1)=1$ 。

所以：
$$
\begin{align}
f(n) &= 1 + \sum_{i=1}^ng(i)\\
&= 1 + 1 + \sum_{i=2}^n(2i-2)\\
&= 2 - 2(n-1) + 2\sum_{i=2}^ni\\
&= 4 - 2n + \frac{2(n+2)(n-1)}{2}\\
&= n^2 - n + 2
\end{align}
$$

#### 平面分割空间

第 $n$ 个平面与前 $n-1$ 个平面相交，形成 $n-1$ 条交线，

这 $n-1$ 条交线可以把第 $n$ 个平面最多分割成 $h(n-1)$ 个区域，

$h(n-1)$ 即为用 $n-1$ 条直线分割平面，最多可以分割出的区域数量，

则第 $n$ 个平面的每个被分割出的区域，都将空间一分为二，

即，增加了 $\large g(n) = h(n-1) = 1 + \frac{n(n-1)}{2}$ 个空间。

所以：
$$
\begin{align}
f(n) &= 1 + \sum_{i=1}^ng(i)\\
&= 1 + \sum_{i=1}^n[1 + \frac{i(i-1)}{2}]\\
&= 1 + n + \frac{1}{2}\sum_{i=1}^n(i^2-i)\\
&= 1 + n + \frac{1}{2}(\frac{n(n+1)(2n+1)}{6}-\frac{n(n+1)}{2})\\
&= 1 + n + \frac{1}{2}(\frac{2n^3+3n^2+n}{6}-\frac{3n^2+3n}{6})\\
&= 1 + n + \frac{1}{2}(\frac{2n^3-2n}{6})\\
&= 1 + n + \frac{n^3-n}{6}\\
&= 1 + \frac{n^3+5n}{6}
\end{align}
$$
附：如何证明 $n^3 - n$ 是 $6$ 的倍数

证： $n^3-n = n(n^2-1) = n (n+1)(n-1)$ ，因为是三个连续的整数，所以必含 $2$ 的倍数和 $3$ 的倍数，因此其乘积一定是 $6$ 的倍数，命题得证。



---

<div STYLE="page-break-after: always;"></div>
## Games / 博弈论

### 尼姆博弈

n 堆石子，每堆 a[i] 个石子，每次取**某一堆**任意数量（至少取一个）石子，最后无石子可取者为败。

必败态： a[1] ^ a[2] ^ ... ^ a[n-1] ^ a[n] == 0



#### 广义尼姆博弈

n 堆石子，每堆 a[i] 个石子，每次将**某一堆**石子状态转移到另一个状态，最后无法转移者为败。

必败态： sg[a[1]] ^ sg[a[2]] ^ ... ^ sg[a[n-1]] ^ sg[a[n]] == 0



#### SG函数

定义一个对于集合的操作 mex ，表示最小的不属于该集合的非负整数。

例如： mex{ 0, 1, 2 } = 3 ， mex{ 1, 2, 3 } = 0 ， mex{ 0, 1, 3 } = 2

SG(x) = mex{ SG(y) | y 是 x 的后继状态，即 x 可转移到的所有状态 }

**模板** 

```c++
// 求 0 ~ n 的 sg 函数值
int sg[N];
bool vis[N];
void GetSG(int n) {
    memset(sg, 0, sizeof(sg));
    rep(i, 1, n+1) {
        memset(vis, 0, sizeof(vis));
        for (all next state from i) vis[sg[next(i)]] = 1;
        rep(j, 0, n+1) if (!vis[j]) {
            sg[i] = j;
            break;
        }
    }
}

// 记忆化搜索求 sg 函数值
map <int, int> sg;
int SG(int x) {
    if (!x) return 0;
    if (sg.count(x)) return sg[x];
    map <int, int> vis;
    for (all next state from x) vis[SG(next(x))] = 1
    rep(i, 0, N) if (!vis.count(i)) return sg[mask] = i;
}
```



---



**例题 : CF850C** 

**题意**

给定 n 个数，两人轮流从中改数，每次选一个素数 p 和一个正整数 k ，将 n 个数中所有可以被 p^k 整除的数除以 p^k 。当玩家在他的回合把所有数都变成 1 后，该玩家胜利。

**题解**

每个数为其所有质因子贡献相应的指数。

n 个数的所有质因子，每个质因子看作一堆石子。

石子的状态为该质因子所有出现过的指数，用二进制形式表示，第 i 位为 1 ，表示出现过 p 的 i 次方，下标从 1 开始。

对于 p^k ，状态转移即为，将 p 这堆石子的状态，大于等于 k 的那部分指数右移。

求所有石子的 sg 函数，再求异或和即可。

**代码**

```c++
/* <<head>> {{{*/
const int N = (int)1e2+7;

// ------- 变量 ------- //

int n, a[N];
map <int, int> pri, sg;

// ------- 函数 ------- //

void DPF(int x) {
    for (int i = 2; i * i <= x; ++i) if (x % i == 0) {
        int cnt = 0;
        while (x % i == 0) x /= i, cnt++;
        pri[i] = pri[i] | (1 << (cnt-1));
    }
    if (x > 1) pri[x] = pri[x] | 1;
}

int SG(int mask) {
    if (!mask) return 0;
    if (sg.count(mask)) return sg[mask];
    map <int, int> vis;
    int bit = 32 - __builtin_clz(mask);
    rep(i, 1, bit+1) vis[SG( (mask >> i) | (mask & ((1 << (i-1)) - 1)) )] = 1;
    rep(i, 0, N) if (!vis.count(i)) return sg[mask] = i;
}

void Init() {
    pri.clear();
    sg.clear();

    rep(i, 1, n+1) scanf("%d", a+i);
}

int Solve() {
    rep(i, 1, n+1) DPF(a[i]);

    int ans = 0;
    for (auto o : pri) {
        int p = o.fi, mask = o.se;
        ans ^= SG(mask);
    }
    return puts(ans ? "Mojtaba" : "Arpa");
}

// ------- main ------- //

int main ()
{
    while (~scanf("%d", &n)) {
        Init();
        Solve();
    }
    return 0;
}

```



---

<div STYLE="page-break-after: always;"></div>
## Geometry / 计算几何

### 分形

- **POJ3889** 

**题意**

询问等级 $N$ 的分形图中，编号为 $S$ 的点坐标与编号为 $T$ 的点坐标的直线距离。

**题解**

递归，坐标变换。

**代码** 

```c++
/* <<head>> */

// ------- 变量 ------- //

int n;
ll S, T;

// ------- 函数 ------- //

void move(pair<ll, ll> &pos, ll d) { pos.fi += d; pos.se += d; }

void rot(pair<ll, ll> &pos, int f) {
    pair<ll, ll> tmp = pos;
    swap(tmp.fi, tmp.se);
    if (f) tmp.se = -tmp.se; else tmp.fi = -tmp.fi;
    pos = tmp;
}

void flip(pair<ll, ll> &pos) { pos.se = -pos.se; }

pair<ll, ll> tran(pair<ll, ll> pos, ll len, int f) {
    if (f == 1 || f == 2) return pos;
    pos.fi <<= 1; pos.se <<= 1;  // 缩放
    move(pos, -len);             // 平移
    rot(pos, f == 0);            // 旋转
    flip(pos);                   // 水平翻转
    move(pos, len);              // 平移
    pos.fi >>= 1; pos.se >>= 1;  // 缩放
    return pos;
}

pair<ll, ll> work(int n, ll id) {
    if (n == 0) return mp(0, 0);
    ll len = 1ll << (n-1), cnt = 1ll << (2 * n - 2);  // 等级 n-1 的分形图的边长和元素个数
    pair<ll, ll> pos = work(n-1, id % cnt);
    pair<ll, ll> res = tran(pos, len-1, id / cnt);
    switch (id / cnt) {
        case 0 : return res;
        case 1 : return mp(res.fi, res.se + len);
        case 2 : return mp(res.fi + len, res.se + len);
        case 3 : return mp(res.fi + len, res.se);
    }
}

void Init() {
    scanf("%d%lld%lld", &n, &S, &T);
    S--; T--;
}

int Solve() {
    pair<ll, ll> ss = work(n, S);
    pair<ll, ll> tt = work(n, T);
    ll dx = ss.fi - tt.fi, dy = ss.se - tt.se;
    return printf("%.0f\n", (db)sqrt(dx * dx + dy * dy) * 10);
}

// ------- main ------- //

int main ()
{
    int t; scanf("%d", &t); while (t--) {
        Init();
        Solve();
    }
    return 0;
}
```



---


<div STYLE="page-break-after: always;"></div>
## Graphs / 图论

### 割点

- **BZOJ1123** 

**题意** 

n 个点， m 条边的无向图，保证连通。求当把与节点 i 关联的边删掉后，有多少有序点对 ( x, y ) 满足 x 和 y 不连通。

**题解**

若 u 不是割点，则答案为 2 * (n - 1)

若 u 是割点，则统计删除边后形成的连通块，

1. 节点 u 自身构成一个连通块
2. 搜索树上满足 low[v] >= dfn[u] 的子节点 v 各自形成的连通块
3. 除上述节点之外的所有点构成的连通块

所有连通块贡献之和即为答案。

**代码**

```c++
/* <<head>> */
const int N = (int)1e5+7;

// ------- 变量 ------- //

int n, m;
vi e[N];
ll ans[N];

// ------- 函数 ------- //

bool cut[N];
int dfn[N], low[N], sz[N], no;

void cutpoint(int u, int rt) {
    dfn[u] = low[u] = ++no; sz[u] = 1;
    int son = 0, sum = 0;
    for (auto v : e[u]) {
        if (!dfn[v]) {
            cutpoint(v, rt);
            sz[u] += sz[v];
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                son++;
                if (u != rt || son > 1) cut[u] = 1;
                sum += sz[v];
                ans[u] += 1ll * sz[v] * (n - sz[v]);
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (cut[u]) ans[u] += 1ll * (n - sum - 1) * (sum + 1) + (n - 1);
    else ans[u] = 2 * (n - 1);
}

void run(int n) {
    no = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(cut, 0, sizeof(cut));
    rep(i, 1, n+1) if (!dfn[i]) cutpoint(i, i);
}

void Init() {
    rep(i, 0, n+1) e[i].clear();

    rep(i, 0, m) {
        int u, v; scanf("%d%d", &u, &v);
        e[u].pb(v); e[v].pb(u);
    }
}

int Solve() {
    run(n);
    rep(i, 1, n+1) printf("%lld\n", ans[i]);
    return 0;
}

// ------- main ------- //

int main ()
{
    while (~scanf("%d%d", &n, &m)) {
        Init();
        Solve();
    }
    return 0;
}
```



---



### 边双连通分量（BCC）及缩点

- **POJ3694** 

**题意**

n 个点， m 条边的无向连通图， Q 次操作，每次加一条边，并询问图中桥的数量。

**题解**

求边双连通分量，缩点，在求 LCA 过程中统计桥，并查集路径压缩。

**代码**

```c++
/* <<head>> */
const int N = (int)2e5+7;

// ------- 变量 ------- //

int n, m, edge, fa[N];

// ------- 函数 ------- //

bool bri[N];
vector <pii> e[N];
int dfn[N], low[N], bcc[N], S[N], top, cnt, no;
void BCC(int u, int eid) {
    dfn[u] = low[u] = ++no;
    S[top++] = u;
    for (auto o : e[u]) {
        int v = o.fi, id = o.se;
        if (!dfn[v]) {
            BCC(v, id);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) bri[id] = 1;
        } else if (id != eid) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        ++cnt;
        do { bcc[S[--top]] = cnt; } while (S[top] != u);
    }
}

vi e2[N];
void run(int n) {
    no = top = cnt = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(bri, 0, sizeof(bri));
    memset(bcc, 0, sizeof(bcc));
    rep(i, 1, n+1) if (!dfn[i]) BCC(i, 0);
    rep(i, 1, cnt+1) e2[i].clear();
    rep(u, 1, n+1) for (auto o : e[u])
        if (bcc[u] != bcc[o.fi]) e2[bcc[u]].pb(bcc[o.fi]);
}

int f[N], dep[N];
void dfs(int u, int p, int d) {
    f[u] = p; dep[u] = d;
    for (auto v : e2[u]) if (v != p) dfs(v, u, d+1);
}

int Find(int x) { return x == fa[x] ? x : fa[x] = Find(fa[x]); }
void Union(int x, int y) { fa[Find(y)] = Find(x); }

void Init() {
    edge = 0;
    int id = 0;
    rep(i, 0, n+1) e[i].clear();
    rep(i, 0, m) {
        int u, v; scanf("%d%d", &u, &v);
        ++id;
        e[u].pb(mp(v, id)); e[v].pb(mp(u, id));
    }
}

int Solve() {
    run(n);
    edge = cnt - 1;

    dfs(1, 1, 0);

    rep(i, 1, cnt+1) fa[i] = i;

    int q; scanf("%d", &q);
    while (q--) {
        int u, v; scanf("%d%d", &u, &v);
        u = bcc[u]; v = bcc[v];
        int fu = Find(u), fv = Find(v);
        while (fu != fv) {
            if (dep[fu] > dep[fv]) {
                Union(f[fu], fu);
                edge--;
                fu = Find(fu);
            } else if (dep[fu] < dep[fv]) {
                Union(f[fv], fv);
                edge--;
                fv = Find(fv);
            } else {
                Union(f[fu], fu); Union(f[fv], fv);
                edge -= 2;
                fu = Find(fu); fv = Find(fv);
            }
        }
        printf("%d\n", edge);
    }
    return puts("");
}

// ------- main ------- //

int main ()
{
    while (~scanf("%d%d", &n, &m)) {
        if (n == 0) break;
        static int kase = 0; printf("Case %d:\n", ++kase);
        Init();
        Solve();
    }
    return 0;
}
```



---



### 点双连通分量（DCC）及缩点

- **POJ2942** 

**题意**

n 个点， m 条边， 每条边表示两端点不能相邻，求有多少个点不被任何奇环包含。

**题解**

建补图，求点双连通分量，判断每个分量里是否有奇环，有则该分量里所有点都可被奇环包含。

**代码**

```c++
/* <<head>> */
const int N = (int)1e3+7;

// ------- 变量 ------- //

int n, m;
bool g[N][N];
vi e[N];

// ------- 函数 ------- //

vi Dcc[N];
bool cut[N];
int dfn[N], low[N], S[N], top, cnt, no;
void DCC(int u, int rt) {
    dfn[u] = low[u] = ++no;
    S[top++] = u;
    if (e[u].empty()) { Dcc[++cnt].pb(u); return ; }
    int son = 0;
    for (auto v : e[u]) {
        if (!dfn[v]) {
            DCC(v, rt);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                son++;
                if (u != rt || son > 1) cut[u] = 1;
                cnt++;
                do { Dcc[cnt].pb(S[--top]); } while (S[top] != v);
                Dcc[cnt].pb(u);
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

vi e2[N];
int id[N], dcc[N];
void run(int n) {
    no = top = cnt = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(cut, 0, sizeof(cut));
    rep(i, 1, n+1) Dcc[i].clear();
    rep(i, 1, n+1) if (!dfn[i]) DCC(i, i);
    int num = cnt;
    rep(i, 1, n+1) if (cut[i]) id[i] = ++num;
    rep(i, 1, cnt+1) for (auto o : Dcc[i]) {
        if (cut[o]) { e2[i].pb(id[o]); e2[id[o]].pb(i); }
        else dcc[o] = i;
    }
}

bool odd_cir;
int vis[N], col[N], able[N];
int dfs(int u, int color, int id) {
    col[u] = color;
    for (auto v : e[u]) if (vis[v] == id) {
        if (!col[v]) dfs(v, 3-color, id);
        else if (col[v] == color) return odd_cir = 1;
    }
    return 0;
}

void Init() {
    memset(vis, 0, sizeof(vis));
    memset(able, 0, sizeof(able));
    memset(g, 0, sizeof(g));
    rep(i, 0, n+1) e[i].clear();

    rep(i, 0, m) {
        int u, v; scanf("%d%d", &u, &v);
        g[u][v] = g[v][u] = 1;
    }
    rep(i, 1, n) rep(j, i+1, n+1) if (!g[i][j]) { e[i].pb(j); e[j].pb(i); }
}

int Solve() {
    run(n);
    
    rep(i, 1, cnt+1) {
        for (auto o : Dcc[i]) vis[o] = i, col[o] = 0;
        odd_cir = 0;
        dfs(Dcc[i][0], 1, i);
        if (!odd_cir) continue;
        for (auto o : Dcc[i]) able[o] = 1;
    }
    int ans = 0;
    rep(i, 1, n+1) if (!able[i]) ans++;
    return printf("%d\n", ans);
}

// ------- main ------- //

int main ()
{
    while (~scanf("%d%d", &n, &m)) {
        if (n == 0) break;
        Init();
        Solve();
    }
    return 0;
}
```



---

<div STYLE="page-break-after: always;"></div>
## Greedy / 贪心

### 线段覆盖

- **CF115E** 

**题意** 

n 个点， m 个线段，每个点有代价，每个线段有收益，求选若干个线段使获益最大。

**题解**

首先假设所有线段都取，获得所有收益。

枚举 n 个点，对所有覆盖这个点的线段，优先取右端点靠左的线段。

对于每一个点，看当前线段的收益是否足够支付这个点的代价。

如果够，把线段扣去相应的代价，并在之后接着考虑，这个点的代价就变为 0 ，接下来其他覆盖这个点的线段就不用再支付代价。

如果不够，相当于不用这个线段，扣掉对应收益，全都扣掉就相当于没取过这个线段。当这个点代价太大，使得覆盖这个点的线段都被扣掉，其实相当于不取这个点，自然也不用支付这个点的代价。

**代码**

```c++
/* <<head>> */
const int N = (int)2e5+7;

// ------- 变量 ------- //

int n, m, cost[N];
vector <pii> seg[N];
ll ans = 0;

// ------- 函数 ------- //

void Init() {
    rep(i, 1, n+1) seg[i].clear();

    ans = 0;
    rep(i, 1, n+1) scanf("%d", cost+i);
    rep(i, 1, m+1) {
        int l, r, val;
        scanf("%d%d%d", &l, &r, &val);
        seg[l].pb(mp(r, val));
        ans += val;
    }
}

int Solve() {
    priority_queue < pii, vector<pii>, greater<pii> > Q;  // 优先右端点近的
    rep(i, 1, n+1) {  // 枚举每个点
        
        // 之前不覆盖当前点的线段出队
        while (!Q.empty() && Q.top().fi < i) Q.pop();
        
        for (auto o : seg[i]) Q.push(o);  // 覆盖当前点的新线段入队
        
        while (!Q.empty() && cost[i]) {  // 当前这个点的代价还未支付完
            auto fron = Q.top(); Q.pop();
            int val = fron.se;
            int mi = min(val, cost[i]);
            cost[i] -= mi;
            val -= mi;
            ans -= mi;
            
            // 如果当前线段的收益足够支付代价，且还有剩余，则再次入队供之后的点考虑
            if (val) Q.push(mp(fron.fi, val));
        }
    }
    return printf("%lld\n", ans);
}

// ------- main ------- //

int main ()
{
    while (~scanf("%d%d", &n, &m)) {
        Init();
        Solve();
    }
    return 0;
}
```



---

<div STYLE="page-break-after: always;"></div>
## Number theory / 数论

### 数论基础

#### 数论函数

**定义**

定义域为正整数的函数。

#### 积性函数

**定义** 

若 $gcd(n,m) = 1$ ，有 $f(n * m) = f(n) * f(m)$ ，则称数论函数 $f(x)$ 为积性函数。

特别地：
$$
\large 若\ n=p_1^{e_1}p_2^{e_2}...p_k^{e_k} \\
\large 则\ f(n)=f(p_1^{e_1})f(p_2^{e_2})...f(p_k^{e_k})
$$

**完全积性函数** 

若对任意正整数 $n$ 和 $m$ ，有 $f(n * m) = f(n) * f(m)$ ，则称数论函数 $f(x)$ 为完全积性函数。

**性质**

1. 若 $f(x)$ 非恒等于 $0$ ，则有 $f(1)=1$ 
2. 若 $f(x)$ 和 $g(x)$ 都是积性函数，则 $f(x) * g(x)$ 也是积性函数
3. 若 $f(x) * g(x)$ 和 $g(x)$ 都是积性函数，则 $f(x)$ 也是积性函数

**常见积性函数**

- $1(x)=1$  
- $f(x)=x$ 
- 欧拉函数： $\phi(x)$ 
- 莫比乌斯函数： $\mu(x)$ 




#### 狄利克雷卷积

**定义**
$$
\Large h(n) = \sum_{d|n}f(d)g(\frac{n}{d})
$$
也可表示为
$$
\Large h(n) = \sum_{ab=n}f(a)g(b)
$$
简记为 $h(n) = f(n) * g(n)$ 

**性质**

1. 满足结合律
2. 满足交换律
3. 若 $f(x)$ 和 $g(x)$ 都是积性函数，则 $f(x) * g(x)$ 也是积性函数
4. 若 $f(x) * g(x)$ 和 $g(x)$ 都是积性函数，则 $f(x)$ 也是积性函数



---



### 莫比乌斯函数

**定义**
$$
\mu(1)=1\\
\mu(n)=\mu(p_1^{q_1})\mu(p_2^{q_2})...\mu(p_k^{q_k})=\begin{cases}(-1)^k\quad 当\ q_1 = q_2 = ... =q^k=1\\0\qquad\ \ \ \  其他\end{cases}
$$
**解释**

对于 x ，其质因数序列，如果有某个质因数指数大于 1 ，则 $\mu(x) = 0$ 

否则，若有奇数个质因数，则 $\mu(x) = -1$ 

若有偶数个质因数，则 $\mu(x)=1$ 



#### 莫比乌斯反演

穷举 n 的约数 d ：
$$
F(n)=\sum_{d|n}f(d) \\
f(n)=\sum_{d|n}\mu(d)F(\frac{n}{d})
$$
穷举 n 的倍数 d :
$$
F(n)=\sum_{n|d}f(d) \\
f(n)=\sum_{n|d}\mu(d)F(\frac{d}{n})
$$

**模板** 

```c++
memset(mu, 0, sizeof(mu));
mu[1] = 1;
rep(i, 1, m+1) for (int j = i+i; j <= m; j += i) mu[j] -= mu[i];
```



**例题 : CF1139D** 

**题意**

给定一个 m ，每次在 1 到 m 中随机取一个数加入序列中，当序列的 gcd 为 1 时停止，求序列期望长度。

**题解**

$$E(X)$$ 表示序列的 gcd > 1 的期望长度。

$$E(X)=\sum_{i\ge 1}P(X\ge i)$$ 

$$P(X\ge i)$$ 表示序列的 gcd > 1 且序列长度大于等于 i 的概率。



$$P(X\ge i) = P(X\ge i|gcd=2) + P(X\ge i | gcd=3) + P(X\ge i|gcd=4) + ...$$ 

$$= P(X\ge i|gcd 是 2 的倍数) + P(X\ge i|gcd是3的倍数) + P(X\ge i|gcd 是 5 的倍数)+...$$ 

$$- P(X\ge i|gcd 是 2和3 的倍数) - P(X\ge i|gcd是2和5的倍数) - P(X\ge i|gcd 是3和5的倍数)-...$$ 

$$+ P(X\ge i|gcd 是 2、3、5的倍数)+...$$ 



令 $g(x)$ 表示 $P(X\ge i|gcd=x)$ ， $G(x)$ 表示 $P(X\ge i|gcd是x的倍数)$ 

则

$$G(n) = \sum_{n|d}g(d)$$ 

$$P(X\ge i) = g(2) + g(3) + g(4) + ... = 1 - g(1)$$ 

根据莫比乌斯反演，则 $$g(1) = \sum_{1|d}\mu(d)G(\frac{d}{1}) = \sum_{d\ge1}\mu(d)G(d)$$ 

则 $$P(X\ge i) = 1 - \sum_{d\ge1}\mu(d)G(d)$$ 



令 $$p(x)$$ 表示随机选取一个数，且该数是 x 的倍数的概率，则 $$\large p(x) = \frac{m / x}{m}$$ 

则 $$G(x) = p^i(x)$$ 



则
$$
E(X) = \sum_{i\ge1}P(X\ge i) = \sum_{i\ge1}[1 - \sum_{d\ge1}\mu(d)G(d)]= \sum_{i\ge1}[1 - \sum_{d\ge1}\mu(d)p^i(d)]\\
因为\quad \mu(1)p^i(1) = 1\qquad
所以\quad E(X)=-\sum_{i\ge1}\sum_{d\ge2}\mu(d)p^i(d)=-\sum_{d\ge2}\mu(d)\sum_{i\ge1}p^i(d)\\
因为当\ d>m\ 时，p^i(d) = 0\qquad 所以\quad E(X)=-\sum_{d\ge2}^m\mu(d)\sum_{i\ge1}p^i(d)\\
又根据等比数列求和，\sum_{i\ge1}p^i(d) = \frac{p(d)}{1-p(d)}
$$
所以
$$
ans = E(X)+1 = 1-\sum_{d\ge2}^{m}\mu(d)\frac{p(d)}{1-p(d)}
$$

**代码** 

```c++
/* <<head>> */
const int MOD = (int)1e9+7;
const int N = (int)1e5+7;
 
// ------- 变量 ------- //
 
int m;
int mu[N];
 
// ------- 函数 ------- //
 
void Init() {
    mu[1] = 1;
    rep(i, 1, m+1) for (int j = i+i; j <= m; j += i) mu[j] -= mu[i];
}
 
inline int add(int a, int b) { return (a += b) >= MOD ? a - MOD : a; }
inline int mul(int a, int b) { return 1ll * a * b % MOD; }
int powmod(ll a, ll b) { ll res = 1; for (a %= MOD; b; b >>= 1) { if (b & 1) res = mul(res, a); a = mul(a, a); } return res; }
inline int p(int x) { return mul(m / x, powmod(m, MOD-2)); }
 
int Solve() {
    int ans = 1;
    rep(i, 2, m+1) {
        ans = add(ans, MOD-mul((mu[i]+MOD)%MOD, mul(p(i), powmod(MOD+1-p(i), MOD-2))));
    }
    return printf("%d\n", ans);
}
 
// ------- main ------- //
 
int main ()
{
    while (~scanf("%d", &m)) {
        Init();
        Solve();
    }
    return 0;
}
```



---

<div STYLE="page-break-after: always;"></div>
## Sortings / 排序

### 中位数

- **七夕祭 BZOJ3032** 

**问题模型：货仓选址、均分纸牌、环形均分纸牌** 



1. **货仓选址 CH0501** 

**题意** 

数轴上 $n$ 家商店，坐标为 $a[i]$ ，选一点 $x$ 使得所有商店到 $x$ 的距离之和最小。

**题解** 

对于坐标 $x$ ，左边商店比右边商店多时，向左移动会减少距离和，反之同理。因此，最优解即左右商店数量一样多。即 $x$ 应选在中位数处。

当商店数量为偶数时， $x$ 选在 $a[n/2]$ 和 $a[n/2+1]$ 之间；当商店数量为奇数时， $x$ 选在 $a[(n+1)/2]$ 。



2. **均分纸牌** 

**题意**

$n$ 个人，每人 $a[i]$ 张牌，每一步可以让某个人将一张纸牌交给相邻的人，求最少操作步数使得每人手牌数相等。

**题解** 

当纸牌总数 $T$ 能被 $n$ 整除时，问题有解：
$$
ans = \sum_{i=1}^n|i*\frac{T}{n}-G[i]|\qquad G[i] = \sum_{j=1}^iC[j]
$$
前 $i$ 个人共有 $G[i]$ 张牌，最终会有 $i * T / n$ 张牌，多退少补，与后 $n - i$ 个人发生二者绝对值之差的交换。

设 $A[i] = C[i] - T / n$ ，即一开始每个人先减掉应有的 $T / n$ 张牌，最终要让每个人都恰好有 $0$ 张牌。
$$
ans = \sum_{i=1}^n|S[i]|\qquad S[i] = \sum_{j=1}^iA[j]
$$



3. **环形均分纸牌** 

**题意** 

题意同上，第 $1$ 个人可和第 $n$ 个人传递纸牌。

**题解** 

一定存在最优解，使得某两个相邻的人之间没有传递纸牌。问题转化为一般的均分纸牌。

第 $1$ 个人和第 $n$ 个人之间断开： （$S'[i]$ 表示从断点处开始的前缀和）
$$
S'[i] = S[i]
$$
第 $k$ 个人和第 $k+1$ 个人之间断开：
$$
S’[i] = 
\begin{cases}
S[i] - S[k]\qquad\qquad i > k\\
S[i] + S[n] - S[k]\quad i <= k
\end{cases}\\
$$
因为 $S[n] = 0$ ，所以：
$$
S'[i] = S[i] - S[k]
$$
 所以：
$$
ans = \sum_{i=1}^n|S'[i]| = min\{\ \sum_{i=1}^n|S[i]-S[k]|\quad k\in[1, n]\ \}
$$
此问题即为 “货仓选址” 问题，将 $S$ 从小到大排序，取中位数作为 $S[k]$ 即为最优解。



- **七夕祭 BZOJ3032** 

**题意** 

n 行 m 列的矩阵，有若干黑色格子，至少交换多少次相邻的格子，使得每行黑格子一样多，每列黑格子也一样多。

**题解** 

行列交换互相独立。

交换即为 “环形均分纸牌” 。

**代码** 

```c++
/* <<head>> */
const int N = (int)1e5+7;

// ------- 变量 ------- //

int n, m, t;
int x[N], y[N];
int a[N], s[N];

// ------- 函数 ------- //

void Init() {
    rep(i, 0, t) scanf("%d%d", x+i, y+i);
}

int Solve() {
    bool row = !(t % n), col = !(t % m);
    switch (row << 1 | col) {
        case 0 : return puts("impossible");
        case 1 : printf("column "); break;
        case 2 : printf("row "); break;
        case 3 : printf("both "); break;
    }
    ll ans = 0;
    if (row) {
        int num = t / n;
        memset(a, 0, sizeof(a));
        rep(i, 0, t) a[x[i]]++;
        rep(i, 1, n+1) a[i] -= num;
        rep(i, 1, n+1) s[i] = s[i-1] + a[i];
        sort(s + 1, s + n + 1);
        int k = s[n/2+1];
        rep(i, 1, n+1) ans += abs(s[i] - k);
    }
    if (col) {
        int num = t / m;
        memset(a, 0, sizeof(a));
        rep(i, 0, t) a[y[i]]++;
        rep(i, 1, m+1) a[i] -= num;
        rep(i, 1, m+1) s[i] = s[i-1] + a[i];
        sort(s + 1, s + m + 1);
        int k = s[m/2+1];
        rep(i, 1, m+1) ans += abs(s[i] - k);
    }
    return printf("%lld\n", ans);
}

// ------- main ------- //

int main ()
{
    while (~scanf("%d%d%d", &n, &m, &t)) {
        Init();
        Solve();
    }
    return 0;
}
```



---

<div STYLE="page-break-after: always;"></div>
## String / 字符串

### KMP

**例题 : CF825F** 

**题意**

给一字符串，可进行压缩，如： aaaaa 可压缩成 5a ，求最短压缩后长度。

**题解**

dp[i] 表示前 i 个字符的最短长度。

dp[i] = min(dp[i], dp[j] + cost\[i][j])

cost\[i][j] 表示子串 [i, j] 的最小循环节长度 + 循环节个数的数字长度

枚举字符串后缀，用 KMP 可以求出当前后缀的所有前缀的最小循环节，即：

用 KMP 求出所有区间的 cost\[i][j]

**代码**

```c++
/* <<head>> */
const int N = (int)8e3+7;

// ------- 变量 ------- //

char s[N];
int len, dig[N], cost[N][N], dp[N];

// ------- 函数 ------- //

int net[N];
void Get(char *p, int m) {
    net[0] = -1;
    for (int i = 0, j = -1; i < m;) {
        if (j == -1 || p[i] == p[j]) net[++i] = ++j;
        else j = net[j];
    }
    // 最小循环节长度 ( m 也可以是当前字符串的前缀长度，求前缀字符串的最小循环节 )
    // if (m % (m - net[m]) == 0) return m - net[m]; else return m;
    // 最小循环节个数
    // if (m % (m - net[m]) == 0) return m / (m - net[m]); else return 1;
}

void Init() {
    rep(i, 1, N) dig[i] = dig[i/10] + 1;
    len = strlen(s + 1);
    rep(i, 1, len+1) {  // 枚举后缀
        Get(s + i, len-i+1);  // 将后缀进行 KMP 处理，求 net 数组
        rep(j, i, len+1) {  // 枚举后缀的前缀，即枚举所有子区间 [i, j]
            if (j == i) cost[i][j] = 2;
            else {
                int tlen = j - i + 1;  // 前缀长度，即区间长度
                if (tlen % (tlen - net[tlen]) == 0) {
                    int cnt = tlen / (tlen - net[tlen]);
                    cost[i][j] = dig[cnt] + tlen - net[tlen];
                } else {
                    cost[i][j] = 1 + tlen;
                }
            }
        }
    }
}

int Solve() {
    rep(i, 1, len+1) {
        dp[i] = cost[1][i];
        rep(j, 1, i) dp[i] = min(dp[i], dp[j] + cost[j+1][i]);
    }
    return printf("%d\n", dp[len]);
}

// ------- main ------- //

int main ()
{
    while (~scanf("%s", s + 1)) {
        Init();
        Solve();
    }
    return 0;
}
```



---



### 字典树

**例题 : CF1129C** 

**题意**

1 至 4 位 01 串可代表一个字母，注意， 01 串位数不同，代表的字母就不同，即 0011 和 11 代表不同字母。并且 0011 、 0101 、 1110 、 1111 不代表字母。

逐次添加一位 0 或 1 ，问当前 01 串的所有子串可表示的字符串种类数。

**题解**

每次操作，反向将当前字符串插入字典树，字典树上每个节点到根节点形成的子串代表一个独特的子串，每个节点保存该节点代表的子串所能形成的字符串种数，通过 dp 转移。

因为一个字母最多由 4 位组成，所以新节点最多向上枚举 4 位，表示在确定形成当前这个字母时，祖先节点形成的 01 串能形成多少种字符串，累加进新节点的 dp 值。

每生成一个新节点，便将新节点对应 dp 值累加进答案。

**代码**

```c++
/* <<head>> */
const int MOD = (int)1e9+7;
const int N = (int)3e3+7;

// ------- 变量 ------- //

int n, s[N], ans;
int no, trie[N*N][2], fa[N*N];
int dp[N*N];

// ------- 函数 ------- //

int newnode() { ++no; memset(trie[no], 0, sizeof(trie[no])); return no; }

// 反向将后缀插入字典树，可以看做所有后缀统一在根节点汇聚
// 每个节点到根节点形成的子串代表一个独特的子串
void Insert(int len) {
    int rt = 0;
    per(i, 1, len+1) {
        int id = s[i];
        if (!trie[rt][id]) {
            int num = trie[rt][id] = newnode();
            fa[num] = rt;
            
            int t = rt, val = 0;
            rep(j, 0, 4) {
                
                // 判断 num 节点向上 4 位形成的字母是否合法
                val = val << 1 | s[i+j];
                if (j == 3 && (val == 3 || val == 5 || val == 14 || val == 15)) break;

                // dp[num] 表示从 num 节点到根形成的子串能构造的字符串种数
                // dp[num] 可从最多四个祖先转移过来
                // 表示 num 节点向上至多 4 位形成一个字母，
                // 然后上面的所有祖先节点所能形成的所有字符串种数 dp[t]
                dp[num] = (dp[num] + dp[t]) % MOD;
                if (t) t = fa[t]; else break;
            }
            ans = (ans + dp[num]) % MOD;  // 每当有一个新节点，就更新答案
        }
        rt = trie[rt][id];
    }
}

void Init() {
    no = -1; newnode();
    dp[0] = 1;
    ans = 0;
}

int Solve() {
    rep(i, 1, n+1) {
        scanf("%d", s+i);
        Insert(i);  // 反向将当前 01 串插入字典树
        printf("%d\n", ans);
    }
    return 0;
}

// ------- main ------- //

int main ()
{
    while (~scanf("%d", &n)) {
        Init();
        Solve();
    }
    return 0;
}
```



---



**例题 : CF1084E** 

**题意** 

给定两个字符串 s 和 t ，保证 s 和 t 的长度都为 n ，只由 'a' 和 'b' 构成，且 s 的字典序小于等于 t ，要求在 [s, t] 中选择不超过 k 个字符串，使得这些字符串的所有前缀的种数尽可能多。

**题解** 

在字典树上， s 和 t 形成左右边界，即求在这个边界内，选择不超过 k 个叶子节点，使得这几条树链的结点总数尽可能多。

模拟根节点扩展过程，累加节点数，直到节点数大于等于 k 时，后面的答案可以一次统计。

**代码** 

```c++
/* <<head>> */
const int N = (int)5e5+7;

// ------- 变量 ------- //

int n, k;
char s[N], t[N];

// ------- 函数 ------- //

void Init() {
}

int Solve() {
    int pos = 0; ll ans = 0;
    while (pos < n && s[pos] == t[pos]) pos++, ans++;  // 相同前缀
    ll leaf = 1;
    for (; pos < n; pos++) {
        leaf <<= 1;
        if (s[pos] == 'b') leaf--;  // 边界的节点没有扩展
        if (t[pos] == 'a') leaf--;
        if (leaf >= k) {
            ans += 1ll * (n - pos) * k;  // 当前叶子达到 k 个，后面都是单链
            break;
        } else {
            ans += leaf;
        }
    }
    return printf("%lld\n", ans);
}

// ------- main ------- //

int main ()
{
    while (~scanf("%d%d%s%s", &n, &k, s, t)) {
        Init();
        Solve();
    }
    return 0;
}
```



<div STYLE="page-break-after: always;"></div>
