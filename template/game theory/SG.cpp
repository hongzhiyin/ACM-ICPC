// 求 0 ~ len-1 的 sg 函数值
// way[] 表示转移方式，k 为转移方式个数

int sg[N];
bool vis[N];
void GetSG(int len) {
    memset(sg, 0, sizeof(sg));
    rep(i, 1, len) {
        memset(vis, 0, sizeof(vis));
        for (int j = 0; j < k && way[j] <= i; j++)
            vis[sg[i-way[j]]] = 1;
        rep(j, 0, len) if (!vis[j]) {
            sg[i] = j;
            break;
        }
    }
}
