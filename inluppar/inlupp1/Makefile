FLAGS = -g -Wall -pedantic 

hash_table: hash_table.c hashtests.c
	gcc $(FLAGS) hash_table.c hashtests.c -o hashtests -lcunit

memtest: hash_table
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./hashtests 

linked_lists: linked_list.c linkedtests.c
	gcc $(FLAGS) linked_list.c linkedtests.c -o linkedtests -lcunit

coverage: hash_table.c hashtests.c
	gcc -Wall -fprofile-arcs -ftest-coverage hash_table.c hashtests.c -o hashtests -lcunit