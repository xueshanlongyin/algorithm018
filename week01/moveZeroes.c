void moveZeroes(int* nums, int numsSize){
    if (nums == NULL || numsSize <= 0) {
        return;
    }

    int j = 0;
    for(int i = 0; i < numsSize; i++) {
        if(nums[i] != 0) {
            int tmp = nums[i];
            nums[i] = nums[j];
            nums[j++] = tmp;
        }
    }
}