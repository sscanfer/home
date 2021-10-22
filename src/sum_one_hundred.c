#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 100
#define SUM 100
#define HALF 50

int MyCmp(const void *a, const void *b)
{
    return *(const int*)a - *(const int*)b;
}

int GetSumOneHundredPairs(int *arr, int arrLen)
{
    if (arr == NULL || arrLen <= 0) {
        return -1;
    }
    qsort(arr, arrLen, sizeof(int), MyCmp);
    int left = 0;
    while (arr[left] < 0) {
        left++;
    }
    int count    = 0;
    int right    = arrLen - 1;
    int leftCnt  = 0;
    int rightCnt = 0;
    int leftBuf;
    int rightBuf;
    bool halfFlag = false;
    while (left < right) {
        if (arr[left] + arr[right] > SUM) {
            right--;
        } else if (arr[left] + arr[right] == SUM) {
            leftBuf = arr[left];
            rightBuf = arr[right];
            while (arr[left] == leftBuf) {
                leftCnt++;
                left++;
            }
            if (leftBuf == HALF) {
                halfFlag = true;
            } else {
                while (arr[right] == rightBuf) {
                    rightCnt++;
                    right--;
                }
            }
            count += halfFlag ? (leftCnt * (leftCnt - 1) / 2) : leftCnt *rightCnt;
            if (halfFlag) {
                halfFlag = false;
            }
            leftCnt  = 0;
            rightCnt = 0;
        } else {
            while (arr[left] + arr[right] < SUM && left < right) {
                left++;
            }
        }
    }
    return count;
}

int FindSumOneHundredPairs(int *arr, int arrLen)
{
    if (arr == NULL || arrLen <= 0) {
        return -1;
    }
    int hash[MAX_N + 1] = { 0 };
    for (int i = 0; i < arrLen; i++) {
        if (arr[i] >= 0) {
            hash[arr[i]]++;
        }
    }
    int count = 0;
    for (int i = 0; i < MAX_N / 2; i++) {
        if (hash[i] != 0) {
            count += hash[i] * hash[MAX_N - i];
        }
    }
    int tmp = hash[MAX_N / 2] * (hash[MAX_N / 2] - 1) / 2; // 50的情况
    return count + tmp;
}

int main(int argc, char **argv)
{
    int n;
    if (scanf("%d", &n) != 1) {
        return -1;
    }
    if (n <= 0) {
        return -1;
    }
    int *arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        return -1;
    }
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            return -1;
        }
    }

    // 调用函数
    int count = FindSumOneHundredPairs(arr, n);
    // int count = GetSumOneHundredPairs(arr, n);
    printf("%d", count);

    // 释放内存
    free(arr);

    return 0;
}