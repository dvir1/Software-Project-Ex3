CC = gcc
OBJS = Tester.o ParserUnitTest.o Parser.o Game.o Solver.o MainAux.o
EXEC = sudoku
COMP_FLAG = -ansi -Wall -Wextra -Werror -pedantic-errors

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@
Tester.o: Tester.c Parser.h SPBufferset.h
	$(CC) $(COMP_FLAG) -c $*.c
ParserUnitTest.o: ParserUnitTest.c ParserUnitTest.h
	$(CC) $(COMP_FLAG) -c $*.c
Parser.o: Parser.c Parser.h
	$(CC) $(COMP_FLAG) -c $*.c
Game.o: Game.c Game.h
	$(CC) $(COMP_FLAG) -c $*.c
Solver.o: Solver.c Solver.h
	$(CC) $(COMP_FLAG) -c $*.c
MainAux.o: MainAux.c MainAux.h
	$(CC) $(COMP_FLAG) -c $*.c
clean:
	rm -f $(OBJS) $(EXEC)
