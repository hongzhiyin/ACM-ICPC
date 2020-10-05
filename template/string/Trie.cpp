/* ----- 字典树 ----- */

struct node {                                                   // 字典树节点
    vector<node*> next;                                         // 节点分支
    bool isword;                                                // 从根节点到当前节点是否是一个完整单词
    node(int fork) {                                            // 新建一个 fork 个分支的节点
        next = vector<node*>(fork, nullptr);                    // fork 个分支初始为空指针
        isword = 0;                                             // 标记位清零
    }
};

struct Trie {
    typedef node *Iter;
    Iter root;                                                      // 根节点指针
    int fork;                                                       // 节点分支数
    Trie(int fork) : fork(fork) { root = new node(fork); }          // 初始化，建立根节点

    void insert(string &s) {                                        // 插入单词
        node *cur = root;                                           // 临时指针
        for (auto ch : s) {                                         // 遍历每个字母
            int id = ch - 'a';                                      // 字母对应 id
            if (!cur->next[id]) cur->next[id] = new node(fork);     // 如果分支为空指针，建立新节点
            cur = cur->next[id];                                    // 指针指向下一个节点
        }
        cur->isword = true;                                         // 设置标记位
    }
};
