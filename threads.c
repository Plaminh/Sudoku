/*
 * threads.c
 */

#include <stdlib.h>
#include <pthread.h>
#include "sudoku.h"

/* ─────────────────────────────────────────
   check_row
   ───────────────────────────────────────── */

void *check_row(void *param)
{
    parameters *p = (parameters *)param;
    int row = p->row;
    int idx = p->index;
    free(param);

    int seen[SIZE + 1];

    /// khởi tạo seen
    for (int k = 0; k <= SIZE; k++)
        seen[k] = 0;

    // check
    for (int j = 0; j < SIZE; j++)
    {
        int num = sudoku[row][j];
        if (num < 1 || num > SIZE || seen[num])
        {
            result[idx] = 0;
            pthread_exit(NULL);
        }
        seen[num] = 1;
    }
    result[idx] = 1;
    pthread_exit(NULL);
}

/* ─────────────────────────────────────────
   check_col
   ───────────────────────────────────────── */

void *check_col(void *param)
{
    parameters *p = (parameters *)param;
    int col = p->col;
    int idx = p->index;
    free(param);

    int seen[SIZE + 1];

    for (int k = 0; k <= SIZE; k++)
        seen[k] = 0;

    for (int i = 0; i < SIZE; i++)
    {
        int num = sudoku[i][col];
        if (num < 1 || num > SIZE || seen[num])
        {
            result[idx] = 0;
            pthread_exit(NULL);
        }
        seen[num] = 1;
    }
    result[idx] = 1;
    pthread_exit(NULL);
}

/* ─────────────────────────────────────────
   check_subgrid
   ───────────────────────────────────────── */

void *check_subgrid(void *param)
{
    parameters *p = (parameters *)param;
    int startR = p->row;
    int startC = p->col;
    int idx = p->index;
    free(param);

    int seen[SIZE + 1];

    for (int k = 0; k <= SIZE; k++)
        seen[k] = 0;

    for (int i = startR; i < startR + 3; i++)
    {
        for (int j = startC; j < startC + 3; j++)
        {
            int num = sudoku[i][j];
            if (num < 1 || num > SIZE || seen[num])
            {
                result[idx] = 0;
                pthread_exit(NULL);
            }
            seen[num] = 1;
        }
    }
    result[idx] = 1;
    pthread_exit(NULL);
}
