T heap[N];
struct Heap {
    int size;
    void clear() { size = 0; }
    bool empty() { return size == 0; }
    T top() { return heap[1]; }
    void push(T x) {
        heap[++size] = x;
        for (int v = size, u = v >> 1; v; v = u, u = v >> 1) {
            if (heap[u] > heap[v]) swap(heap[u], heap[v]);
            else break;
        }
    }
    void pop() {
        swap(heap[size--], heap[1]);
        for (int u = 1, v = 2; v <= size; u = v, v <<= 1) {
            if (v + 1 <= size && heap[v+1] < heap[v]) ++v;
            if (heap[v] < heap[u]) swap(heap[v], heap[u]);
            else break;
        }
    }
};
