/**
 * 链接：https://leetcode-cn.com/problems/permutations-ii/solution/quan-pai-lie-ii-by-leetcode-solution/
 * 时间复杂度O(n*n!),空间复杂度O(n)
*/
int* vis;

void backtrack(int* nums, int numSize, int** ans, int* ansSize, int idx, int* perm) {
    if (idx == numSize) {
        int* tmp = malloc(sizeof(int) * numSize);
        memcpy(tmp, perm, sizeof(int) * numSize);
        ans[(*ansSize)++] = tmp;
        return;
    }
    for (int i = 0; i < numSize; ++i) {
        if (vis[i] || (i > 0 && nums[i] == nums[i - 1] && !vis[i - 1])) {
            continue;
        }
        perm[idx] = nums[i];
        vis[i] = 1;
        backtrack(nums, numSize, ans, ansSize, idx + 1, perm);
        vis[i] = 0;
    }
}

int cmp(void* a, void* b) {
    return *(int*)a - *(int*)b;
}

int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int** ans = malloc(sizeof(int*) * 2001);
    int* perm = malloc(sizeof(int) * 2001);
    vis = malloc(sizeof(int) * numsSize);
    memset(vis, 0, sizeof(int) * numsSize);
    qsort(nums, numsSize, sizeof(int), cmp);
    *returnSize = 0;
    backtrack(nums, numsSize, ans, returnSize, 0, perm);
    *returnColumnSizes = malloc(sizeof(int) * (*returnSize));
    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = numsSize;
    }
    return ans;
}