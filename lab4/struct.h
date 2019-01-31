/*
   struct.h
   Richard Coffey
   ECE 223
   Program #4
*/

#include "list.h"

typedef struct hash_table 
{
    list *table; //array of linked lists - dynamically allocated
    int size; //number of elements in array
    
} hash_table;

typedef struct book_word
{
    char word[128]; //null terminated ascii key
    int count[2]; //0 for the first book, 1 for the second book
    int len;
    
} book_word;

typedef struct stats_table {
 
    int drac_word_count, frank_word_count, com_word_count;;
    int drac_uni, frank_uni, com_uni;
    book_word *drac_large[6], *frank_large[6], *com_large[6];
    book_word *drac_mfreq[16], *frank_mfreq[16], *com_mfreq[16];
    book_word *drac_lfreq[6], *frank_lfreq[6], *com_lfreq[6];

} stats_table;








