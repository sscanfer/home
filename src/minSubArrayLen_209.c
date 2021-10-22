#include <stdio.h>

int minSubArrayLen(int target, int *nums, int numsSize)
{
    if (nums == NULL || numsSize <= 0) {
        return -1;
    }
    int min = 0;
    int start = 0;
    int sum = 0;
    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
        while (sum >= target) {
            if (min == 0) {
                min = i - start + 1;
            } else {
                min = i - start + 1 < min ? i - start + 1 : min;
            }
            sum -= nums[start];
            start++;
        }
    }
    return min;
}

int main(int argc, char **argv)
{
    int nums[] = { 2,3,1,2,4,3 };
    int target = 7;

    int len = minSubArrayLen(target, nums, 6);
    printf("%d", len);

    return 0;
}