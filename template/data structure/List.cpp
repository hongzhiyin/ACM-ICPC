// 可用作无序集合使用，支持遍历和删除操作。

void build(int n) {  // 创建一个长为 n 的链表
    rep(i, 0, n+1) net[i] = i + 1;
    rep(i, 1, n+2) pre[i] = i - 1;
}

void erase(int x) {  // 删除结点 x
    net[pre[x]] = net[x];
    pre[net[x]] = pre[x];
}

void link(int a, int b) {  // 链接结点 a 和 结点 b
    net[a] = b;
    pre[b] = a;
}

// 遍历 ( 结点 0 用于找到链表头部，不做使用 )
for (int i = net[0]; i <= n; i = net[i]) {  // 一般遍历
for (int i = net[0]; i <= n; i = net[0]) {  // 用于遍历过程会删除结点
