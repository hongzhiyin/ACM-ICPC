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

    vector<string> stringToStringVector(string input) {
        vector<string> output;
        trimLeftTrailingSpaces(input);
        trimRightTrailingSpaces(input);
        input = input.substr(1, input.length() - 2);
        stringstream ss;
        ss.str(input);
        string item;
        char delim = ',';
        while (getline(ss, item, delim)) {
            item = item.substr(1, item.length() - 2);
            output.push_back(item);
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

    string stringVectorToString(vector<string> stringVector) {
        string output = "";
        for (auto str : stringVector) output += "\"" + str + "\",";
        return "[" + output.substr(0, output.length() - 1) + "]";
    }

    // ---------- read any ----------
    vector<string> readStringVector() {
        string line;
        getline(cin, line);
        return stringToStringVector(line);
    }

    // ---------- print any ----------
    void print(vector<string> stringVector) {
        cout << stringVectorToString(stringVector) << endl;
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

} solution;

int main()
{
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);

    auto param = lc.read();
    
    auto ans = solution.fun(param);

    lc.print(ans);    

    return 0;
}