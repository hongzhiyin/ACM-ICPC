/* ----- 希尔排序 -----
< 参数 >
    1. first 和 last 为随机访问迭代器

< 使用 >
    1. 使用方法同 std::sort()
*/

template <class Iter>
void Shell_Sort(Iter first, Iter last) {
    if (first == last) return;                                          // 容器为空
    typename iterator_traits<Iter>::difference_type gap;                // 分部排序的序列间隔 gap
    for (gap = (last - first) >> 1; gap; gap >>= 1) {                   // 间隔逐步减半
        for (Iter i = first; i - first != gap; ++i) {                   // 序列首部
            for (Iter j = i + gap, k; j < last; j += gap) {             // 序列内插入排序
                typename iterator_traits<Iter>::value_type tmp = *j;    // tmp 暂存元素值
                for (k = j; k != i && tmp < *(k-gap); k -= gap) {       // 向前遍历
                    *k = *(k - gap);                                    // 更大的元素向后移动
                }
                *k = tmp;                                               // 将元素插入正确的位置
            }
        }
    }
}