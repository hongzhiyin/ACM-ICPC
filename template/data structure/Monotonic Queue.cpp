/* ----- 单调队列 ----- */

template <class T, class Comp=less<T>>                              // T: 元素类型； Comp: 关系类仿函数
struct Monotonic_Queue {                                            // 默认队首最小的单调队列
    deque <T> Q;                                                    // 容器 deque
    inline T& front() { return Q.front(); }                         // 返回队首的引用
    inline void push(T x) {                                         // 队尾加入元素 x
        while (!Q.empty() && Comp()(x, Q.back())) Q.pop_back();     // 默认：队尾大于等于 x 的元素出队
        Q.push_back(x);                                             // 元素 x 入队
    }
    inline void pop() { Q.pop_front(); }                            // 队首出队
};