// https://www.cnblogs.com/TheRoadToTheGold/p/6290732.html

int trie[N][26];
void Init() {
    memset(trie, 0, sizeof(trie));
    int node_tot = 0;
}

struct Trie {
    void insert(char *s) {     // 插入单词 s
        int len = strlen(s), rt = 0;   // 根节点编号为 0
        rep(i, 0, len) {
            int id = s[i] - 'a';
            if(!trie[rt][id]) trie[rt][id] = ++node_tot;  // 如果之前没有从 rt 到 id 的前缀，插入新节点
            rt = trie[rt][id];      // 顺着字典树往下走
            // sum[rt]++;     // 保存前缀出现次数
        }
        // isw[rt] = true; 标志该单词末位字母的尾结点，在查询整个单词时用到
    }
    bool find(char *s) {
        int len = strlen(s), rt = 0;  // 从根结点开始找
        rep(i, 0, len) {
            int id = s[i] - 'a';
            if(!trie[rt][id]) return false; 
            rt = trie[rt][id];      // 为查询下个字母做准备，往下走 
        }
        return true;            // 作为前缀出现
        // return isw[rt];      // 是否作为完整的单词出现过
        // return sum[rt];      // 前缀出现的次数 
    }
};
