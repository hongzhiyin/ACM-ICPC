/* ----- 插入排序 -----
< 参数 >
    1. first 和 last 为随机访问迭代器

< 使用 >
    1. 使用方法同 std::sort()
*/

template <class Iter>
void Insertion_Sort(Iter first, Iter last) {
    if (first == last) return;                                  // 容器为空
    for (Iter i = first + 1, j; i != last; ++i) {               // 将第 i 位元素向前插入
        typename iterator_traits<Iter>::value_type tmp = *i;    // tmp 暂存元素值
        for (j = i; j != first && tmp < *(j-1); --j) {          // 向前遍历
            *j = *(j - 1);                                      // 更大的元素向后移动
        }
        *j = tmp;                                               // 将元素插入正确的位置
    }
}