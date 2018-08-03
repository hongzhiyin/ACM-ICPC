int net[N];
char s[N], p[N];
struct KMP {
    void Get(char *p, int m) {
        net[0] = -1;
        for (int i = 0, j = -1; i < m;) {
            if (j == -1 || p[i] == p[j]) net[++i] = ++j;
            else j = net[j];
        }
        // 最小循环节长度
        // if (m % (m - net[m]) == 0) return n - net[n]; else return n;
        // 最小循环节个数
        // if (m % (m - net[m]) == 0) return m / (m - net[m]); else return 1;
    }
    int kmp(char *s, int n, char *p, int m) {
        Get(p, m);
        for (int i = 0, j = 0; i < n;) {
            if (j == -1 || s[i] == p[j]) ++i, ++j;
            else j = net[j];
            if (j == m) return i - j;   // 第一个匹配成功的 s 串下标
            //if (j == m) cnt++, j = 0;     // 母串中可匹配的不相交模式串个数
        }
        return -1;
    }
};
