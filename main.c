/*
 * main.c
 * Khởi tạo 27 threads, join, in kết quả.
 *
 * Compile:  make
 * Run:      ./sudoku
 */

#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

/* ─────────────────────────────────────────
   GLOBAL DEFINITIONS  (declared extern in sudoku.h)
   ───────────────────────────────────────── */

int sudoku[SIZE][SIZE] = {
    {6, 2, 4, 5, 3, 9, 1, 8, 7},
    {5, 1, 9, 7, 2, 8, 6, 3, 4},
    {8, 3, 7, 6, 1, 4, 2, 9, 5},
    {1, 4, 3, 8, 6, 5, 7, 2, 9},
    {9, 5, 8, 2, 4, 7, 3, 6, 1},
    {7, 6, 2, 3, 9, 1, 4, 5, 8},
    {3, 7, 1, 9, 5, 6, 8, 4, 2},
    {4, 9, 6, 1, 8, 2, 5, 7, 3},
    {2, 8, 5, 4, 7, 3, 9, 1, 6}
};

int result[NUM_THREADS];

/* ─────────────────────────────────────────
   HELPER — allocate + fill a parameters struct
   ───────────────────────────────────────── */

static parameters *make_param(int row, int col, int index)
{
    parameters *p = malloc(sizeof(parameters));
    if (!p) { perror("malloc"); exit(1); }
    p->row   = row;
    p->col   = col;
    p->index = index;
    return p;
}

/* ─────────────────────────────────────────
   MAIN
   ───────────────────────────────────────── */

int main(void)
{
    pthread_t threads[NUM_THREADS];
    int t = 0;   /* thread index, always pass as data->index then t++ */

    print_board();

    /* ── ROW THREADS  (t = 0..8) ──────────────────────── */
    for (int i = 0; i < SIZE; i++) {
        /* TODO: thay ??? bằng giá trị đúng */
        pthread_create(&threads[t], NULL, check_row,
                       make_param(i, 0, t));
        t++;
    }

    /* ── COLUMN THREADS  (t = 9..17) ──────────────────── */
    for (int j = 0; j < SIZE; j++) {
        /* TODO: thay ??? bằng giá trị đúng */
        pthread_create(&threads[t], NULL, check_col,
                       make_param(0, j, t));
        t++;
    }

    /* ── SUBGRID THREADS  (t = 18..26) ────────────────── */
    /*
     * 9 subgrids, top-left corners:
     *   (0,0)(0,3)(0,6)
     *   (3,0)(3,3)(3,6)
     *   (6,0)(6,3)(6,6)
     */
    for (int i = 0; i < SIZE; i += 3) {
        for (int j = 0; j < SIZE; j += 3) {
            /* TODO: thay ??? bằng giá trị đúng */
            pthread_create(&threads[t], NULL, check_subgrid,
                           make_param(i, j, t));
            t++;
        }
    }

    /* ── JOIN ──────────────────────────────────────────── */
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    /* ── PRINT RESULT ──────────────────────────────────── */
    int valid = 1;
    for (int i = 0; i < NUM_THREADS; i++) {
        if (result[i] == 0) { valid = 0; break; }
    }

    printf("\nSudoku solution is %s.\n", valid ? "VALID" : "INVALID");
    return 0;
}
