// 本地要用文件调试
struct FastIO {
    static const int S = 1310720;
    int wpos; char wbuf[S];
    FastIO() : wpos(0) {}
    inline int rchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len) pos = 0, len = fread(buf, 1, S, stdin);
        if (pos == len) return -1;
        return buf[pos++];
    }
    inline int ruint() {	// unsign int
        int c = rchar(), x = 0;
        while (c <= 32) c = rchar();
        for (; '0' <= c && c <= '9'; c = rchar())
            x = x * 10 + c - '0';
        return x;
    }
    inline int rint() {		// 可以手动改 long long
        int s = 1, c = rchar(), x = 0;
        while (c <= 32) c = rchar();
        if (c == '-') s = -1, c = rchar();
        for (; '0' <= c && c <= '9'; c = rchar())
            x = x * 10 + c - '0';
        return x * s;
    }
    inline void rstring(char *s) {
        int c = rchar();
        while (c <= 32) c = rchar();
        for (; c > 32; c = rchar())
            *s++ = c;
        *s = 0;
    }
    inline void wchar(int x) {
        if (wpos == S)
            fwrite(wbuf, 1, S, stdout), wpos = 0;
        wbuf[wpos++] = x;
    }
    inline void wint(int x) {
        if (x < 0) wchar('-'), x = -x;
        char s[24]; int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
    }
    inline void wstring(const char *s) {
        while (*s) wchar(*s++);
    }
    ~FastIO() {
        if (wpos)
            fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;
