CC = gcc
FLAGS =  -Wall -g
PROGS = snake

all : $(PROGS)

snake : main.o snake.o game.o
	$(CC) $(FLAGS) -o $@ $^ -lncurses

main.o : main.c include/game.h
	$(CC) $(FLAGS) -c $<

snake.o : src/snake.c include/snake.h common/common.h
	$(CC) $(FLAGS) -c $<

game.o : src/game.c include/*.h common/common.h
	$(CC) $(FLAGS) -c $<

clean: 
	rm -f *.o $(PROGS)