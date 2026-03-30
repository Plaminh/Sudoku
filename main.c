/*
 * main.c
 * Compile:  make
 * Run:      ./sudoku
 */

#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

/* ─────────────────────────────────────────
   GLOBAL DEFINITIONS  (declared extern in sudoku.h)
   ───────────────────────────────────────── */
int sudoku[SIZE][SIZE];

int result[NUM_THREADS];

/* ─────────────────────────────────────────
   HELPER — allocate + fill a parameters struct
   ───────────────────────────────────────── */

static parameters *make_param(int row, int col, int index)
{
    parameters *p = malloc(sizeof(parameters));
    if (!p)
    {
        perror("malloc");
        exit(1);
    }
    p->row = row;
    p->col = col;
    p->index = index;
    return p;
}

/* ─────────────────────────────────────────
   MAIN
   ───────────────────────────────────────── */

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./sudoku <file.csv>\n");
        return 1;
    }
    if (read_board_from_file(argv[1]) != 0)
        return 1;

    pthread_t threads[NUM_THREADS];
    int t = 0; /* thread index, always pass as data->index then t++ */

    print_board();

    /* ── ROW THREADS  (t = 0..8) ──────────────────────── */
    for (int i = 0; i < SIZE; i++)
    {
        pthread_create(&threads[t], NULL, check_row,
                       make_param(i, 0, t));
        t++;
    }

    /* ── COLUMN THREADS  (t = 9..17) ──────────────────── */
    for (int j = 0; j < SIZE; j++)
    {
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
    for (int i = 0; i < SIZE; i += 3)
    {
        for (int j = 0; j < SIZE; j += 3)
        {
            pthread_create(&threads[t], NULL, check_subgrid,
                           make_param(i, j, t));
            t++;
        }
    }

    /* ── JOIN ──────────────────────────────────────────── */
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    /* ── PRINT RESULT ──────────────────────────────────── */
    print_results();

    int valid = 1;
    for (int i = 0; i < NUM_THREADS; i++)
        if (result[i] == 0)
        {
            valid = 0;
            break;
        }

    printf("\n>>> Sudoku solution is %s. <<<\n", valid ? "VALID" : "INVALID");
    return 0;
}
