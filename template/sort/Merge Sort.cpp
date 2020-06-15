/* ----- 归并排序 -----
< 参数 >
    1. first 和 last 为随机访问迭代器

< 使用 >
    1. 使用方法同 std::sort()
*/

template <class Iter>
void Merge_Sort(Iter first, Iter last) {
    if (first == last || last - first == 1) return;                             // 容器为空或容量为 1
    Iter middle = first + (last - first) / 2, i, j;                             // 区间中点 middle
    Merge_Sort(first, middle); Merge_Sort(middle, last);                        // 归并左右区间
    vector <typename iterator_traits<Iter>::value_type> tmp(last - first);      // 临时容器 tmp
    typename vector <typename iterator_traits<Iter>::value_type>::iterator k;   // 容器 tmp 的迭代器 k
    for (k = tmp.begin(), i = first, j = middle; k != tmp.end(); ++k) {         // 遍历
        if (j == last || i < middle && *i <= *j) *k = *(i++);                   // 右区间已遍历完 或 左区间值更小
        else *k = *(j++);                                                       // 与上述相反
    }
    for (k = tmp.begin(), i = first; k != tmp.end(); ++k) *(i++) = *k;          // 通过临时容器还原
}