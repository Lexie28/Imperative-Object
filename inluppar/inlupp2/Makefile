FLAGS = -g -Wall -pedantic 

frontend: utils.c common.c linked_list.c iterator.c hash_table.c backend.c frontend.c
	gcc $(FLAGS) utils.c common.c linked_list.c iterator.c hash_table.c backend.c frontend.c -o frontend

dbtests:
	gcc $(FLAGS) frontend.c backend.c hash_table.c linked_list.c common.c dbtests.c -o dbtests
