# DOCUMENTATION OF PROGRAM

Details about the sections of this program can be found in the header-file.

# RUNNING THE PROGRAM & TESTS

Running frequency count on .txt file
Makefile:
FLAGS = -g -Wall -pedantic

frontend: utils.c common.c linked_list.c iterator.c hash_table.c backend.c frontend.c
	gcc $(FLAGS) utils.c common.c linked_list.c iterator.c hash_table.c backend.c frontend.c -o frontend

In terminal:
make uitest
./ui_tests < <file you want to test> (e.g. addnonexisttocart.txt etc.)

Running backend tests:
In Makefile:
backtests: backend.c hash_table.c linked_list.c iterator.c common.c backtests.c utils.c
	gcc $(FLAGS) backend.c hash_table.c linked_list.c iterator.c common.c utils.c backtests.c -o backtests -lcunit
In terminal:
make backtests
    ./backtests

Running backend tests with memory analysis:
memtest:
	valgrind --show-leak-kinds=all --leak-check=full ./backtests


# Profiling Results

# COVERAGE ANALYSIS

# IN FRONTEND

The most important part of our testing was done through testing the frontend interaction (although backend-testing was done too, as can 
be seen below).
It is important to note that the backend-functions functionality as well as memory leakage were tested in our frontend-analysis.
We interacted with the frontend through the text-files found under the ui-tests-folder (namned with descriptive names), where we tested
different scenarios such as examples below:

- functionality for all basic functions
- negative pricing being rejected
- case of editing warehouse merch while it is in a cart - it is automatically edited in the cart too
- case of removing warehouse merch while it is in a cart - it is automatically edited in the cart too
- adding a non-existent merchandise to a cart
- adding merchandise to a non-existent cart
- removing something that does not exist in the warehouse
- adding cart after removing the previous one
- adding a large amount of carts
- calculating the cost of an empty cart
- stock of merch after a cart has been checked out

# IN BACKEND:

LCOV

LCOV was used to measure the test coverage for each file.

Results:
-
backend.c: 
line coverage: 76.9%, 356/463
functions: 85.1%, 40/47

These results demonstrate that most of the code we have written (meaning each line and loop) have been tested in our written tests. 
We have attempted to write our test such that it achieves high quality with regards to edge cases, special inputs and the functionality of each function (so that the functions follow their documentation) - and if this is true, an 100% file coverage means that we have tested all of these scenario. 
If our code and corresponding tests are written in such a way that they only consider simple cases, the test coverage does not tell us much.


# GPROF

The hash_table, linked_list and iterator functionalities were tested using the following scenario:

Gprof was used to test how many calls and the time consumed by each function when given a document and instructed to do a word-count. Gprof was used upon the test-files: small.txt, 1k-long-words.txt, 10k-words.txt and 16k-words.txt.

For each input, what are the top 3 functions?
    For every single one of the different inputs, we saw the same three functions in the top 3. These are:
1. string_eq
2. find_previous_entry_for_key
3. string_sum_hash
For each input, what are the top 3 functions in your code (that you have written), or is it library functions?
    We have written all of the top three called functions.
Are the top 3 functions in your code consistent across the inputs? Why? Why not?
    Yes, as mentioned above they are consistent across the inputs. This can be explainedd as the procedure to process each input file is the same, the only difference is the amount of words in each input (and therefore in the number of calls - but not in the proportion between them).
Is there some kind of trend? (Possibly several.)
    There is always the same amount of calls to find_previous_entry_for_key and string_sum_hash. Both are used within hash_table_lookup and hash_table_insert, and every time we call one of these functions, we add a call to both find_previous_entry_for_key and string_sum_hash, meaning their amount of calls will always be equal to each other.
Do the results correspond with your expectations?
    Initially we thought that hash_table_insert and hash_table_lookup would be within the top three functions. This inital expectation was based on the fact that these functions were call in freq-count's process_word-function. However, upon reflection we understand that the functions used within those functions - the ones that actually ended up in the top three - accumulated more calls.
Based on these results, do you see a way to make your program go faster?
    The only way to make our program go faster (based on these results) would be to potentially optimise our top three functions, which at this time does not seem possible for us. As such, we are now content with the efficiency of the program we have written. 
    