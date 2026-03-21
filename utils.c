/*
 * utils.c
 * Các hàm tiện ích: in bảng, load bảng từ nguồn khác.
 */

#include <stdio.h>
#include "sudoku.h"

/* ─────────────────────────────────────────
   print_board
   In sudoku[][] ra stdout theo dạng lưới 9×9.
   ───────────────────────────────────────── */

void print_board(void)
{
    printf("\n+-------+-------+-------+\n");
    for (int i = 0; i < SIZE; i++) {
        printf("| ");
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", sudoku[i][j]);
            if ((j + 1) % 3 == 0) printf("| ");
        }
        printf("\n");
        if ((i + 1) % 3 == 0)
            printf("+-------+-------+-------+\n");
    }
}

/* ─────────────────────────────────────────
   load_board
   Copy dữ liệu từ mảng 2D bên ngoài vào sudoku[][].
   Dùng khi muốn test nhiều puzzle mà không sửa main.c.

   Ví dụ:
       int puzzle[SIZE][SIZE] = { ... };
       load_board(puzzle);
   ───────────────────────────────────────── */

void load_board(int src[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            sudoku[i][j] = src[i][j];
}
