/*
 * threads.c
 * Ba hàm chạy trong thread: check_row, check_col, check_subgrid.
 * Logic check giống nhau — chỉ khác cách duyệt mảng sudoku[][].
 *
 * Pattern chung:
 *   1. Khởi tạo seen[SIZE+1] = {0}
 *   2. Lặp qua 9 ô của vùng cần check
 *   3. Nếu num ngoài [1,9] hoặc seen[num] đã bật → invalid
 *   4. Đánh dấu seen[num] = 1
 *   5. Qua hết vòng lặp → valid
 */

#include <stdlib.h>
#include <pthread.h>
#include "sudoku.h"

/* ─────────────────────────────────────────
   check_row
   Kiểm tra hàng p->row chứa đủ 1–9, không trùng.
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
   Kiểm tra cột p->col chứa đủ 1–9, không trùng.
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
   Kiểm tra ô 3×3 có góc trên-trái là (p->row, p->col).
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
