/* ----- 希尔排序 -----
< 参数 >
    1. first 和 last 为随机访问迭代器

< 使用 >
    1. 使用方法同 std::sort()
*/

template <class Iter>
void Shell_Sort(Iter first, Iter last) {
    if (first == last) return;
    typename iterator_traits<Iter>::difference_type gap;
    for (gap = (last - first) >> 1; gap; gap >>= 1) {
        for (Iter i = first; i - first != gap; ++i) {
            for (Iter j = i + gap, k; j < last; j += gap) {
                typename iterator_traits<Iter>::value_type tmp = *j;
                for (k = j; k != i && tmp < *(k-gap); k -= gap) {
                    *k = *(k - gap);
                }
                *k = tmp;
            }
        }
    }
}