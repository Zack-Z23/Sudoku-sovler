CC = gcc
CFLAGS =  -I$(IDIR)

IDIR = ./include/
SRCDIR  = ./src/

SOURCES = ${SRCDIR}*.c

all: sudoku run clean

sudoku:
	${CC} ${SOURCES} ${CFLAGS} -o $@

run:
	./sudoku

clean:
	del sudoku.exe