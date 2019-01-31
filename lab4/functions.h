/*
functions.h
Richard Coffey
ECE 2230
Program 4
*/

#include "struct.h"
#include <stdio.h>

hash_table *hash_init();

//key = word, data = struct book_word
void *hash_insert(struct hash_table *h, char *key, void *data); 

void *hash_search(struct hash_table *h, char *key);

int h(char *p, int m);

int stats_word(book_word *word, stats_table *stats, int book);

void hash_free(hash_table *hash); 
