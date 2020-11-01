/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

/*时间复杂度O(n),空间复杂度O(n)
https://leetcode-cn.com/problems/n-ary-tree-level-order-traversal/submissions/*/
class Solution {
public:
    int depth = 0;
    vector<vector<int>> levelOrder(Node* root) {
        findDepth(root, 0);
        vector<vector<int>> res(depth); //初始化数组
        queue<Node*> q;
        q.push(root);
        for(int m = 0; m < depth; ++ m){ // 以层为单位遍历整棵树
            int layer = q.size();
            for(int i = 0; i < layer; ++ i){ // 迭代处理当前层的每个节点
                res[m].push_back(q.front() -> val);
                for(auto j : q.front() -> children){ // 将当前层的children压入队列
                    q.push(j);
                }
                q.pop();
            }
        }
        return res;
    }
    void findDepth(Node* root, int d){ //寻找深度，用以初始化数组
        if(!root)   return;
        ++ d;
        depth = max(d, depth);
        for(auto i : root -> children){
            findDepth(i, d);
        }
        
    }
};