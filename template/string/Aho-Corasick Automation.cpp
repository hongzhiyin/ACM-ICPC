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
