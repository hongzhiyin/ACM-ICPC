void Init() {
    memset(trie, 0, sizeof(trie));
    node_tot = 0;
}

int node_tot;
int trie[N][128], fail[N], isw[N], que[N];    // N = 单词个数 * 单词长度，第二维视情况而定
struct AhoCorasick {
    int newnode() {
        ++node_tot;
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
                if (trie[cur][i]) {
                    int p = fail[cur];
                    while (p && !trie[p][i]) p = fail[p];
                    fail[trie[cur][i]] = (!cur ? 0 : trie[p][i]);
                    que[tail++] = trie[cur][i];
                } else {
                    trie[cur][i] = trie[fail[cur]][i];
                }
            }
        }
    }
    void run(char *s) {
        int len = strlen(s), rt = 0;
        rep(i, 0, len) {
            int id = s[i], f = 1;
            while (!trie[rt][id]) {
                if (rt == 0) { f = 0; break; }
                rt = fail[rt];
            }
            if (!f) continue;
            int tmp = rt = trie[rt][id];
            while (tmp) {
                if (isw[tmp]) cnt[isw[tmp]]++;      // 统计单词出现次数
                tmp = fail[tmp];
            }
        }
    }
};
