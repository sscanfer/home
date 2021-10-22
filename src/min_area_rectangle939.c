/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2020. All rights reserved.
 * Test Cases:
 * input: 3,2 3,1 4,4 1,1 4,3 0,3 0,2 4,0 A
 * output: 0
 * input: 1,1 1,3 3,1 3,3 2,2 a
 * output: 4
 * input: 1,1 1,3 3,1 3,3 4,1 4,3 a
 * output: 2
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "uthash.h"

#define POINTS_LEN 500
#define POINT_NUMS 2

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point point;       // point structure as key
    UT_hash_handle hh;
} Hash;

Hash *g_hash = NULL;   // must set as NULL
bool g_rectExisted = false;

bool TraverseFind(int **points, int pointsSize, int x, int y);
void ComputeMinArea(int **points, int pointsSize, int i, int j, int *area);
int FindMinRectangleInViolence(int **points, int pointsSize);

/*
 * Add Point to hash table
 * Description: if point is existed, return false, or add new one and return true
 */
bool AddPoint(int x, int y)
{
    Hash *find = NULL;
    Point tmp = { x, y };

    HASH_FIND(hh, g_hash, &tmp, sizeof(tmp), find);
    if (find == NULL) {
        find = (Hash*)malloc(sizeof(Hash));
        find->point.x = x;
        find->point.y = y;
        HASH_ADD(hh, g_hash, point, sizeof(Point), find);
        return true;
    }
    return false;
}

/*
 * Find Point in hash table
 * Details: if point is existed, return its hash pointer or return NULL
 */
Hash *FindPoint(int x, int y)
{
    Hash *find = NULL;
    Point tmp = { x, y };

    HASH_FIND(hh, g_hash, &tmp, sizeof(tmp), find);
    return find;
}

/*
 * Free hash table
 */
void FreeHash(Hash *hash)
{
    Hash *cur = NULL;
    Hash *tmp = NULL;
    HASH_ITER(hh, hash, cur, tmp) {
        HASH_DEL(hash, cur);
        free(cur);
        cur = NULL;
    }
}

static inline int Min(unsigned int a, unsigned int b)
{
    return a < b ? a : b;
}

void CalcMinArea(int **points, int i, int j, int *area, bool *rectExisted)
{
    if (points[i][0] != points[j][0] && points[i][1] != points[j][1]) {
        if (FindPoint(points[i][0], points[j][1]) != NULL && FindPoint(points[j][0], points[i][1]) != NULL) {
            *area = Min(abs(points[i][0] - points[j][0]) * abs(points[i][1] - points[j][1]), *area);
            *rectExisted = true;
        }
    }
}

int MinAreaRect(int **points, int pointsSize, int *pointsColSize)
{
    if (points == NULL || pointsSize <= 0) {
        return 0;
    }
    g_hash = NULL;
    for (int i = 0; i < pointsSize; i++) {
        AddPoint(points[i][0], points[i][1]);
    }
    bool rectExisted = false;
    int minArea = INT_MAX;
    for (int i = 0; i < pointsSize; i++) {
        for (int j = 0; j < pointsSize; j++) {
            if (i == j) {
                continue;
            }
            CalcMinArea(points, i, j, &minArea, &rectExisted);
        }
    }
    FreeHash(g_hash);
    if (rectExisted) {
        return minArea;
    }
    return 0;
}

int main(int argc, char **argv)
{
    int pointsSize = 0;
    int **points = (int**)malloc(POINTS_LEN * sizeof(int*));
    if (points == NULL) {
        return -1;
    }
    int pointsColSize = POINT_NUMS;
    for (int i = 0; i < POINTS_LEN; i++) {
        points[i] = (int*)malloc(POINT_NUMS * sizeof(int));
        if (points[i] == NULL) {
            return -1;
        }
    }
    while (scanf("%d,%d", &points[pointsSize][0], &points[pointsSize][1]) == 2) {
        pointsSize++;
    }

    // call user function
    int result = MinAreaRect(points, pointsSize, &pointsColSize);
    // int result = FindMinRectangleInViolence(points, pointsSize);
    printf("%d", result);

    // free dynamic memory
    for (int i = 0; i < POINTS_LEN; i++) {
        free(points[i]);
    }
    free(points);
    // FreeHash(g_hash);

    return 0;
}

// 暴力法
bool TraverseFind(int **points, int pointsSize, int x, int y)
{
    for (int i = 0; i < pointsSize; i++) {
        if (points[i][0] == x && points[i][1] == y) {
            return true;
        }
    }
    return false;
}

void ComputeMinArea(int **points, int pointsSize, int i, int j, int *area)
{
    if (points[i][0] != points[j][0] && points[i][1] != points[j][1]) {
        if (TraverseFind(points, pointsSize, points[i][0], points[j][1]) &&
            TraverseFind(points, pointsSize, points[j][0], points[i][1])) {
            *area = Min(abs(points[i][0] - points[j][0]) * abs(points[i][1] - points[j][1]), *area);
            g_rectExisted = true;
        }
    }
}

int FindMinRectangleInViolence(int **points, int pointsSize)
{
    if (points == NULL || pointsSize <= 0) {
        return 0;
    }
    int minArea = INT_MAX;
    for (int i = 0; i < pointsSize; i++) {
        for (int j = 0; j < pointsSize; j++) {
            if (i == j) {
                continue;
            }
            ComputeMinArea(points, pointsSize, i, j, &minArea);
        }
    }
    if (g_rectExisted) {
        return minArea;
    }
    return 0;
}