CC	= gcc
CFLAGS	= -pthread
RM	= rm- f

default: all

all: Sudoku

Sudoku: sudoku.c
	$(CC) $(CFLAGS) -o Sudoku sudoku.c
	
clean veryclean:
	$(RM) Sudoku
