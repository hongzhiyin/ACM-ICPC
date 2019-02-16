// https://www.cnblogs.com/TheRoadToTheGold/p/6290732.html
// 在单词表中查找单词或前缀

int no, trie[N * len][k];    // 字母种类 : k ; 单词长度 : len ; 单词个数 : N
int newnode() {
    ++no;
    memset(trie[no], 0, sizeof(trie[no]));
    // isw[no] = 0;
    // sum[no] = 0;
    return no;
}
void Clear() { no = -1; newnode(); }    // 使用前注意先用 Clear() 初始化
void insert(char *s) {     // 插入单词 s
    int len = strlen(s), rt = 0;   // 根节点编号为 0
    rep(i, 0, len) {
        int id = s[i] - 'a';
        if(!trie[rt][id]) trie[rt][id] = newnode();  // 如果之前没有从 rt 到 id 的前缀，插入新节点
        rt = trie[rt][id];      // 顺着字典树往下走
        // sum[rt]++;       // 保存前缀出现次数
    }
    // isw[rt] = true;      // 标志该单词末位字母的尾结点，在查询整个单词时用到
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
