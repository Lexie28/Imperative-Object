# Initial Profiling Results
For each input, what are the top 3 functions?
1. string_eq
2. find_previous_entry_for_key
3. string_sum_hash
For each input, what are the top 3 functions in your code (that you have written), or is it library functions?
    Same as before?
Are the top 3 functions in your code consistent across the inputs? Why? Why not?
    Because the procedure to process the file and all words is the same regardless of the file, the only difference is that there will be more calls.
Is there some kind of trend? (Possibly several.)
    There is always the same amount of calls to find_previous_entry_for_key and string_sum_hash. Both are used within hash_table_lookup and hash_table_insert, and every time we make an equal amount of calls to these two functions.
Do the results correspond with your expectations?
    Initially we thought that hash_table_insert and hash_table_lookup would be part of the top three functions with the motivation that they were used the most in process word which we call for every word. However the results were one layer deeper in which the function calls within hash_table_insert och hash_table_lookup were the top 3, find_previous_entry_for_key which is used once in both, string_sum_hash also used once in both, and string_eq which is used in find_previous_entry_for_key.
Based on these results, do you see a way to make your program go faster?
    Since our top three functions are all function calls within another function, the best way to speed it up would be to call these directly, but this would make the code more complicated and would not really make sense, so in the end we don’t really see a way that we could make our program go faster.