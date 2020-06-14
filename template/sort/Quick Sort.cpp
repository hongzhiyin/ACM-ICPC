/* ----- 快速排序 -----
< 参数 >
    1. first 和 last 为随机访问迭代器

< 使用 >
    1. 使用方法同 std::sort()
*/

template <class Iter>
void Quick_Sort(Iter first, Iter last) {
    if (first == last) return;
    Iter i = first, j = last - 1;
    typename iterator_traits<Iter>::value_type pivot = *(i + (j - i) / 2);
    while (i <= j) {
        while (*i < pivot) ++i;
        while (*j > pivot) --j;
        if (i <= j) swap(*(i++), *(j--));
    }
    Quick_Sort(first, j + 1);
    Quick_Sort(i, last);
}