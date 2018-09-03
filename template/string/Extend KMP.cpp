// 讲解：https://blog.csdn.net/dyx404514/article/details/41831947
// 代码：https://subetter.com/articles/2018/04/extended-kmp-algorithm.html

int net[N], ex[N];  // ex[i] 表示 T 与 S[i, n-1] 的最长公共前缀
char s[N], t[N];
struct ExKMP {  // 求 T 与 S 的每一个后缀的最长公共前缀
    void Get(char *t, int m) {
        int a = 0, p = 0;
        net[0] = m;
        rep(i, 1, m) {
            if (i >= p || i + net[i-a] >= p) {
                if (i >= p) p = i;
                while (p < m && t[p] == t[p-i]) p++;
                net[i] = p - i;
                a = i;
            } else {
                net[i] = net[i-a];
            }
        }
    }
    void exkmp(char *s, int n, char *t, int m) {
        Get(t, m);
        int a = 0, p = 0;
        rep(i, 0, n) {
            if (i >= p || i + net[i-a] >= p) {
                if (i >= p) p = i;
                while (p < n && p - i < m && s[p] == t[p-i]) p++;
                ex[i] = p - i;
                a = i;
            } else {
                ex[i] = net[i-a];
            }
        }
    }
};

================================================== Problem Set ==================================================

// cf 535D
// 
