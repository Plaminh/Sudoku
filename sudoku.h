/*
 * sudoku.h
 */

#ifndef SUDOKU_H
#define SUDOKU_H

#include <pthread.h>

/* ─────────────────────────────────────────
   CONSTANTS
   ───────────────────────────────────────── */

#define SIZE        9
#define NUM_THREADS 27   /* 9 rows + 9 cols + 9 subgrids */

/* ─────────────────────────────────────────
   SHARED GLOBALS  (defined in main.c)
   ───────────────────────────────────────── */

extern int sudoku[SIZE][SIZE];   /* the puzzle                        */
extern int result[NUM_THREADS];  /* result[i] = 1 valid, 0 invalid    */

/* ─────────────────────────────────────────
   PARAMETER STRUCT
   ───────────────────────────────────────── */

typedef struct {
    int row;    /* starting row   (row check & subgrid)  */
    int col;    /* starting col   (col check & subgrid)  */
    int index;  /* owns result[index]                    */
} parameters;

/* ─────────────────────────────────────────
   threads.c — THREAD FUNCTIONS
   ───────────────────────────────────────── */

void *check_row    (void *param);
void *check_col    (void *param);
void *check_subgrid(void *param);

/* ─────────────────────────────────────────
   utils.c — HELPER FUNCTIONS
   ───────────────────────────────────────── */

void print_board (void);
void load_board  (int src[SIZE][SIZE]);
int  read_board_from_file(const char *filename);
void print_results       (void);

#endif /* SUDOKU_H */
