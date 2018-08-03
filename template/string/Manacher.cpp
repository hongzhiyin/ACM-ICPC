// https://subetter.com/articles/2018/03/manacher-algorithm.html

int p[N];
char str[N], s[N];
struct Manacher {
    int init(char *str, int m) {
        s[0] = '$'; s[1] = '#';
        int j = 2;
        rep(i, 0, m) {
            s[j++] = str[i];
            s[j++] = '#';
        }
        s[j] = '\0';
        return j;
    }
    int manacher(char *str, int m) {
        int n = init(str, m), res = 0, id, mx = 0;
        rep(i, 1, n) {
            if (i < mx) p[i] = min(p[2*id-i], mx - i);
            else p[i] = 1;
            while (s[i-p[i]] == s[i+p[i]]) p[i]++;
            if (mx < i + p[i]) {
                id = i;
                mx = i + p[i];
            }
            res = max(res, p[i] - 1);
        }
        return res;
    }
};
