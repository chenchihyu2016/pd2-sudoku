all: Sudoku.o giveQuestion.o solve.o transform.o
	g++ Sudoku.o giveQuestion.o -o giveQuestion
	g++ Sudoku.o solve.o -o solve
	g++ Sudoku.o transform.o -o transform
Sudoku.o: Sudoku.cpp Sudoku.h
	g++ -c Sudoku.cpp Sudoku.h
giveQuestion.o: giveQuestion.cpp Sudoku.h
	g++ -c giveQuestion.cpp
solve.o: solve.cpp Sudoku.h
	g++ -c solve.cpp
transform.o: transform.cpp Sudoku.h
	g++ -c transform.cpp
clean:
	rm **.o
