/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numChildren;
 *     struct Node** children;
 * };
 */

/**
 * 时间复杂度O(n),空间复杂度O(n),https://leetcode-cn.com/problems/n-ary-tree-preorder-traversal/description/
 */
#define MAX_SIZE 10000
void traval(struct Node* root, int* result, int* returnSize) {
    result[(*returnSize)++] = root->val;
    for(int i = 0; i < root->numChildren; i++) {
        traval(root->children[i], result, returnSize);
    }
}

int* preorder(struct Node* root, int* returnSize) {
    int *result = (int*)calloc(MAX_SIZE, sizeof(int));
    *returnSize = 0;
    if (root == NULL) return NULL;

    traval(root, result, returnSize);
    return result;
}