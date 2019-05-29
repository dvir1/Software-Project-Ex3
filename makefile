CC = gcc
OBJS = ParserUnitTest.o Parser.o Game.o
EXEC = sudoku
COMP_FLAG = -ansi -Wall -Wextra -Werror -pedantic-errors

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@
ParserUnitTest.o: ParserUnitTest.c Parser.h SPBufferset.h
	$(CC) $(COMP_FLAG) -c $*.c
Parser.o: Parser.c Parser.h Game.h
	$(CC) $(COMP_FLAG) -c $*.c
Game.o: Game.c Game.h
	$(CC) $(COMP_FLAG) -c $*.c
clean:
	rm -f $(OBJS) $(EXEC)
