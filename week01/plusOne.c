int* plusOne(int* digits, int digitsSize, int* returnSize){
    int *result = NULL;
    for(int i = digitsSize - 1; i >= 0; i--) {
        if (digits[i] == 9) {
            digits[i] = 0;
        } else { //逢9进1,不为9结束
            digits[i]++;
            result = (int*)calloc(digitsSize, sizeof(int));
            memcpy(result, digits, digitsSize * sizeof(int));
            *returnSize = digitsSize;
            return result;
        }
    }
    //全为9
    result = (int*)calloc(digitsSize + 1, sizeof(int));
    result[0] = 1;
    *returnSize = digitsSize + 1;
    return result;
}