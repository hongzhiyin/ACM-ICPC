// https://subetter.com/algorithm/manacher-algorithm.html
// 给定一个字符串，求出其最长回文子串

class Manacher {
public:
    const static int N = 1e5 + 7;
    int radius[N<<1];
    string longestPalindrome(string s) {
        if (s.size() == 0) return s;
        string t = "$#";
        for (int i = 0; i < s.size(); ++i) {
            t += s[i];
            t += '#';
        }
        int maxlen = 0, rbound = 0, mid, pos;
        for (int i = 1; i < t.size(); ++i) {
            radius[i] = i < rbound ? min(radius[2*mid-i], rbound - i) : 1;
            while (t[i-radius[i]] == t[i+radius[i]]) radius[i]++;
            if (rbound < i + radius[i]) rbound = i + radius[mid=i];
            if (maxlen < radius[i] - 1) {
                maxlen = radius[i] - 1;
                pos = i - maxlen;
                pos = (pos + 1) / 2 - 1;
            }
        }
        return s.substr(pos, maxlen);
    }
};
