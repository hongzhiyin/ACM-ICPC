/* ----- 选择排序 -----
< 参数 >
    1. first 和 last 为随机访问迭代器

< 使用 >
    1. 使用方法同 std::sort()
*/

template <class Iter>
void Selection_Sort(Iter first, Iter last) {
    if (first == last) return;                              // 容器为空
    for (Iter tmp = first; first != last; tmp = ++first) {  // 查找当前最小值，用 tmp 标记
        for (Iter i = first + 1; i != last; ++i) {          // 遍历
            if (*i < *tmp) tmp = i;                         // 更新当前最小值标记
        }
        swap(*first, *tmp);                                 // 将当前最小值移至正确位置
    }
}