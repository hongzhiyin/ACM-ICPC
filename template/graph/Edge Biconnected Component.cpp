/* ----- 边双连通分量 -----
< 注释 >
    0. 边双连通分量：无向图中不存在桥
    1. dfs 序：节点在搜索树上的遍历顺序
    2. 追溯值 (low) ：节点通过不在搜索树上的边所能到达的 dfs 序最小的节点的 dfs 序
    3. Edge == vector<vector<pair<int,int>>>
       edge[u] = {{v1, id1}, {v2, id2}}
    4. n: 最大节点编号 | m: 最大边编号

< 使用 >
    1. 构造对象时直接传入相应参数，得到 bcc 和 bri 供后续使用

< 注意 >
    1. 缩点时，因为遍历的是原图的点，所以只需要加单向边，另一个方向的边在遍历到对面的点时就会加入
*/

struct Edge_Biconnected_Component {
    int no, top, cnt;                               // no: dfs 序 | top: 栈指针 | cnt: 边双连通分量编号
    vector <int> dfn, low, sta;                     // dfn: dfs 序 | low: 追溯值 | sta: 保存连通分量的栈
    vector <int> bcc, bri;                          // bcc: 点所属的双连通分量编号 | bri: 该条边是否是桥

    template <class Edge>                           // Edge == vector<vector<pair<int,int>>>
    void dfs(int u, int eid, Edge &edge) {          // u: 端点编号 | eid: dfs 到达节点 u 所经过的边的编号
        dfn[u] = low[u] = ++no;                     // 追溯值初始为该节点的dfs序
        sta[top++] = u;                             // 节点入栈
        for (auto &o : edge[u]) {                   // 遍历以 u 为端点的边
            int v = o.first, id = o.second;         // v: 另一端点 | id: 边 (u, v) 的编号
            if (!dfn[v]) {                          // 如果节点 v 尚未访问过
                dfs(v, id, edge);                   // 进入下一层 dfs 搜索
                low[u] = min(low[u], low[v]);       // 更新节点 u 的追溯值
                if (low[v] > dfn[u]) bri[id] = 1;   // 节点 v 不能通过其他边到达节点 u ，则边 (u, v) 为桥
            } else if (id != eid) {                 // 节点 v 已访问过，且不是 dfs 到达节点 u 的边
                low[u] = min(low[u], dfn[v]);       // 说明该条边不属于搜索树，更新最小的 dfs 序
            }
        }
        if (low[u] == dfn[u]) {                     // 如果节点 u 无法追溯到更早的节点，说明已形成边双连通分量
            ++cnt;                                  // 边双连通分量编号
            do { bcc[sta[--top]] = cnt; }           // 栈保存的节点顺序就是搜索顺序
            while (sta[top] != u);                  // 搜索树上以 u 为根节点的子树（保存在栈中）属于同一边双连通分量
        }
    }

    template <class Edge>                           // n: 最大节点编号 | m: 最大边编号
    Edge_Biconnected_Component(int n, int m, Edge &edge) : no(0), top(0), cnt(0) {
        dfn.clear(); dfn.resize(n+1);
        low.clear(); low.resize(n+1);
        sta.clear(); sta.resize(n+1);
        bcc.clear(); bcc.resize(n+1);
        bri.clear(); bri.resize(m+1);               // 变量、容器初始化
        for (int i = 1; i <= n; ++i)                // 默认节点编号从 1 开始
            if (!dfn[i]) dfs(i, -1, edge);          // 遍历每个连通子图
    }
};
