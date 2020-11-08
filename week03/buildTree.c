/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 * 时间复杂度O(n),空间复杂度O(n)
 * https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/solution/c-di-gui-tu-jie-by-mrggls-t/
 */
 struct TreeNode* build(int* preorder,int pStart,int pEnd,int* inorder,int iStart,int iEnd)
 {
     if(pStart>pEnd)//只有在pStart小于等于pEnd的情况下才创建新节点
        return NULL;
    struct TreeNode* root=(struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val=preorder[pStart];
    int index=-1;
    for(int i=iStart;i<=iEnd;i++)
        if(inorder[i]==preorder[pStart])//找出根节点在中序遍历数组中的位置
        {
            index=i;
            break;
        }
    root->left=build(preorder,pStart+1,pStart+index-iStart,inorder,iStart,index-1);
    root->right=build(preorder,pStart+index-iStart+1,pEnd,inorder,index+1,iEnd);
    return root;
 }

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize){
    if(preorderSize==0)
        return NULL;
    return build(preorder,0,preorderSize-1,inorder,0,inorderSize-1);
}
