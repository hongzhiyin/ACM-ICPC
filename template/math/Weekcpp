inline int week(int y, int m, int d) {
    if (y < 1600 || y > 9999) return -1;
    if (m < 1 || m > 12) return -1;
    if (d < 1 || d > day[m] + (m==2 && (y%400==0||y%100!=0&&y%4==0))) return -1;
    int tm = m >= 3 ? (m - 2) : (m + 10);
    int ty = m >= 3 ? y : (y - 1);
    return (ty + ty / 4 - ty / 100 + ty / 400 + (int)(2.6 * tm - 0.2) + d) % 7;
}
