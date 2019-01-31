README.txt
Richard Coffey
ECE 223
Program 4

Compilation Command: 

"gcc -Wall -g prog4.c functions.c functions.h list.c list.h struct.h -o prog"

Flags:

-d [first book]
-f [second book]

Running the program:

./prog4 -d dracwords.txt -f frankwords.txt

You can also use any two other novels, althought the variable names will remain for these two novels


Files:
**NOTE**: Merged hash_func.c with functions.c

Prog4.c

main():
-uses getopt to parse flags
-allocates stats table for passing
-calls hash_init to init hash_table
-calls parse_file to build hash table
-call print_stats to print stats
-frees hash table and stats table

parse_file();
-opens files and load words into a buffer for hash_search and hash_insert to work
-keeps track of total words count

print_stats():
-calls stat_word for each word in built hash_table to build stats table
-formats output



functions.h
-Contains headers for functions.ci

struct.h
-contains typedefs for structures

list.h
-contains headers and structs for list.c

list.c
-Contains linked list functions used in previous labs

Functions.c
-Most of the complex functions are in here

hash_init()
-Allocates hash_table
-Allocates array of linked lists
-inits all of them using HSZ constant

hash_insert()
-calculates hash value from key
-appends to linked list at hash value

hash_search()
-computes hash value
-checks if there is a collison
-returns NULL if space is empty
-if there is a collison, uses list_next to iterate until it matches key or find an empty space in the linked list
-returns found space and whatever is in it

h()
-computes hash value
-made by professor ligon, just use output

stats_word()
-take a book_word and enters a switch statement depending on the book
-keeps track of length, and most/least usage by a set of comparisons to the arrays in stats_table

hash_free()
-frees the data in each node, then finalizes the linked lists
-frees the hash_table























