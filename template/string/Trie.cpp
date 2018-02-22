void Init()
{
    memset(trie, 0, sizeof(trie));
    int tot = 0;
}

void insert()//插入单词s
{
    int len = strlen(s);//单词s的长度
    int root = 0;//根节点编号为0
    rep(i, 0, len) {
        int id = s[i]-'a';//第二种编号
        if(!trie[root][id])//如果之前没有从root到id的前缀 
            trie[root][id] = ++tot;//插入，tot即为第一种编号
        root = trie[root][id];//顺着字典树往下走
        //sum[root]++;//前缀后移一个位置保存
    }
    /*isw[rt]=true;标志该单词末位字母的尾结点，在查询整个单词时用到*/
}

bool find()
{
    int len=strlen(s), root = 0;//从根结点开始找
    rep(i, 0, len) {
        int x = s[i] - 'a';
        if( !trie[root][x]) return false; 
        root = trie[root][x];//为查询下个字母做准备，往下走 
    }
    return true;//找到了
    //查询整个单词时，应该return isw[rt] 
    //return sum[root]; 因为前缀后移了一个保存，所以此时的sum[root]就是要求的前缀出现的次数 
}
