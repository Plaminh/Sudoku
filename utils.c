/*
 * utils.c
 * Các hàm tiện ích:
 *   - print_board()         : in bảng sudoku ra màn hình
 *   - load_board()          : copy từ mảng 2D vào sudoku[][]
 *   - read_board_from_file(): đọc puzzle từ file CSV
 *   - print_results()       : in ra thread nào PASS / FAIL
 */

#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

/* ─────────────────────────────────────────
   print_board
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
   Copy từ mảng 2D bên ngoài vào sudoku[][].
   ───────────────────────────────────────── */

void load_board(int src[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            sudoku[i][j] = src[i][j];
}

/* ─────────────────────────────────────────
   read_board_from_file
   Đọc puzzle từ file CSV, format:
       6,2,4,5,3,9,1,8,7
       5,1,9,7,2,8,6,3,4
       ...  (9 dòng, mỗi dòng 9 số cách nhau bằng dấu phẩy)

   Trả về:  0 nếu thành công
           -1 nếu lỗi
   ───────────────────────────────────────── */

int read_board_from_file(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error: cannot open file '%s'\n", filename);
        return -1;
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (fscanf(fp, "%d", &sudoku[i][j]) != 1) {
                fprintf(stderr, "Error: invalid format at row %d col %d\n",
                        i + 1, j + 1);
                fclose(fp);
                return -1;
            }
            /* bỏ qua dấu phẩy hoặc newline giữa các số */
            char ch;
            if (fscanf(fp, "%c", &ch) == 1) {
                /* ký tự separator — fscanf tự xử lý lần sau */
                (void)ch;
            }
        }
    }

    fclose(fp);
    return 0;
}

/* ─────────────────────────────────────────
   print_results
   In ra từng thread PASS hay FAIL kèm mô tả vùng.
   Gọi sau khi đã pthread_join() tất cả.
   ───────────────────────────────────────── */

void print_results(void)
{
    printf("\n%-32s %s\n", "Thread", "Status");
    printf("%-32s %s\n",   "────────────────────────────────", "──────");

    /* ROW threads: index 0–8 */
    for (int i = 0; i < SIZE; i++) {
        char label[32];
        snprintf(label, sizeof(label), "Row %d", i + 1);
        printf("%-32s %s\n", label,
               result[i] ? "PASS" : "FAIL ← invalid");
    }

    /* COL threads: index 9–17 */
    for (int j = 0; j < SIZE; j++) {
        char label[32];
        snprintf(label, sizeof(label), "Column %d", j + 1);
        printf("%-32s %s\n", label,
               result[9 + j] ? "PASS" : "FAIL ← invalid");
    }

    /* SUBGRID threads: index 18–26 */
    int t = 18;
    for (int i = 0; i < SIZE; i += 3) {
        for (int j = 0; j < SIZE; j += 3) {
            char label[32];
            snprintf(label, sizeof(label),
                     "Subgrid (%d,%d)–(%d,%d)",
                     i + 1, j + 1, i + 3, j + 3);
            printf("%-32s %s\n", label,
                   result[t] ? "PASS" : "FAIL ← invalid");
            t++;
        }
    }
}