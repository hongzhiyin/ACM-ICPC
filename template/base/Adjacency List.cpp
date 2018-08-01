T node[N];
int node_cnt, net[N];
struct Vector {
    int head;
    Vector() { head = 0; }
    void clear() { head = 0; }
    void push_back(T x) {
        node_cnt++;
        node[node_cnt] = x;
        net[node_cnt] = head;
        head = node_cnt;
    }
};
Vector e[N];
void Init() {
    node_cnt = 0;
    rep(i, 0, n) e[i].clear();
}
// 遍历
for (int i = e[u].head; i; i = net[i])
