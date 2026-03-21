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
    parameters *p   = (parameters *) param;
    int         row = p->row;
    int         idx = p->index;
    free(param);

    int seen[SIZE + 1];

    /* TODO: khởi tạo seen[] về 0 */

    /* TODO: loop j = 0..SIZE-1
     *   int num = sudoku[row][j];
     *   if (num < 1 || num > 9 || seen[num]) → result[idx]=0, exit
     *   seen[num] = 1;
     */

    result[idx] = 0; /* TODO: đổi thành 1 khi pass hết vòng lặp */
    pthread_exit(NULL);
}

/* ─────────────────────────────────────────
   check_col
   Kiểm tra cột p->col chứa đủ 1–9, không trùng.
   ───────────────────────────────────────── */

void *check_col(void *param)
{
    parameters *p   = (parameters *) param;
    int         col = p->col;
    int         idx = p->index;
    free(param);

    int seen[SIZE + 1];

    /* TODO: khởi tạo seen[] về 0 */

    /* TODO: loop i = 0..SIZE-1
     *   int num = sudoku[i][col];   ← đảo i/j so với check_row
     *   check seen, mark seen
     */

    result[idx] = 0; /* TODO */
    pthread_exit(NULL);
}

/* ─────────────────────────────────────────
   check_subgrid
   Kiểm tra ô 3×3 có góc trên-trái là (p->row, p->col).
   ───────────────────────────────────────── */

void *check_subgrid(void *param)
{
    parameters *p      = (parameters *) param;
    int         startR = p->row;
    int         startC = p->col;
    int         idx    = p->index;
    free(param);

    int seen[SIZE + 1];

    /* TODO: khởi tạo seen[] về 0 */

    /* TODO: loop i = startR .. startR+2
     *         loop j = startC .. startC+2
     *           int num = sudoku[i][j];
     *           check seen, mark seen
     */

    result[idx] = 0; /* TODO */
    pthread_exit(NULL);
}
