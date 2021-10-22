#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAXN 300
#define OUTPUT_BUF_LEN 512
#define TAG_CHAR1 0
#define TAG_CHAR2 1
#define LEN_CHAR1 2
#define LEN_CHAR2 3
#define LEN_CHAR3 4
#define LEN_CHAR4 5
#define VALUE_OFFSET 6

unsigned int GetTag(const unsigned char *input)
{
    return (input[TAG_CHAR1] << 1 * CHAR_BIT) + input[TAG_CHAR2];
}

unsigned int GetLength(const unsigned char *input)
{
    return (input[LEN_CHAR1] << 3 * CHAR_BIT) + (input[LEN_CHAR2] << 2 * CHAR_BIT) + 
           (input[LEN_CHAR3] << 1 * CHAR_BIT) + (input[LEN_CHAR4] << 0 * CHAR_BIT);
}

bool ValidValue(size_t inputLen, unsigned int length)
{
    unsigned int valLen = inputLen - VALUE_OFFSET;
    if (valLen >= length) {
        return true;
    }
    return false;
}

int ConvertValue(const unsigned char *input, size_t inputLen, unsigned int length, char *value)
{
    if (!ValidValue(inputLen, length)) {
        strcpy(value, "Invalid");
        return 0;
    }
    for (int i = 0; i < length; i++) {
        if (islower(input[i + VALUE_OFFSET])) {
            value[i] = toupper(input[i + VALUE_OFFSET]);
            continue;
        }
        value[i] = input[i + VALUE_OFFSET];
    }
    return 0;
}

void ParseTlv(const unsigned char *input, size_t inputLen, char outputBuf[], size_t outputBufLen)
{
    char value[OUTPUT_BUF_LEN] = { '\0' };
    unsigned int tag = GetTag(input);
    unsigned int length = GetLength(input);
    ConvertValue(input, inputLen, length, value);
    sprintf(outputBuf, "{T:%u,L:%u,V:%s}", tag, length, value);
}

int main(int argc, char **argv)
{
    unsigned char input[MAXN];
    size_t len = 0;
    unsigned int ch;
    while (scanf("%02x", &ch) == 1) {
        input[len++] = (unsigned char)ch;
    }
    
    char output[OUTPUT_BUF_LEN];
    ParseTlv(input, len, output, sizeof(output));
    (void)printf("%s", output);
    return 0;
}