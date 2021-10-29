CC = gcc
FLAGS =  -Wall -g
PROGS = snake

all : $(PROGS)

snake : main.o snake.o game.o sleep.o apple.o
	$(CC) $(FLAGS) -o $@ $^ -lncurses

main.o : main.c include/game.h
	$(CC) $(FLAGS) -c $<

snake.o : src/snake.c include/snake.h common/common.h
	$(CC) $(FLAGS) -c $<

game.o : src/game.c include/*.h common/common.h
	$(CC) $(FLAGS) -c $<

sleep.o : common/sleep.c common/sleep.h
	$(CC) $(FLAGS) -c $<

apple.o: src/apple.c include/apple.h
	$(CC) $(FLAGS) -c $<

run:
	./$(PROGS)

clean: 
	rm -f *.o $(PROGS)