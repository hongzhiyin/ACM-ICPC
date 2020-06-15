/* ----- 冒泡排序 -----
< 参数 >
    1. first 和 last 为随机访问迭代器

< 使用 >
    1. 使用方法同 std::sort()
*/

template <class Iter>
void Bubble_Sort(Iter first, Iter last) {
    if (first == last) return;                      // 容器为空
    for (--last; first != last; --last) {           // last 标记当前最大值的正确位置
        for (Iter i = first; i != last; ++i) {      // “冒泡” 过程
            if (*i > *(i + 1)) swap(*i, *(i+1));    // 将当前最大值往后移动
        }
    }
}