/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

// 不能数组作为哈希表，因为元素有负值，下标不能有负数
#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"

#define MAX_NUMS_SIZE 10000


typedef struct {
    int            num;
    int            idx;
    UT_hash_handle hh;
} Hash;

Hash *head = NULL;

int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    int      another;
    int     *ret        = NULL;
    Hash    *find       = NULL;

    // returnSize     = (int*)malloc(sizeof(int));
    // if (returnSize == NULL) {
    //     return NULL;
    // }
    *returnSize = 2;

    for (int i = 0; i < numsSize; i++) {
        find    = NULL;
        another = target - nums[i];
        HASH_FIND_INT(head, &another, find);
        if (find == NULL) {
            find      = (Hash*)malloc(sizeof(Hash));
            find->num = nums[i];
            find->idx = i;
            HASH_ADD_INT(head, num, find);
        } else {
            ret = malloc(*returnSize * sizeof(int));
            if (ret == NULL) {
                return NULL;
            }
            ret[0] = i;
            ret[1] = find->idx;
            return ret;
        }
    }

    return ret;
}

int main(int argc, char **argv)
{
    int  numsSize;
    int *nums      = NULL;
    int  target;
    int *ret;
    int retSize;

    // input numsSize
    if (scanf("%d", &numsSize) != 1 || numsSize <= 0 || numsSize > MAX_NUMS_SIZE) {
        return -1;
    }
    nums = (int*)malloc(numsSize * sizeof(int));
    if (nums == NULL) {
        return -2;
    }

    // input nums
    for (int i = 0; i < numsSize; i++) {
        if (scanf("%d", &nums[i]) != 1) {
            return -3;
        }
    }

    // input target
    if (scanf("%d", &target) != 1) {
        return -4;
    }

    ret = twoSum(nums, numsSize, target, &retSize);
    if (ret != NULL) {
        for (int i = 0; i < retSize; i++) {
            printf("%d ", ret[i]);
        }
    }

    return 0;
}