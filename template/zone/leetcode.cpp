#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct LeetCode {
    // ---------- trim spaces ----------
    void trimLeftTrailingSpaces(string &input) {
        input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
            return !isspace(ch);
        }));
    }

    void trimRightTrailingSpaces(string &input) {
        input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
            return !isspace(ch);
        }).base(), input.end());
    }

    // ---------- string to any ----------
    int stringToInteger(string input) {
        return stoi(input);
    }

    vector<int> stringToIntegerVector(string input) {
        vector<int> output;
        trimLeftTrailingSpaces(input);
        trimRightTrailingSpaces(input);
        input = input.substr(1, input.length() - 2);
        stringstream ss;
        ss.str(input);
        string item;
        char delim = ',';
        while (getline(ss, item, delim)) {
            output.push_back(stoi(item));
        }
        return output;
    }

    vector<vector<int>> stringToInt2dArray(string input) {
        vector<vector<int>> output;
        trimLeftTrailingSpaces(input);
        trimRightTrailingSpaces(input);
        input = input.substr(1, input.length() - 2);
        stringstream ss;
        ss.str(input);
        string item;
        char delim = ']';
        while (getline(ss, item, delim)) {
            output.push_back(stringToIntegerVector(item + "]"));
            ss.get();
        }
        return output;
    }

    vector<char> stringToCharVector(string input) {
        vector<char> output;
        trimLeftTrailingSpaces(input);
        trimRightTrailingSpaces(input);
        input = input.substr(1, input.length() - 2);
        for (int i = 1; i < input.size(); i += 4)
            output.push_back(input[i]);
        return output;
    }

    vector<vector<char>> stringToChar2dArray(string input) {
        vector<vector<char>> output;
        trimLeftTrailingSpaces(input);
        trimRightTrailingSpaces(input);
        input = input.substr(1, input.length() - 2);
        stringstream ss;
        ss.str(input);
        string item;
        char delim = ']';
        while (getline(ss, item, delim)) {
            output.push_back(stringToCharVector(item + "]"));
            ss.get();
        }
        return output;
    }

    string stringToString(string input) {
        return input.substr(1, input.length() - 2);
    }

    vector<string> stringToStringVector(string input) {
        vector<string> output;
        trimLeftTrailingSpaces(input);
        trimRightTrailingSpaces(input);
        input = input.substr(1, input.length() - 2);
        string item;
        for (int i = 0, f = 0; i < input.size(); ++i) {
            char ch = input[i];
            if (ch == '\"') {
                if (f) {
                    f = 0; ++i;
                    output.push_back(item);
                } else {
                    f = 1;
                    item = "";
                }
            } else if (ch == '\\') {
                item += input[++i];
            } else {
                item += ch;
            }
        }
        return output;
    }

    ListNode* stringToListNode(string input) {
        // Generate list from the input
        vector<int> list = stringToIntegerVector(input);

        // Now convert that list into linked list
        ListNode* dummyRoot = new ListNode(0);
        ListNode* ptr = dummyRoot;
        for(int item : list) {
            ptr->next = new ListNode(item);
            ptr = ptr->next;
        }
        ptr = dummyRoot->next;
        delete dummyRoot;
        return ptr;
    }

    TreeNode* stringToTreeNode(string input) {
        trimLeftTrailingSpaces(input);
        trimRightTrailingSpaces(input);
        input = input.substr(1, input.length() - 2);
        if (!input.size()) {
            return nullptr;
        }

        string item;
        stringstream ss;
        ss.str(input);

        getline(ss, item, ',');
        TreeNode* root = new TreeNode(stoi(item));
        queue<TreeNode*> nodeQueue;
        nodeQueue.push(root);

        while (true) {
            TreeNode* node = nodeQueue.front();
            nodeQueue.pop();

            if (!getline(ss, item, ',')) {
                break;
            }

            trimLeftTrailingSpaces(item);
            trimRightTrailingSpaces(item);
            if (item != "null") {
                int leftNumber = stoi(item);
                node->left = new TreeNode(leftNumber);
                nodeQueue.push(node->left);
            }

            if (!getline(ss, item, ',')) {
                break;
            }

            trimLeftTrailingSpaces(item);
            trimRightTrailingSpaces(item);
            if (item != "null") {
                int rightNumber = stoi(item);
                node->right = new TreeNode(rightNumber);
                nodeQueue.push(node->right);
            }
        }
        return root;
    }

    // ---------- any to string ----------
    string integerVectorToString(vector<int> list, int length = -1) {
        if (length == -1) {
            length = list.size();
        }

        if (length == 0) {
            return "[]";
        }

        string result;
        for(int index = 0; index < length; index++) {
            int number = list[index];
            result += to_string(number) + ", ";
        }
        return "[" + result.substr(0, result.length() - 2) + "]";
    }

    string int2dArrayToString(vector<vector<int>> array) {
        if (array.size() == 0) return "[]";
    
        string output;
        for (auto item : array)
            output += integerVectorToString(item) + ",";
        
        return "[" + output.substr(0, output.length() - 1) + "]";
    }

    string stringVectorToString(vector<string> stringVector) {
        string output = "";
        for (auto str : stringVector) output += "\"" + str + "\",";
        return "[" + output.substr(0, output.length() - 1) + "]";
    }

    string treeNodeToString(TreeNode* root) {
        if (root == nullptr) {
        return "[]";
        }

        string output = "";
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            TreeNode* node = q.front();
            q.pop();

            if (node == nullptr) {
            output += "null, ";
            continue;
            }

            output += to_string(node->val) + ", ";
            q.push(node->left);
            q.push(node->right);
        }
        return "[" + output.substr(0, output.length() - 2) + "]";
    }

    // ---------- print any ----------
    void print(int integer) {
        cout << integer << endl;
    }
    
    void print(vector<int> integerVector) {
        cout << integerVectorToString(integerVector) << endl;
    }

    void print(vector<vector<int>> int2dArray) {
        cout << int2dArrayToString(int2dArray) << endl;
    }

    void print(string str) {
        cout << "\"" + str + "\"" << endl;
    }

    void print(vector<string> stringVector) {
        cout << stringVectorToString(stringVector) << endl;
    }

    void print(TreeNode* root) {
        cout << treeNodeToString(root) << endl;
    }

    // ---------- pretty print any ----------
    void prettyPrintLinkedList(ListNode* node) {
        while (node && node->next) {
            cout << node->val << "->";
            node = node->next;
        }

        if (node) {
            cout << node->val << endl;
        } else {
            cout << "Empty LinkedList" << endl;
        }
    }

    void prettyPrintTree(TreeNode* node, string prefix = "", bool isLeft = true) {
        if (node == nullptr) {
            cout << "Empty tree";
            return;
        }

        if(node->right) {
            prettyPrintTree(node->right, prefix + (isLeft ? "│   " : "    "), false);
        }

        cout << prefix + (isLeft ? "└── " : "┌── ") + to_string(node->val) + "\n";

        if (node->left) {
            prettyPrintTree(node->left, prefix + (isLeft ? "    " : "│   "), true);
        }
    }
} lc;

class Solution {
public:

};

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    string line;
    while (getline(cin, line)) {
        auto param = lc.stringToIntegerVector(line);
        //getline(cin, line);
        //auto param = lc.stringToInteger(line);
        
        //auto begin = clock();
        auto ans = Solution().function(param);
        //auto end = clock();
        //cout << endl << (double)(end - begin) / CLOCKS_PER_SEC << endl << endl;

        lc.print(ans);
    }

    return 0;
}