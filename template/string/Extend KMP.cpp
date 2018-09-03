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
// 题意：有一个长度为 n 的字符串，已知一个子串以及这个子串出现的若干个位置（可能不是全部）。问这种长度为 n 的字符串有多少种可能性
// 题解：从左到右依次把若干个子串填入原串，用一个指针表示前一个填入的子串的末尾，保证不重复填子串，最后用扩展 KMP 检验原串
int Solve() {
	int pos = -1;
	rep(i, 0, m) if (a[i] + len - 1 > pos) {
		for (int j = len-1; ~j && str[a[i]+j] == '?'; --j) str[a[i]+j] = s[j];
		pos = a[i] + len - 1;
	}
	obj.exkmp(str, n, s, len);
	bool ok = 1;
	rep(i, 0, m) if (ex[a[i]] != len) {
		ok = 0; break;
	}
	if (!ok) return !puts("0");
	ll ans = 1;
	rep(i, 0, n) if (str[i] == '?') ans = (ans * 26) % MOD;
	return !printf("%lld\n", ans);
}
