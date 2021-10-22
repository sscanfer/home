#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARR_MAX_SIZE 16
#define MAXLEN 26 // 最多26个英文字母，也即掩码中1的个数

// 计算掩码，如果字符串自身含有重复字符，返回0
unsigned int CalcMask(const char *str, int len)
{
    unsigned int mask = 0;
    for (int i = 0; i < len; i++) {
        if ((mask >> (str[i] - 'a')) & 0x1) {
            return 0;
        }
        mask |= 0x1 << (str[i] - 'a');
    }
    return mask;
}

// 统计掩码中1的个数，也即结果字符串的长度
int CountMask(unsigned int mask)
{
    int cnt = 0;
    for (int i = 0; i < MAXLEN; i++) {
        if ((mask >> i) & 0x1) {
            cnt++;
        }
    }
    return cnt;
}

int result;

// 递归函数backtrace(pos, mask)的定义：判断maskSet[pos]，是否与mask中重复
void BackTrace(unsigned int *maskSet, int maskSetSize, int pos, unsigned int mask)
{
    if (pos == maskSetSize) {
        int tmp = CountMask(mask);
        result = tmp > result ? tmp : result;
        return;
    }
    if ((maskSet[pos] & mask) == 0) { // maskSet[pos] 与结果不重复，加入结果，继续判断下一字符串
        BackTrace(maskSet, maskSetSize, pos + 1, mask | maskSet[pos]);
    }
    BackTrace(maskSet, maskSetSize, pos + 1, mask); // 这里之前错误地放在了else分支，导致少了情况
}

int MaxLength(const char **arr, int arrSize)
{
    // 异常处理
    if (arr == NULL || arrSize <= 0 || arrSize > ARR_MAX_SIZE) {
        return 0;
    }

    result = 0;

    unsigned int *maskSet = (unsigned int*)malloc(arrSize * sizeof(unsigned int));
    if (maskSet == NULL) {
        printf("malloc error\n");
        return -1;
    }

    int maskSetSize = 0;
    unsigned int mask;
    for (int i = 0; i < arrSize; i++) {
        mask = CalcMask(arr[i], strlen(arr[i]));
        if (mask != 0) {
            maskSet[maskSetSize] = mask;
            maskSetSize++;
        }
    }

    BackTrace(maskSet, maskSetSize, 0, 0);

    // 释放内存，以后记得成对的写
    free(maskSet);

    return result;
}

int main(int argc, char **argv)
{
    const char *arr[] = { "cha", "r", "act", "ers" };

    int result = MaxLength(arr, 4);
    printf("%d\n", result);

    return 0;
}