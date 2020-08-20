/* ----- 二分查找 -----
< 参数 >
    1. 二分区间边界值 left 与 right
    2. 判别函数 check
    3. 可自行添加判别函数的其他参数，记得在代码中修改

< 返回 >
    1. pair< 是否无解，最终二分值 >
*/

// 求最大值
template <class T, class Func>
pair<bool, T> Binary_Search_Max(T left, T right, Func check) {      // 左右边界与判别函数
    T Left = left - 1, Right = right;                               // 左边界预留越界下标
    while (Left < Right) {                                          // 终止条件即二者相等
        T Middle = Left + ((Right - Left + 1) >> 1);                // 偶数长度区间的中点落在靠右一侧
        if (check(Middle)) Left = Middle;                           // 中点可行
        else Right = Middle - 1;                                    // 中点不可行
    }
    return make_pair(Left != left - 1, Left);                       // 是否无解，最终二分值
}

// 求最小值
template <class T, class Func>
pair<bool, T> Binary_Search_Min(T left, T right, Func check) {      // 左右边界与判别函数
    T Left = left, Right = right + 1;                               // 右边界预留越界下标
    while (Left < Right) {                                          // 终止条件即二者相等
        T Middle = Left + ((Right - Left) >> 1);                    // 偶数长度区间的中点落在靠左一侧
        if (check(Middle)) Right = Middle;                          // 中点可行
        else Left = Middle + 1;                                     // 中点不可行
    }
    return make_pair(Left != right + 1, Left);                      // 是否无解，最终二分值
}
