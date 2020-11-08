/*
递归,时间复杂度O(n),空间复杂度O(n)
1、如果root等于p或q，说明root本身就是最近公共祖先，直接返回
2、如果root为NULL则说明到了叶子节点，直接返回
3、分别查询左节点和右节点是否能够查到p或q
若p左q右，或p右q左，说明root就是最近公共祖先
若都在一边，那么只要继续查这一边就可以了
https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/
*/
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    if (NULL == root || root == p || root == q)
        return root;

    struct TreeNode *left = lowestCommonAncestor(root->left, p, q);
    struct TreeNode *right = lowestCommonAncestor(root->right, p, q);

    if (NULL != left && NULL != right)
        return root;

    return NULL == left ? right : left;
}
