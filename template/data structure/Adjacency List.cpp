T node[N];
int node, net[N];
struct Vector {
    int head;
    Vector() { head = 0; }
    void clear() { head = 0; }
    void push_back(T x) {
        node++;
        node[node] = x;
        net[node] = head;
        head = node;
    }
};
Vector e[N];
void Init() {
    node = 0;
    rep(i, 0, n) e[i].clear();
}
// 遍历
for (int i = e[u].head; i; i = net[i])
