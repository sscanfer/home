// https://blog.csdn.net/xiaonuo911teamo/article/details/117540212
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_LEN 65536

const char g_vowels[] = "aeiouAEIOU";

bool IsVowel(char c)
{
    if (strchr(g_vowels, c) != NULL) {
        return true;
    }
    return false;
}

int GetSubstrLen(int flaw, char *str, int *start, int *len)
{
    int cnt = 0;
    bool flag = false;
    int left = *start;
    while (left < strlen(str) && !IsVowel(str[left])) {  // 跳过开头的非元音字母
        left++;
    }
    for (int i = left; i < strlen(str); i++) {   // n个元音 + flaw + m个元音
        if (!flag && !IsVowel(str[i])) {  // 找flaw
            if (cnt < flaw) {
                cnt++;
            } else {
                flag = true;
                // continue;
            }
        }
        if (flag && !IsVowel(str[i])) { // 满足flaw后的最后一个元音字母m
            if (i - left < *len) {
                *len = i - left;
            }
            *start = i;
            break;
        }
    }
    *start = left;
    return left;
}

int GetLongestFlawedVowelSubstrLen1(int flaw, char* str)
{
    int bp = 0;
    int fp = 0;
    bool flag = false;
    for (int i = 0; i < flaw; i++) {
        for (int j = 0; j < strlen(str); j++) {
            if (!IsVowel(str[j])) {

            }
        }
    }
    int cnt = 0;
    int len = 0;
    for (int i = 0; i < strlen(str); i++) {  // 第一次遍历，先找够flaw
        if (!flag && !IsVowel(str[i])) {
            if (cnt < flaw) {
                cnt++;
            } else {
                flag = true;
                continue;
            }
        }
        if (flag && !IsVowel(str[i])) {
            return i - 0;
        }
    }
}

int GetLongestFlawedVowelSubstrLen(int flaw, char* str)
{
    int maxLen = 0;
    int len = 0;
    int preLen;
    int tmp;
    bool flag;
    for (int i = 0; i < strlen(str); i += preLen) {  // think 边界
        preLen = 1;
        len = 0;
        tmp = 0;
        flag = false;
        if (IsVowel(str[i])) {
            for (int j = i; j < strlen(str); j++) {
                if (!flag && IsVowel(str[j])) {
                    len++;
                    preLen = len;  // 利用已有结果，下次使用
                } else {
                    if (tmp != flaw) {
                        tmp++;
                        len++;
                        preLen += len;
                    } else {
                        flag = true;  // 暂时放下一种情况，flaw=0
                        if (IsVowel(str[j])) {
                            len++;
                        } else {
                            if (len > maxLen) {
                                maxLen = len;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    return maxLen;
}


int main(void)
{
    int flaw = 0;
    if (scanf("%d\n", &flaw) != 1) { return -1; }
    char str[MAX_LEN];
    if (scanf("%s", str) != 1) { return -1; }
    // int result = GetLongestFlawedVowelSubstrLen(flaw, str);
    int start = 0;
    int len = INT_MAX;
    int result = GetSubstrLen(flaw, str, &start, &len);
    (void)printf("%d", result);
    return 0;
}
