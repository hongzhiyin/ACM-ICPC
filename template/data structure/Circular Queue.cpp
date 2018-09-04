int qnode[N], head, tail;
struct Queue {
    Queue () { head = tail = 0; }
    bool empty() { return head == tail; }
    int front() { return qnode[head]; }
    void push(int x) { qnode[tail++] = x; if (tail == N) tail = 0; }
    void pop() { ++head; if (head == N) head = 0; }
};
Queue Q;
