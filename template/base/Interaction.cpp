// 交互题不要使用 while (~scanf("", )) {}

int query(int sx, int sy, int ex, int ey) {
    printf("? %d %d %d %d\n", sx, sy, ex, ey);
    fflush(stdout);
    string s; cin >> s;
    if (s == "YES") return 1;
    return 0;
}
