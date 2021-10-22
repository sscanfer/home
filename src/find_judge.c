#include <stdio.h>
#include <stdlib.h>

#define TRUST_LEN 10000
#define N         1000
#define TRUST_COL 2

int FindJudge(int n, int **trust, int trustSize, int *trustColSize)
{
    if (trust == NULL || trustSize < n - 1) {
        return -1;
    }
    // 统计每个人的入度和出度
    int people[N + 1][TRUST_COL] = { 0 };
    for (int i = 0; i < trustSize; i++) {
        people[trust[i][0]][0]++; // people[i][0] 表示 i 的出度, 表示 i 信任的人数
        people[trust[i][1]][1]++; // people[i][1] 表示 i 的入度, 表示信任 i 的人数
    }
    // 寻找judge, 即出度为0, 入度等于 n - 1
    for (int i = 1; i <= n; i++) {
        if (people[i][0] == 0 && people[i][1] == n - 1) {
            return i;
        }
    }
    return -1;
}

int main(int argc, char **argv)
{
    int n = 0;
    if (scanf("%d", &n) != 1) {
        return -1;
    }
    int **trust = (int**)malloc(TRUST_LEN * sizeof(int*));
    if (trust == NULL) {
        return -1;
    }
    for (int i = 0; i < TRUST_LEN; i++) {
        trust[i] = (int*)malloc(TRUST_COL * sizeof(int));
        if (trust[i] == NULL) {
            return -1;
        }
    }
    int trustSize = 0;
    while (scanf("%d,%d", &trust[trustSize][0], &trust[trustSize][1]) == 2) {
        trustSize++;
    }

    // 调用用户的函数
    int trustColSize = TRUST_COL;
    int result = FindJudge(n, trust, trustSize, &trustColSize);
    printf("%d", result);

    // 释放内存
    for (int i = 0; i < trustSize; i++) {
        free(trust[i]);
    }
    free(trust);

    return 0;
}
