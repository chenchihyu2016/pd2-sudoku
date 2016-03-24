all: Sudoku.o  giveQuestion.cpp solve.cpp transform.cpp
	g++ giveQuestion.cpp Sudoku.o -o giveQuestion
	g++ solve.cpp Sudoku.o -o solve
	g++ transform.cpp Sudoku.o -o transform
Sudoku.o: Sudoku.cpp Sudoku.h
	g++ -c Sudoku.cpp Sudoku.h
clean:
	  rm **.o
