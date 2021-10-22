#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} List;

// 头插法
bool ListInsert(List *head, int val)
{
    List *node = NULL;
    node = (List*)malloc(sizeof(List));
    if (node == NULL) {
        return false;
    }
    node->val  = val;
    node->next = head->next;
    head->next = node;
    return true;
}

void SwapVal(List *front, List *rear)
{
    int tmp    = front->val;
    front->val = rear->val;
    rear->val  = tmp;
}

// 迭代法
void ListReverseIteratively(List *head)
{
    List *front = head; // front始终指向前一个位置(带头结点链表的特点)
    List *rear = NULL;
    List *tmp = NULL;    // 缓存上一次rear位置
    while (front != rear && front->next != rear) {
        rear = front;
        while (rear->next != tmp) {
            rear = rear->next;
        }
        SwapVal(front->next, rear);
        front = front->next;
        tmp = rear;
    }
}

// 迭代法反转从 m 到 n 的部分，编号从 1 开始
bool ListReverseIteratively_Partially(List *head, int m, int n)
{
    // 异常处理
    if (m < 1 || n < m) {
        return false;
    }

    List *front = head;
    for (int i = 1; i < m; i++) {     // 定位m的位置
        if (front->next == NULL) {
            return false;
        }
        front = front->next;
    }
    List *rear = front->next; // front始终指向前一个位置(带头结点链表的特点), 所以这里next, 否则少移动一位
    for (int i = 0; i < n - m; i++) { // 定位n的位置
        if (rear->next == NULL) {
            return false;
        }
        rear = rear->next;
    }

    List *tmp = rear;                 // 缓存上一次rear位置
    while (front != rear && front->next != rear) {
        SwapVal(front->next, rear);
        tmp = rear;
        rear = front;
        while (rear->next != tmp) {
            rear = rear->next;
        }
        front = front->next;
    }

    return true;
}

// 递归法反转整个链表
List *ListReverseRecursively(List *head)
{
    if (head->next == NULL) {
        return head;
    }
    List *last = ListReverseRecursively(head->next);
    head->next->next = head;
    head->next = NULL;
    return last;
}

// 递归反转链表的前n个节点
List *tmp = NULL; // 缓存后面的节点
List *ListReverseN(List *head, int n)
{
    if (n == 1) {
        tmp = head->next;
        return head;
    }
    List *last = ListReverseN(head->next, n - 1);
    head->next->next = head;
    head->next = tmp; // 将反转后的节点与后面的节点连接
    return last;
}

// 递归地反转链表的一部分
List *ListReverseRecursively_Partially(List *head, int m, int n)
{
    if (m == 1) {
        return ListReverseN(head, n);
    }
    head->next = ListReverseRecursively_Partially(head->next, m - 1, n - 1);
    return head;
}

void ListTraverse(List *head)
{
    for (List *p = head; p->next != NULL; p = p->next) {
        printf("%d ", p->next->val);
    }
}

int main(int argc, char **argv)
{
    // 创建单链表头节点
    List *head = NULL;
    head = (List*)malloc(sizeof(List));
    if (head == NULL) {
        return -1;
    }
    head->next = NULL;

    // 根据输入建立单链表，头插法，与输入逆序
    int num = 0;
    if (scanf("%d", &num) != 1 || num <= 0) {
        printf("invalid num!\n");
        return -1;
    }
    int tmp;
    for (int i = 0; i < num; i++) {
        if (scanf("%d", &tmp) != 1) {
            printf("input error!\n");
            return -1;
        }
        if (ListInsert(head, tmp) != true) {
            printf("insert error\n");
            return -1;
        }
    }
    // 反转前
    printf("Before reverse: ");
    ListTraverse(head);
    printf("\n");

    // ListReverseIteratively(head);
    ListReverseIteratively_Partially(head, 2, 5);

    // 反转后
    printf("After reverse:  ");
    ListTraverse(head);
    printf("\n");

    return 0;
}