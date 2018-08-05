int rank[N],height[N];
int wa[N],wb[N],wv[N],ws[N];    // 不要问这些数组是什么意思，因为我也不知道，抄就对了
struct SuffixArray {
    int cmp(int *s, int a, int b, int l) { return s[a] == s[b] && s[a+l] == s[b+l]; }
    void calsa(int *s, int *sa, int n, int m) {     // for -> rep 如果超时了试试换回来？
        int *x = wa, *y = wb, *t;
        rep(i, 0, m) ws[i] = 0;
        rep(i, 0, n) ws[x[i]=s[i]]++;
        rep(i, 1, m) ws[i] += ws[i-1];
        per(i, 0, n) sa[--ws[x[i]]] = i;
        for(int j = 1, p = 1; p < n; j <<= 1, m = p) {
            p = 0; rep(i, n-j, n) y[p++] = i;
            rep(i, 0, n) if(sa[i] >= j) y[p++] = sa[i] - j;
            rep(i, 0, n) wv[i] = x[y[i]];
            rep(i, 0, m) ws[i] = 0;
            rep(i, 0, n) ws[wv[i]]++;
            rep(i, 1, m) ws[i] += ws[i-1];
            per(i, 0, n) sa[--ws[wv[i]]] = y[i];
            t = x, x = y, y = t, p = 1, x[sa[0]] = 0;
            rep(i, 1, n) x[sa[i]] = cmp(y, sa[i-1], sa[i], j) ? p-1 : p++;
        }
        return ;
    }
    void calheight(int *s, int *sa, int n) {
        int j, k = 0;
        rep(i, 1, n+1) rank[sa[i]] = i;
        for(int i = 0; i < n; height[rank[i++]] = k)
            for(k ? k-- : 0, j = sa[rank[i]-1]; s[i+k] == s[j+k]; k++);
        return ;
    }
};
