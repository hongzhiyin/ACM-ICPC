// IOI 2009 国家集训队论文 罗穗骞《后缀数组——处理字符串的有力工具》

// for -> rep 如果超时了试试换回来？
// sa[i] 表示排在第 i 位的是后缀 sa[i], 注意：因为 s[len] = 0, 所以 sa[0] = len
// rank[i] 表示后缀 i 排第 rank[i]
// height[i] = LCP(sa[i], sa[i-1]), LCP: 最长公共前缀
int sa[N], rank[N], height[N];
int wa[N], wb[N], wc[N], wd[N];    // 不要问这些数组是什么意思，因为我也不知道，抄就对了
struct SuffixArray {
    int cmp(int *s, int a, int b, int l) { return s[a] == s[b] && s[a+l] == s[b+l]; }
    void calsa(int *s, int n, int m) {     // s[len] = 0, n = len + 1, m 为字符种类
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
        rep(i, 1, n+1) rank[sa[i]] = i;
        for(int i = 0, j, k = 0; i < n; height[rank[i++]] = k)
            for(k ? k-- : 0, j = sa[rank[i]-1]; s[i+k] == s[j+k]; k++);
    }
    // 把 n 个字符串连接起来，中间插入未出现字符
    int connect(int *s, int n) {
        int len = 0, d = n;     // 注意偏移值 d 是否需要修改
        rep(i, 1, n+1) {
            int k = strlen(str[i]);
            rep(j, 0, k) {
                s[j+len] = str[i][j] + d;
                id[j+len] = i;
            }
            s[len+k] = i;       // 注意插入的字符选择
            id[len+k] = 0;
            len += k + 1;
        }
        s[--len] = 0;
        return len;
    }
};

// -------------------------------------------------- 单个字符串问题 -------------------------------------------------- //

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

// -------------------------------------------------- //

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

// -------------------------------------------------- //

// 【不相同的子串的个数】
// 按排名遍历，每一次新加进来的后缀 suffix(sa[k]), 它将产生 n-sa[k] 个新的前缀。
// 但是其中有 height[k] 个是和前面的字符串的前缀是相同的。
// 所以 suffix(sa[k]) 将贡献出 n-sa[k]-height[k] 个不同的子串。
int cnt(int len) {
    int res = 0; rep(i, 1, len+1) res += n - sa[i] - height[i]; return res;
}

// -------------------------------------------------- //

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
            if (lcp(k, k + i) >= i)
            if (tmp+1 > res || tmp+1 == res && rk[k] < rk[adr]) {
                res = cnt = tmp+1; adr = k; alen = i;
            }
        }
    }
}

// -------------------------------------------------- 两个字符串问题 -------------------------------------------------- //

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

// -------------------------------------------------- //

// -------------------------------------------------- 多个字符串问题 -------------------------------------------------- //

// 【最长公共子串】
// 求 n 个字符串的最长公共子串，复杂度 O(nLlogL) L: 单个字符串最大长度
// connect -> calsa -> calheight -> lcs -> check
// 和求两个字符串的时候一样，先把 n 个字符串连接起来
// 调用的时候把 grup 移到外面，数组大小为单个字符串最大长度
int grup[dlen];
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
    return L;
}

// -------------------------------------------------- //

