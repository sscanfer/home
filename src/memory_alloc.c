#include <stdio.h>
#include <stdbool.h>

// 用例足够使用
#define BUF_LEN 64
#define OUT_BUF_LEN 64

#define MEM_MAX 100
#define UNUSED 0
#define ALLOCATED 1

int g_memLeft = MAX_MEM;

typedef struct MemNode {
    int index;
    int size;
    int status;
    struct MemNode *prev;
    struct MemNode *next;
} MemPool;

MemPool *head = NULL;

// 在此添加你的代码
void MemPoolInit(void)
{
    head = (MemPool*)malloc(sizeof(struct MemNode));
    head->index  = 0;
    head->size   = 0;
    head->status = ALLOCATED;
    head->prev   = NULL;
    head->next   = NULL;

    return;
}

// 在此添加你的代码
void MemPoolDeinit(void)
{
    for (MemPool *p = head; p->next != NULL; p = p->next) {
        free(p->next);
    }
    free(head);
}

void MemNodeInsert(MemPool *p, int memSize)
{
    int overage;
    p->status = ALLOCATED; // 长度正好匹配，只需改变状态
    if (p->size > memSize) {
        overage = p->size - memSize;
        if (p->next != NULL && p->next->status == UNUSED) { // 合并多余内存到后面的未分配内存
            p->next->index -= overage;
            p->next->size += overage;
        } else {                                            // 不可合并，新建节点
            MemPool *newNode = (MemPool*)malloc(sizeof(struct MemNode));
            newNode->index = p->index + memSize;
            newNode->size = overage;
            newNode->status = UNUSED;
            newNode->prev = p;
            newNode->next = p->next;
            p->next->prev = newNode; // 维护p->next;
            p->size = memSize;       // 维护p;
            p->next = newNode;
        }
    }
    return;
}

/* 返回分配的内存首地址，失败返回 -1，框架会自动输出"error" */
int MemPoolRequest(int memSize)
{
    if (memSize <= g_memLeft) {
        for (MemPool *p = head->next; p != NULL; p = p->next) {
            if (p->status == UNUSED && p->size >= memSize) {
                MemNodeInsert(p, memSize);
                return p->index;
            }
        }
    }
    return -1;
}

void MemNodeRemove(MemPool *p)
{
    p->status = UNUSED;
    if (p->next != NULL && p->next->status == UNUSED) {
        p->size += p->next->size;
        p->next = p->next->next;
        p->next->
        free(p->next);
    }
    if (p->prev != NULL && p->prev->status == UNUSED) {
        p->prev->size += p->size;
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }

}

/* 成功返回 true；失败返回 false，框架会自动输出 "error" */
bool MemPoolRelease(int startAddr)
{
    // 异常输入处理
    if (startAddr < 0 || startAddr > MEM_MAX - 1) {
        return false;
    }
    for (MemPool *p = head->next; p != NULL; p = p->next) {
        if (p->index == startAddr && p->status == ALLOCATED) {
            MemNodeRemove(p);
        }
    }
    return true;
}

int main(void)
{
    MemPoolInit();

    int n;
    if (scanf_s("%d\n", &n) != 1)   { return -1; }

    char buf[BUF_LEN];
    for (int i = 0; i < n; i++) {
        if (gets_s(buf, sizeof(buf)) == NULL)   { return -1; }
        int info = atoi(buf + 8);
        if (buf[2] == 'Q') { // REQUEST
            int addr = MemPoolRequest(info);
            if (addr != -1) {
                (void)printf("%d\n", addr);
            } else { (void)printf("error\n"); }
        } else { // RELEASE
            bool ret = MemPoolRelease(info);
            if (ret == false) { (void)printf("error\n"); }
        }
    }

    MemPoolDeinit();
    return 0;
}