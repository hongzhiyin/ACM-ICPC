vector <int> nums;
vector <char> ops;

int grade(char op) {
    switch (op) {
        case '(': return 1;
        case '+':
        case '-': return 2;
        case '*':
        case '/': return 3;
    }
    return 0;
}

void calc(char op) {
    int y = *nums.rbegin(); nums.pop_back();
    int x = *nums.rbegin(); nums.pop_back();
    int z;
    switch (op) {
        case '+': z = x + y; break;
        case '-': z = x - y; break;
        case '*': z = x * y; break;
        case '/': z = x / y; break;
    }
    nums.push_back(z);
}

int eval(string s) {
    nums.clear(); ops.clear();
    int top = 0, val = 0;
    for (int i = 0; i < sz(s); i++) {
        if ('0' <= s[i] && s[i] <= '9') {
            val = val * 10 + s[i] - '0';
            if ('0' <= s[i+1] && s[i+1] <= '9') continue;
            nums.pb(val);
            val = 0;
        } else if (s[i] == '(') {
            ops.pb(s[i]);
        } else if (s[i] == ')') {
            while (*ops.rbegin() != '(') {
                calc(*ops.rbegin());
                ops.pop_back();
            }
            ops.pop_back();
        } else {
            while (ops.size() && grade(*ops.rbegin()) >= grade(s[i])) {
                calc(*ops.rbegin());
                ops.pop_back();
            }
            ops.pb(s[i]);
        }
    }
    while (ops.size()) {
        calc(*ops.rbegin());
        ops.pop_back();
    }
    return *nums.begin();
}
