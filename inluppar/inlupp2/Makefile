FLAGS = -g -Wall -pedantic 

frontend: utils.c common.c linked_list.c iterator.c hash_table.c backend.c frontend.c
	gcc $(FLAGS) utils.c common.c linked_list.c iterator.c hash_table.c backend.c frontend.c -o frontend

backtests: backend.c hash_table.c linked_list.c iterator.c common.c backtests.c utils.c
	gcc $(FLAGS) backend.c hash_table.c linked_list.c iterator.c common.c utils.c backtests.c -o backtests -lcunit

memtest:
	valgrind --show-leak-kinds=all --leak-check=full ./backtests

uitest:
	valgrind --show-leak-kinds=all --leak-check=full --track-origins=yes ./frontend

clean:
	rm -rf backtests
	rm -rf frontend

.PHONY: