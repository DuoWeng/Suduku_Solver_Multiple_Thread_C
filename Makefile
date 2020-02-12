all:
	cc -std=c99 sudoku.c -lpthread -o s
	
clean:
	rm  s
