// IOI 2009 国家集训队论文 罗穗骞《后缀数组——处理字符串的有力工具》

/*
【使用方法】
1. 读取字符串，将字符串转换为数字存在 s[] 中
2. 调用 calsa() 获得 sa[]
3. 调用 calheight() 获得 rk[] , height[]
*/

// sa[i] 表示排在第 i 位的是后缀 sa[i], 注意：因为 s[len] = 0, 所以 sa[0] = len
// rk[i] 表示后缀 i 排在第 rk[i] 位
// height[i] = LCP(sa[i], sa[i-1]), LCP: 最长公共前缀
int s[N], len, id[N];
int sa[N], rk[N], height[N];
int wa[N], wb[N], wc[N], wd[N];    // 不要问这些数组是什么意思，因为我也不知道，抄就对了
struct SuffixArray {
    int cmp(int *s, int a, int b, int l) { return s[a] == s[b] && s[a+l] == s[b+l]; }
    void calsa(int *s, int n, int m) {     // s[len] = 0, n = len + 1, m 为字符种类 ( m = 128 + d )
        int *x = wa, *y = wb, *t;
        rep(i, 0, m) wc[i] = 0;
        rep(i, 0, n) wc[x[i]=s[i]]++;
        rep(i, 1, m) wc[i] += wc[i-1];
        per(i, 0, n) sa[--wc[x[i]]] = i;
        for(int j = 1, p = 1; p < n; j <<= 1, m = p) {
            p = 0; rep(i, n-j, n) y[p++] = i;
            rep(i, 0, n) if(sa[i] >= j) y[p++] = sa[i] - j;
            rep(i, 0, n) wd[i] = x[y[i]];
            rep(i, 0, m) wc[i] = 0;
            rep(i, 0, n) wc[wd[i]]++;
            rep(i, 1, m) wc[i] += wc[i-1];
            per(i, 0, n) sa[--wc[wd[i]]] = y[i];
            t = x, x = y, y = t, p = 1, x[sa[0]] = 0;
            rep(i, 1, n) x[sa[i]] = cmp(y, sa[i-1], sa[i], j) ? p-1 : p++;
        }
    }
    void calheight(int *s, int n) {    // n = len
        rep(i, 1, n+1) rk[sa[i]] = i;
        for(int i = 0, j, k = 0; i < n; height[rk[i++]] = k)
            for(k ? k-- : 0, j = sa[rk[i]-1]; s[i+k] == s[j+k]; k++);
    }
    // 把 n 个字符串连接起来，中间插入未出现字符
    int connect(int *s, int n) {    // 将 n 个字符串连接成 s
        int len = 0, d = n;     // 注意偏移值 d 是否需要修改
        rep(i, 0, n) {
            scanf("%s", str);
            int k = strlen(str);
            rep(j, 0, k) {
                s[j+len] = str[j] + d;
                id[j+len] = i + 1;
            }
            s[len+k] = i + 1;       // 注意插入的字符选择
            id[len+k] = 0;
            len += k + 1;
        }
        s[--len] = 0;
        return len;
    }
};

================================================== Problem Set ==================================================

-------------------------------------------------- 单个字符串 --------------------------------------------------

// 【最长公共前缀】

// 给定一个字符串，询问某两个字符串的最长公共前缀
// 求两个后缀的最长公共前缀可以转化为求 height[] 某个区间上的最小值 (RMQ)

ST rmq;     // a[] 从 1 开始
void initrmq(int len) { rmq.init(height, len); }
int lcp(int i, int j) {
    int l = rk[i], r = rk[j];
    if (l > r) swap(l, r);
    return rmq.query(l+1, r);
}

----------------------------------------------------------------------------------------------------

// 重复子串：字符串 t 在字符串 s 中至少出现两次，则称 t 是 s 的 重复子串。

// 【可重叠最长重复子串】

// 等价于求 height[] 最大值

int lrs(int len) {
    int res = 0; rep(i, 2, len+1) res = max(res, height[i]); return res;
}

// 【不可重叠最长重复子串】

// 二分长度值，将后缀分组，组内 height[] 值不小于二分值，判断组内后缀的位置最大值和最小值的差值是否不小于二分值

bool check(int m, int len) {
    for (int i = 2, ma = sa[1], mi = sa[1]; i <= len; ++i) {
        if (height[i] < m) ma = mi = sa[i];
        else {
            mi = min(mi, sa[i]);
            ma = max(ma, sa[i]);
            if (ma - mi >= m) return true;      // 如果使用的是差分数组，此处应改为 > m
        }
    }
    return false;
}
int lrs(int len) {
    int L = 0, R = len >> 1;
    while (L < R) {
        int M = L + ((R - L + 1) >> 1);     //防止溢出，溢出可能造成TLE
        if (check(M, len)) L = M; else R = M - 1;
    }
    return L;
}

// 【可重叠的 k 次最长重复子串】

// 给定一个字符串，求至少出现 k 次的最长重复子串，这 k 个子串可以重叠。
// 二分长度，后缀分组，判断组内后缀个数是否不小于 k

bool check(int m, int len, int k) {
    int cnt = 1;
    rep(i, 1, len+1) if (height[i] >= m) {
        if (++cnt >= k) return true;
    } else cnt = 1;
    return false;
}
int lrs(int len, int k) {
    int L = 0, R = len;
    while (L < R) {
        int M = L + ((R - L + 1) >> 1);     //防止溢出，溢出可能造成TLE
        if (check(M, len, k)) L = M; else R = M - 1;
    }
    return L;
}

----------------------------------------------------------------------------------------------------

// 【不相同的子串的个数】

// 按排名遍历，每一次新加进来的后缀 suffix(sa[k]), 它将产生 n-sa[k] 个新的前缀。
// 但是其中有 height[k] 个是和前面的字符串的前缀是相同的。
// 所以 suffix(sa[k]) 将贡献出 n-sa[k]-height[k] 个不同的子串。

int cnt(int len) {
    int res = 0; rep(i, 1, len+1) res += n - sa[i] - height[i]; return res;
}

----------------------------------------------------------------------------------------------------

// 连续重复串：如果一个字符串 s 是由某个字符串 t 重复 R 次而得到的，则称 s 是一个连续重复串。 R 是这个字符串的重复次数。

// 【重复次数最多的连续重复子串】

// 给定一个字符串，求重复次数最多的连续重复子串。
// https://www.cnblogs.com/staginner/archive/2012/02/06/2340521.html

int crs(int len) {
    int res = 1, j, k, dlen, tmp;
    rep(i, 1, len+1) for (j = 0; j + i <= len; j += i) {
        dlen = lcp(j, j + i);
        k = j - (i - dlen % i);
        tmp = dlen / i + 1;
        if (k >= 0 && lcp(k, k + i) >= i) ++tmp;
        res = max(res, tmp);
    }
    return res;     // 返回重复次数
}

// 找到字典序最小的重复次数最多的连续重复子串
// int adr, alen, cnt;
// obj.crs(len, adr, alen, cnt);
// alen *= cnt;
// rep(i, 0, alen) printf("%c", s[i+adr]);

void crs(int len, int &adr, int &alen, int &cnt) {
    int res = 0, j, k, dlen, tmp;
    rep(i, 1, len+1) for (j = 0; j + i <= len; j += i) {
        dlen = lcp(j, j + i);
        tmp = dlen / i + 1;
        if (tmp > res || tmp == res && rk[j] < rk[adr]) {
            res = cnt = tmp; adr = j; alen = i;
        }
        for (k = j - (i - dlen % i); k >= 0 && j - k < i; --k) {
            if (lcp(k, k + i) < i) break;
            if (tmp+1 > res || tmp+1 == res && rk[k] < rk[adr]) {
                res = cnt = tmp+1; adr = k; alen = i;
            }
        }
    }
}

----------------------------------------------------------------------------------------------------

// 【将一个字符串分为两个非空子串，交换两个子串，使得新串字典序最小】
// 等价于
// 【将一个字符串整个反转，然后对应两个子串再反转】

// poj 3581
// 将原串复制一份接在后面，做后缀数组，找到在原串位置上的 sa[] 即可。
// http://blog.163.com/just_gogo/blog/static/1914390652011823103842787/

-------------------------------------------------- 两个字符串 --------------------------------------------------

// 【最长公共子串】

// 求两个字符串的最长公共子串 connect -> calsa -> calheight -> lcs
// 将两个字符串连接，中间插入未出现字符，尾部插入未出现的最小字符
// 然后求这个新字符串的后缀数组
// 按排名遍历相邻后缀，如果两个后缀分属两个字符串，则更新 lcs

int lcs(int mid, int len) {   // mid 为前段字符串长度
    int res = 0;
    rep(i, 2, len+1) if (sa[i] > mid && sa[i-1] < mid || sa[i] < mid && sa[i-1] > mid)
        res = max(res, height[i]);
    return res;
}

----------------------------------------------------------------------------------------------------

// 【长度不小于 k 的公共子串的个数】

// 基本思路是计算 A 的所有后缀和 B 的所有后缀之间的最长公共前缀的长度，把最长公共前缀长度不小于 k 的部分全部加起来。
// 先将两个字符串连起来，中间用一个没有出现过的字符隔开。
// 按 height 值分组（组内 height[] >= k ）后，接下来的工作便是快速的统计每组中后缀之间的最长公共前缀之和。
// 扫描一遍，每遇到一个 B 的后缀就统计与前面的 A 的后缀能产生多少个长度不小于 k 的公共子串，
// 这里 A 的后缀需要用一个单调的栈来高效的维护。然后对 A 也这样做一次。
// https://blog.csdn.net/acm_cxlove/article/details/7946967

int Stack[N][2];
bool cmp(int i, int mid, bool small) { return small ? sa[i] < mid : sa[i] > mid; }
ll cnt(int len, int mid, int k) {
    ll res = 0, tot, top;       // tot 当前总贡献， top 栈顶
    rep(t, 0, 2) {  // 每次碰到 B 串后缀就统计与前面 A 串后缀产生的贡献，然后反过来再做一次
        tot = top = 0;      // 从栈底到栈顶单调递增
        rep(i, 2, len+1) {
            if (height[i] < k) top = tot = 0;
            else {
                int num = 0;
                // height[i] 表示 后缀 i 和后缀 i-1 的公共前缀，这里实际上是拿后缀 i-1 与栈顶比较
                // 如果当前后缀 i-1 是用来产生贡献的串（如上述 A 串）
                // 那么 num+1 用来表示自己参与了贡献 （如果 num = 0 ，就表示自己是如上述 B 串，不参与贡献）
                // tot 加的就是当前后缀最多能够提供多少个公共前缀
                if (cmp(i-1, mid, t)) num++, tot += height[i] - k + 1;
                while (top > 0 && height[i] <= Stack[top-1][0]) {   // 如果当前后缀公共前缀比栈顶后缀短
                    top--;      // 则栈顶需要出栈
                    tot -= Stack[top][1] * (Stack[top][0] - height[i]);     // 之前它所提供的贡献也要相应减少
                    num += Stack[top][1];
                    // num 加的表示当前栈顶后缀把多少个公共后缀比它长的后缀踢出了栈，就要继承他们的贡献
                }
                Stack[top][0] = height[i]; Stack[top++][1] = num;
                // 因为两个后缀的最长公共前缀取决于 height[] 区间最小值
                // 所以较短的公共前缀只会对排在它前面的后缀在贡献时产生影响
                // 不会对后面的后缀在贡献时产生影响
                // 所以当前后缀处理完前面后缀的继承问题后，直接入栈
                if (cmp(i, mid, !t)) res += tot;
                // 在处理完后缀 i-1 的进栈后，如果 i 是属于上述 B 串
                // 则实际上也等价处理了当前情况下后缀 i 对栈的影响
                // （但下一次到后缀 i 和后缀 i+1 时， height[i+1] 就会不一样了）
                // 那么直接将当前贡献加入 res ，就是属于 B 串的后缀 i 能够与前面的 A 串后缀产生的贡献
            }
        }
    }
    return res;
}

-------------------------------------------------- 多个字符串 --------------------------------------------------

// 【最长公共子串】

// 求 n 个字符串的最长公共子串，复杂度 O(nLlogL) L: 单个字符串最大长度
// connect -> calsa -> calheight -> lcs -> check
// 和求两个字符串的时候一样，先把 n 个字符串连接起来
// 调用的时候把 grup 移到外面，数组大小为单个字符串最大长度

int grup[ 字符串总数 ];
bool check(int m, int n, int len) {     // 找到一段区间，使得区间内 height[] >= m 且后缀分属 n 个字符串
    memset(grup, 0, sizeof(grup)); height[len+1] = -1;  // 设 -1 是因为 j 会越界
    for (int i = 2, j, t, num; i <= len; i = j+1) { // 按排名枚举后缀
        for (; i <= len && height[i] < m; i++);     // 找到第一个大于等于 m 的 height[i]
        for(j = i; height[j] >= m; j++);            // 找到最后一个大于等于 m 的 height[i], 此时 j 在下一位
        if (j - i + 1 < n) continue;                // 如果区间长度不足 n
        num = 0; rep(k, i-1, j) if ((t=id[sa[k]]) && grup[t] != j) grup[t] = j, ++num;
        if (num >= n) return true;
    }
    return false;
}
int lcs(int n, int dlen, int len) {   // n 个字符串, dlen : 单个字符串最大长度
    int L = 0, R = dlen;
    while (L < R) {
        int M = L + ((R - L + 1) >> 1);     //防止溢出，溢出可能造成TLE
        if (check(M, n, len)) L = M; else R = M - 1;
    }
    return L;   // 返回子串长度
}

----------------------------------------------------------------------------------------------------

// 【出现在不小于 k 个字符串中的最长公共子串】

// 方法基本同上，通过一个 vector 存子串起始地址
// 可以找到所有这样的子串，并按字典序输出
// 当 k = n 时即为上题做法

vi ans;
int grup[ 字符串总数 ];
bool check(int m, int n, int len) {     // 找到一段区间，使得区间内 height[] >= m 且后缀分属 n 个字符串  // 这里的 n 即为 k
    int f = 0;
    memset(grup, 0, sizeof(grup)); height[len+1] = -1;  // 设 -1 是因为 j 会越界
    for (int i = 2, j, t, num; i <= len; i = j+1) { // 按排名枚举后缀
        for (; i <= len && height[i] < m; i++);     // 找到第一个大于等于 m 的 height[i]
        for(j = i; height[j] >= m; j++);            // 找到最后一个大于等于 m 的 height[i], 此时 j 在下一位
        if (j - i + 1 < n) continue;                // 如果区间长度不足 n
        num = 0; rep(k, i-1, j) if ((t=id[sa[k]]) && grup[t] != j) grup[t] = j, ++num;
        if (num >= n) if (!f) ans.clear(), ans.pb(sa[i-1]), f = 1; else ans.pb(sa[i-1]);    // 每次找到适合的二分值都要清空 ans
    }
    return f;
}
int lcs(int n, int dlen, int len) {   // n 个字符串, dlen : 单个字符串最大长度   // 这里的 n 即为 k
    int L = 0, R = dlen;
    while (L < R) {
        int M = L + ((R - L + 1) >> 1);     //防止溢出，溢出可能造成TLE
        if (check(M, n, len)) L = M; else R = M - 1;
    }
    return L;   // 返回子串长度
}
int Solve() {
    int dlen = obj.lcs(k, max_dlen, len);
    if (dlen == 0) return !puts("?");
    rep(i, 0, sz(ans)) {
        int adr = ans[i];
        rep(j, 0, dlen) printf("%c", s[adr+j] - n);     // n 为偏移值
        puts("");
    }
}

----------------------------------------------------------------------------------------------------

// 【每个字符串至少出现两次且不重叠的最长字串】

// 与求最长公共子串方法基本类似，是否重叠则通过后缀出现位置的最值之差判断
// 刚好由于有两个最值，所以顺便判断了出现次数

int mi[ 字符串总数 ], ma[ 字符串总数 ];
bool check(int m, int n, int len) {     // 找到一段区间，使得区间内 height[] >= m 且后缀分属 n 个字符串
    height[len+1] = -1;  // 设 -1 是因为 j 会越界
    for (int i = 2, j, k, t; i <= len; i = j+1) { // 按排名枚举后缀
        for (; i <= len && height[i] < m; i++);     // 找到第一个大于等于 m 的 height[i]
        for(j = i; height[j] >= m; j++);            // 找到最后一个大于等于 m 的 height[i], 此时 j 在下一位
        if (j - i + 1 < n) continue;                // 如果区间长度不足 n
        memset(mi, 0x3f, sizeof(mi));
        memset(ma, 0xbf, sizeof(ma));   // 原因是这样 ma - mi 时不会下溢
        for (k = i-1; k < j; ++k) {
            t = id[sa[k]];
            mi[t] = min(mi[t], sa[k]);
            ma[t] = max(ma[t], sa[k]);
        }
        // 如果不要求重叠，则下面不需要判断最值之差，用一个 cnt[] 记录出现次数，判断出现次数是否符合要求即可
        for (k = 1; k <= n; ++k) if (ma[k] - mi[k] < m) break;
        if (k > n) return true;
    }
    return false;
}
int lcs(int n, int dlen, int len) {   // n 个字符串, dlen : 单个字符串最大长度
    int L = 0, R = dlen;
    while (L < R) {
        int M = L + ((R - L + 1) >> 1);     //防止溢出，溢出可能造成TLE
        if (check(M, n, len)) L = M; else R = M - 1;
    }
    return L;   // 返回子串长度
}

----------------------------------------------------------------------------------------------------

// 【出现在第一个字符串中且不出现在剩下的字符串中的最短子串】
// UVALive 7902

bool check(int m, int len1, int len) {
    for (int i = 2, j, t, ok; i <= len; i = j+1) { // 按排名枚举后缀
        for (; i <= len; ++i) {
            if (id[sa[i]] == 1 && len1 - sa[i] >= m && height[i] < m) { ans = sa[i]; break; }
            // 找到属于第一个字符串且长度大于等于 m 的后缀，且和前面不属于第一个字符串的后缀的公共前缀长度小于 m
        }
        if (i > len) return false;
        for (ok = 1, j = i+1; j <= len; ++j) {
            if (height[j] < m) return true;     // 两个后缀的最大公共前缀等于区间最小值
            if (id[sa[j]] != 1) { ok = 0; break; }  // 如果不属于第一个字符串的后缀与前面的后缀的公共前缀长度大于等于 m
        }
        if (ok) return true;
    }
    return false;
}
int lcs(int n, int len1, int len) {   // n 个字符串
    int L = 1, R = len1;    // 最大值为第一个字符串长度
    while (L < R) {
        int M = L + ((R - L) >> 1);     //防止溢出，溢出可能造成TLE
        if (check(M, len1, len)) R = M; else L = M + 1;
    }
    if (!check(L, len1, len)) return -1;
    return L;   // 返回子串长度
}
