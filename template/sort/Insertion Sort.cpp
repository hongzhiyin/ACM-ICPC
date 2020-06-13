/* ----- 插入排序 -----
< 参数 >
    1. first 和 last 为随机访问迭代器

< 使用 >
    1. 使用方法同 std::sort()
*/

template <class Iter>
void Insertion_Sort(Iter first, Iter last) {
    if (first == last) return;
    for (Iter i = first + 1, j; i != last; ++i) {
        typename iterator_traits<Iter>::value_type tmp = *i;
        for (j = i; j != first && tmp < *(j-1); --j) {
            *j = *(j - 1);
        }
        *j = tmp;
    }
}