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
        return ;
    }
    void calheight(int *s, int n) {    // n = len
        int j, k = 0;
        rep(i, 1, n+1) rank[sa[i]] = i;
        for(int i = 0; i < n; height[rank[i++]] = k)
            for(k ? k-- : 0, j = sa[rank[i]-1]; s[i+k] == s[j+k]; k++);
        return ;
    }
    int lcp(int *s, int mid, int len) {   // mid 为前段字符串长度
        int res = 0;
        rep(i, 2, len+1) if (sa[i] > mid && sa[i-1] < mid || sa[i] < mid && sa[i-1] > mid)
            res = max(res, height[i]);
        return res;
    }
};
