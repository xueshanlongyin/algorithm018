int removeDuplicates(int* nums, int numsSize){
    if (numsSize <= 1) return numsSize;
    int i = 0; // new array index
    for (int j = 1; j < numsSize; j++) { // old array index
        if (nums[i] != nums[j]) {
            nums[++i] = nums[j];
        }
    }
    return (i + 1); // len=i+1
}