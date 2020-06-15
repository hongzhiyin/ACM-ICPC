/* ----- 归并排序 -----
< 参数 >
    1. first 和 last 为随机访问迭代器

< 使用 >
    1. 使用方法同 std::sort()
*/

template <class Iter>
void Merge_Sort(Iter first, Iter last) {
    if (first == last || last - first == 1) return;
    Iter middle = first + (last - first) / 2, i, j;
    Merge_Sort(first, middle); Merge_Sort(middle, last);
    vector <typename iterator_traits<Iter>::value_type> tmp(last - first);
    typename vector <typename iterator_traits<Iter>::value_type>::iterator k;
    for (k = tmp.begin(), i = first, j = middle; k != tmp.end(); ++k) {
        if (j == last || i < middle && *i <= *j) *k = *(i++);
        else *k = *(j++);
    }
    for (k = tmp.begin(), i = first; k != tmp.end(); ++k) *(i++) = *k;
}