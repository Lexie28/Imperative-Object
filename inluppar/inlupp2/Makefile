FLAGS = -g -Wall -pedantic 

%.o: %.c %.h
	gcc $(FLAGS) -c $< -o $@

frontend: frontend.o utils.o common.o linked_list.o iterator.o hash_table.o backend.o
	gcc $(FLAGS) -o $@.out $^

backtests: backtests.c utils.o common.o linked_list.o iterator.o hash_table.o backend.o
	gcc $(FLAGS) $^ -o backtests -lcunit

memtest:
	valgrind --show-leak-kinds=all --leak-check=full ./backtests

uitest:
	valgrind --show-leak-kinds=all --leak-check=full --track-origins=yes ./frontend.out

clean:
	rm -rf *.o
	rm -rf backtests
	rm -rf frontend
