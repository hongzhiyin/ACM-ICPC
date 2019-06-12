/*
    sg 函数作用 : 尼姆博弈下， n 堆石子的 sg 函数值异或和为 0 ，则为必败态
    vis[sg[next(i)]] = 1 : 当前求 i 的 sg 函数值，需要用到 i 的所有后继状态
    后继状态 : 当前石子有 i 个，那么根据规则，这 i 个石子在一次操作后会变成几个
*/

// 求 0 ~ n 的 sg 函数值
int sg[N];
bool vis[N];
void GetSG(int n) {
    memset(sg, 0, sizeof(sg));
    rep(i, 1, n+1) {
        memset(vis, 0, sizeof(vis));
        for (all next state from i) vis[sg[next(i)]] = 1;
        rep(j, 0, n+1) if (!vis[j]) {
            sg[i] = j;
            break;
        }
    }
}

// 记忆化搜索求 x 的 sg 函数值
map <int, int> sg;
int SG(int x) {
    if (!x) return 0;
    if (sg.count(x)) return sg[x];
    map <int, int> vis;
    for (all next state from x) vis[SG(next(x))] = 1
    rep(i, 0, N) if (!vis.count(i)) return sg[mask] = i;
}
