void Init() {
    node_tot = -1; obj.newnode();
}

int node_tot;
int trie[N][128], fail[N], isw[N], last[N], que[N];
// N = 单词个数 * 单词长度，第二维视情况而定  last[] 表示上一个是单词结尾的失配位置
struct AhoCorasick {
    int newnode() {
        ++node_tot;
        memset(trie[node_tot], 0, sizeof(trie[node_tot]));
        fail[node_tot] = 0;
        isw[node_tot] = 0;
        return node_tot;
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

// ------------------------------------------------------------------------------- //

// poj 2778
// 求不包含所给单词表中的单词且长度为 n 的字符串个数
// AC 自动机 + 矩阵快速幂
// AC 自动机构建状态转移图，通过状态转移构建有向图的邻接矩阵，通过矩阵快速幂计算两点之间长度为 n 的路径数目

int node_tot;
int trie[N][4], fail[N], isw[N], que[N];
struct AhoCorasick {
    int newnode() {
        ++node_tot;
        memset(trie[node_tot], 0, sizeof(trie[node_tot]));
        fail[node_tot] = 0;
        isw[node_tot] = 0;
        return node_tot;
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
            if (isw[fail[cur]]) isw[cur] = 1;
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
        rep(i, 0, node_tot+1) rep(j, 0, 4)      // 遍历节点编号，即遍历所有状态
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
	    rep(k, 0, nm)
        	r.a[i][j] = a[i][k] * b.a[k][j];    // 取模运算十分耗时，尽可能最后再取模
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
    node_tot = -1; obj.newnode();
    
    while (n--) {
        scanf("%s", str);
        obj.insert(str);        // 构建字典树，标记不可转移状态
    }
    obj.build();        // 构建失配指针，标记不可转移状态
    obj.run();          // 构建邻接矩阵， mat[i][j] 表示第 i 号状态到第 j 号状态有 mat[i][j] 条长度为 1 的路
}
int Solve() {
    a = Mat(node_tot+1, node_tot+1);
    rep(i, 0, node_tot+1) rep(j, 0, node_tot+1)
        a.a[i][j] = mat[i][j];
    a = a ^ m;          // 长度为 m 的路径矩阵
    int ans = 0;
    rep(i, 0, node_tot+1) ans += a.a[0][i];     // 从根节点出发到各个状态（包括自己）的长度为 m 的路径总数
    return !printf("%d\n", ans % MOD);
}
