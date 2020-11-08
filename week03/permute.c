/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 * 
 * 链接：https://leetcode-cn.com/problems/permutations/solution/46quan-pai-lie-ti-jie-by-goner/
 * 需要注意每一次全排列结果得到后，count应增加1;
 * count在每一次回溯时，其值不应有改变，因此将count设为全局变量，来保存得到的全排列结果个数
 * depth表示排列树的深度，回溯时应该回到上一次递归时的结果
 * 如果depth在dfs之前++depth了，则在每次dfs之后都应--depth，来恢复其状态
 * 如果depth在下一次传入dfs时直接使用depth+1的结果传入递归，则递归结束后，无需恢复其状态（本来就是原本的状态）
 * 另外分配res内存时，用numsizes的阶乘来计算空间大小
 * 时间复杂度O(n*n!),空间复杂度O(n)
 */
 

int count;

void dfs(int* nums,int numsSize,int depth,int* cur,bool* used,int** res){
    if(depth==numsSize){
        res[count]=(int*)malloc(numsSize*sizeof(int));
        memcpy(res[count++],cur,numsSize*sizeof(int));
        return;
    }

    for(int i=0;i<numsSize;++i){
        if(used[i]==true) continue;
        cur[depth]=nums[i];
        used[i]=true;
        //++depth;

        dfs(nums,numsSize,depth+1,cur,used,res);
        
        //--depth;
        used[i]=false;
    }
}

int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int s=1;
    for(int i=1;i<=numsSize;++i) s*=i;
    int** res=(int**)malloc(s*sizeof(int*));

    bool* used=(bool*)malloc(numsSize*sizeof(bool));
    memset(used,0,numsSize*sizeof(bool));

    int* cur=(int*)malloc(numsSize*sizeof(int));

    count=0;
    dfs(nums,numsSize,0,cur,used,res);
    
    *returnSize=s;
    *returnColumnSizes=(int*)malloc(s*sizeof(int));
    for(int i=0;i<s;++i) (*returnColumnSizes)[i]=numsSize;

    return res;
}