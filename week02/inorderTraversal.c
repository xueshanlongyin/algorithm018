/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


/**
 * Note: The returned array must be malloced, assume caller calls free().
 https://leetcode-cn.com/problems/binary-tree-inorder-traversal/submissions/
 */
 #define MAX_SIZE 10000

void traval(struct TreeNode* root, int* result, int* returnSize) {
    if (root->left != NULL) traval(root->left, result, returnSize);
    result[(*returnSize)++] = root->val;
    if (root->right != NULL) traval(root->right, result, returnSize);
}

int* inorderTraversal(struct TreeNode* root, int* returnSize){
   int *result = (int*)calloc(MAX_SIZE, sizeof(int));
    *returnSize = 0;
    if (root == NULL) return NULL;

    traval(root, result, returnSize);
    return result;
}