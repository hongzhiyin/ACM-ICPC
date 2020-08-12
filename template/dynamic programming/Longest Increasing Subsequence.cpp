/* ----- 最长上升子序列 -----
< 注意事项 >
    1. lower_bound : 严格上升 ; upper_bound : 非严格上升
    2. 最长下降 : a[i] = -a[i] 即可， tmp[i] 不用变

< 结论 >
    1. 判断 a[i] 是否可能在 LIS 中 :
    .. 若 dp1[i] + dp2[i] - 1 == mxlen ，则 a[i] 可能在 LIS 中
    .. dp1[i] : 以 a[i] 为终点的 LIS 长度
    .. dp2[i] : 以 a[i] 为起点的 LIS 长度
    .. mxlen : 序列的 LIS 的长度
   
    2. 判断可能在 LIS 中的元素是否在全部 LIS 中 :
    .. 若在 a[i] 左边的所有可能在 LIS 中的元素中，有值大于等于 a[i] 的元素，
    .. 或在 a[i] 右边的所有可能在 LIS 中的元素中，有值小于等于 a[i] 的元素，
    .. 则 a[i] 不可能在全部 LIS 中。
    .. 反之，则 a[i] 在全部 LIS 中。
*/

int Longest_Increasing_Subsequence(vector<int> &array) {
    int res = 0;                                               // 最长上升子序列长度
    vector <int> tmp(array.size(), INT_MAX);                   // 初始化一个值都为无穷大的序列
    for (auto item : array) {                                  // 查找以 item 结尾的最长上升子序列
        auto pos = lower_bound(tmp.begin(), tmp.end(), item);  // pos 表示 item 的插入位置
        res = max(res, (int)(pos - tmp.begin() + 1));          // 更新最长上升子序列长度
        *pos = item;                                           // 插入位置 pos 的值更新为 item
    }
    return res;                                                // 返回最长上升子序列长度
}
