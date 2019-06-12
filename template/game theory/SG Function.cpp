/*
    sg 函数作用 : n 堆石子的 sg 函数值异或和为 0 ，则为必败态
    vis[sg[next(i)]] = 1 : 当前求 i 的 sg 函数值，需要用到 i 的所有后继状态
    后继状态 : 当前石子有 i 个，那么根据规则，这 i 个石子在一次操作后会变成几个
*/

// 求 0 ~ len-1 的 sg 函数值
// way[] 表示转移方式，k 为转移方式个数

int sg[N];
bool vis[N];
void GetSG(int len) {
    memset(sg, 0, sizeof(sg));
    rep(i, 1, len) {
        memset(vis, 0, sizeof(vis));
        for (int j = 0; j < k && way[j] <= i; j++)
            vis[sg[i-way[j]]] = 1;  // vis[sg[next(i)]] = 1;
        rep(j, 0, len) if (!vis[j]) {
            sg[i] = j;
            break;
        }
    }
}
