/* ----- 进制转换 -----
< 准备 >
    1. a2i[] : 字符 ch 表示的数字是 a2i[ch]
    2. i2a[] : 数字 num 用字符 i2a[num] 表示
    
< 使用 >
    1. 调用 Base_Conversion(s1, a, s2, b)
    .. 将 a 进制表示的数 s1 转换为 b 进制表示的数 s2
*/

char s[N], s1[N], s2[N];
int a2i[128], i2a[500];
void Base_Conversion(char *s1, int a, char *s2, int b) {
    strcpy(s, s1);
    int len = strlen(s), t, i;
    for (t = len, i = 0; t; ++i) {
        int k = 0;
        for (int j = len - t; j < len; j++) {
            k = k * a + a2i[s[j]];
            s[j] = i2a[k/b];
            k %= b;
        }
        s2[i] = i2a[k];
        for (; t > 0 && s[len-t] == '0'; --t);
    }
    reverse(s2, s2 + i); s2[i] = '\0';
}
