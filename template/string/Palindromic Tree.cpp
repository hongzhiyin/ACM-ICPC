// 国家集训队论文 2017 《回文树及其应用》 翁文涛
// https://blog.csdn.net/u013368721/article/details/42100363
// https://blog.csdn.net/qq_38995588/article/details/80644655

// N: 字符串长度 , C: 字符种类数
// t[i][c]: 每个节点 i 表示一个回文串， t[i][c] 表示在回文串 i 两边加上字符 c 形成的新的回文串
// fail[i]: 指向节点 i 的最长真后缀回文串
// cnt[i]:  节点 i 表示的本质不同的回文串的个数（建树时求出的不是完全的，最后跑一遍 count() 后才是正确的）
// flen[i]: 节点 i 的 fail 链的长度
// len[i]:  节点 i 表示的回文串的长度
// s[i]:    第 i 次加入的字符， s[0] = -1
// last:    指向新添加一个字符后所形成的最长回文串表示的节点
// sno:     添加的字符个数
// no:      节点个数
struct Palindromic_Tree {
    int t[N][C], fail[N], cnt[N], flen[N], len[N], s[N], last, sno, no;
    int newnode (int l) {
        rep(i, 0, C) t[no][i] = 0;
        cnt[no] = flen[no] = 0;
        len[no] = l;
        return no++;
    }
    void init () {    // 初始化
        no = last = 0;
        newnode(0); newnode(-1);
        s[sno=0] = -1;
        fail[0] = 1;
    }
    int get_fail(int x) {
        while (s[sno-len[x]-1] != s[sno]) x = fail[x];
        return x;
    }
    void add(int c) {
        c -= 'a';
        s[++sno] = c;
        int cur = get_fail(last);
        if (!t[cur][c]) {
            int now = newnode(len[cur] + 2);
            fail[now] = t[get_fail(fail[cur])][c];
            t[cur][c] = now;
            flen[now] = flen[fail[now]] + 1;
        }
        last = t[cur][c];
        cnt[last]++;
    }
    void count() { per(i, 0, no) cnt[fail[i]] += cnt[i]; }
};

================================================== Problem Set ==================================================

// bzoj 3676
// 题意：求一个字符串中所有回文字串的出现次数与长度乘积的最大值
int Solve() {
    obj.init();   // 初始化
    int len = strlen(s);
    rep(i, 0, len) obj.add(s[i]);
    obj.count();  // 计算 cnt
    
    ll ans = 0;
    rep(i, 2, obj.no) ans = max(ans, (ll)obj.len[i] * obj.cnt[i]);
    return printf("%lld\n", ans);
}

----------------------------------------------------------------------------------------------------

// uva 7041
// 题意：对于 A 中的每个回文子串，求 B 中和该子串相同的子串个数的总和
// 题解：从 0 和 1 两个根节点 DFS 下去，如果两个相同的节点同时存在就统计答案
ll dfs(int a, int b) {
    ll res = 0;
    rep(i, 0, C) if (obj1.t[a][i] != 0 && obj2.t[b][i] != 0)
        res += (ll)obj1.cnt[obj1.t[a][i]] * obj2.cnt[obj2.t[b][i]]
                + dfs(obj1.t[a][i], obj2.t[b][i]);
    return res;
}
int Solve() {
    scanf("%s%s", s1, s2);
    obj1.init(); obj2.init();
    int len1 = strlen(s1), len2 = strlen(s2);
    rep(i, 0, len1) obj1.add(s1[i]);
    rep(i, 0, len2) obj2.add(s2[i]);
    obj1.count(); obj2.count();
    ll ans = dfs(0, 0) + dfs(1, 1);
    return printf("%lld\n", ans);
}

----------------------------------------------------------------------------------------------------

// uestc 1999
// 题意：初始一个空串 s ，根据 op 中的字母来对 s 进行操作，末尾添加字符或末尾删除字符，求每次操作完以后 s 中回文串的个数
// 题解：每次都建一颗回文树
int Solve() {
    int l = 0;
    rep(i, 0, n) {
        if (op[i] == '-') l--;
        else s[l++] = op[i];
        obj.init();
        rep(j, 0, l) obj.add(s[j]);
        obj.count();
        rep(j, 2, obj.no) ans[i] += obj.cnt[j];
    }
    rep(i, 0, n) printf("%d%c", ans[i], " \n"[i==n-1]);
    return 0;
}

----------------------------------------------------------------------------------------------------

// ural 1960
// 题意：每加一个字符，统计本质不同的回文串个数
int Solve() {
    obj.init();
    int len = strlen(s);
    rep(i, 0, len) {
        obj.add(s[i]);
        printf("%d%c", obj.no - 2, " \n"[i==len-1]);
    }
    return 0;
}

----------------------------------------------------------------------------------------------------

// http://www.tsinsen.com/A1280
// 题意：找到最长的串 XY ， X 为长度非 0 的回文串， Y 为长度非 0 的回文串
// 题解：枚举以 i 为结尾的最长回文长度和以 i 为开头的最长回文长度
int Solve() {
    obj.init();
    int len = strlen(s);
    rep(i, 0, len) {
        obj.add(s[i]);
        pre[i] = obj.len[obj.last];
    }
    int ans = 0;
    obj.init();
    per(i, 1, len) {
        obj.add(s[i]);
        suf[i] = obj.len[obj.last];
        ans = max(ans, pre[i-1] + suf[i]);
    }
    return printf("%d\n", ans);
}

----------------------------------------------------------------------------------------------------

// http://www.tsinsen.com/A1255
// 题意：找出字符串中长度为奇数的回文子串，按长度降序排序，求前 k 个回文子串的长度的乘积
// 题解：统计奇数长度的回文子串总个数，分别存在下标表示长度的数组中，从大到小遍历长度，用快速幂计算 len 的 cnt 次方
int Solve() {       // 注意子串个数是否需要用 long long
    obj.init();
    rep(i, 0, n) obj.add(s[i]);
    obj.count();
    rep(i, 2, obj.no) if (obj.len[i] & 1) {
        lcnt[obj.len[i]] += obj.cnt[i];
        sum += obj.cnt[i];
    }
    if (sum < k) return puts("-1");
    ll ans = 1;
    for (int i = n & 1 ? n : n-1; i >= 1; i -= 2) {
        if (lcnt[i] < k) {
            ans = mul(ans, powmod(i, lcnt[i]));
            k -= lcnt[i];
        } else {
            ans = mul(ans, powmod(i, k));
            break;
        }
    }
    return printf("%lld\n", ans);
}
