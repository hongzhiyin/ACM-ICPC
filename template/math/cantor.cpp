int cantor(char* s) {
    int res = 0, len = strlen(s);
    rep(i, 0, len) rep(j, i+1, len)
        if (s[j] < s[i]) res += jc[9-i-1];
    return res;
}

char res[30];
char* revcantor(int x, int len) {
    bool vis[10];
    memset(vis, 0, sizeof(vis));
    rep(i, 0, len) {
        int tmp = x / jc[len-1-i];
        x = x % jc[len-1-i];
        int num = 0;
        rep(j, 0, len) {
            if (vis[j] == 0) num++;
            if (num == tmp + 1) {
                res[i] = j + '0' + 1;
                vis[j] = 1;
                break;
            }
        }
    }
    res[len] = '\0';
    return res;
}
