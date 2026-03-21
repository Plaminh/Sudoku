# ─────────────────────────────────────────
# Makefile — Sudoku Validator
# ─────────────────────────────────────────

CC      = gcc
CFLAGS  = -Wall -Wextra -pthread
TARGET  = sudoku
SRCS    = main.c threads.c utils.c
OBJS    = $(SRCS:.c=.o)

# ── Default target ────────────────────────
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# ── Pattern rule: .c → .o ─────────────────
%.o: %.c sudoku.h
	$(CC) $(CFLAGS) -c $< -o $@

# ── Clean ─────────────────────────────────
clean:
	rm -f $(OBJS) $(TARGET)

# ── Run shortcut ──────────────────────────
run: all
	./$(TARGET)

.PHONY: all clean run
