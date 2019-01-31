/*
   functions.c
   Richard Coffey
   ECE 223
   Program #4
 */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"
#include "stdlib.h"

#define WSZ 256
#define HSZ 8191


hash_table *hash_init() {

    int init = 0;

    //allocate the hash_table
    hash_table *hash;
    hash = (hash_table *)malloc(sizeof(hash_table));
    if (hash == NULL) {
        free(hash);
        return NULL;
    } 
    else {

        //allocate the array of linked list
        list *tab;
        tab = (list *)malloc(HSZ * sizeof( list ));

        hash->table = tab;

        for (init = 0; init < HSZ+1; init++) {
            hash->table[init] = list_init();
        }

        return(hash);

    }    
}

//key = word, data = struct book_word
void *hash_insert(struct hash_table *ha, char *key, void *data) {

    int hash;
    book_word *word; 
    //book_word *new; 
    // new = (book_word *)calloc(1, sizeof(book_word);

    //book_word *found_word;    
    hash = h(key, HSZ);

    word = list_append(ha->table[hash], data);


    return (word);
}



void *hash_search(struct hash_table *ha, char *key) {

    int hash;
    book_word *found_word;

    hash = h(key, HSZ);

    //if table entry is NULL, return NULL to indicate emptiness
    if (ha->table[hash] == NULL) { 
        return (NULL);

    }
    //if table entry is not null, check head, and iterate through list until you find a match. If list_next returns NULL, then break it off.
    found_word = list_first(ha->table[hash]);

    if (found_word == NULL) {
        return NULL;
    }   

    while (strcmp(key, found_word->word) != 0) {
        found_word = list_next(ha->table[hash]);
        if (found_word == NULL) {
            break;
        }
    }
    //this loop exits when key == found_word->word or on break

    //this should return a pointer to the found_word
    //or NULL indicating that it wasn't found
    return (found_word);

}

int h(char *p, int m)
{
    int flip = 0;
    int len = 0;
    int s = 0;
    int shortcnt = 0;
    unsigned short *sp = NULL;

    len = strnlen(p, WSZ);
    shortcnt = len / 2;
    sp = (unsigned short *)p;
    unsigned short hval = 0x5ab6;

    /* folding the string by twos */
    for (s = 0; s < shortcnt; s++)
    {
        unsigned short newv;
        newv = *sp;
        if (flip)
        {
            newv <<= 1;
        }
        flip = !(flip);
        hval ^= newv;
        sp++;
    }
    /* if odd size string double up last char */
    if (len & 0x0001)
    {
        hval ^= ((((short)(p[len-1])) << 8) | (short)(p[len-1]));
    }
    return (int)hval % m;
}

int stats_word(book_word *word, stats_table *stats, int book) {

    int i;
    book_word *temp;

    switch(book) {

        //dracula
        case (0) :

            stats->drac_large[5] = word;
            for (i = 4; i >= 0; i--) {
                if (stats->drac_large[i]->len < stats->drac_large[i+1]->len) {
                    if(stats->drac_large[i] != stats->drac_large[i+1]) {
                        temp = stats->drac_large[i];
                        stats->drac_large[i] = stats->drac_large[i+1];
                        stats->drac_large[i+1] = temp;
                    }
                }
            }

            stats->drac_mfreq[15] = word;
            for (i = 14; i >= 0; i--) {
                if (stats->drac_mfreq[i]->count[0] < stats->drac_mfreq[i+1]->count[0]) {
                    if (stats->drac_mfreq[i] != stats->drac_mfreq[i+1]) {

                        temp = stats->drac_mfreq[i];
                        stats->drac_mfreq[i] = stats->drac_mfreq[i+1];
                        stats->drac_mfreq[i+1] = temp;
                    }
                }
            }

            stats->drac_lfreq[5] = word;
            for (i = 4; i >= 0; i--) {
                if ((stats->drac_lfreq[i]->count[0] >= stats->drac_lfreq[i+1]->count[0]) || stats->drac_lfreq[i+1]->count[0] == 1) {
                    if (stats->drac_lfreq[i] != stats->drac_lfreq[i+1]) {

                        temp = stats->drac_lfreq[i];
                        stats->drac_lfreq[i] = stats->drac_lfreq[i+1];
                        stats->drac_lfreq[i+1] = temp;
                    }
                }
            }
            break;

        //frankenstine
        case (1) :

            stats->frank_large[5] = word;
            for (i = 4; i >= 0; i--) {
                if (stats->frank_large[i]->len < stats->frank_large[i+1]->len) {
                    if(stats->frank_large[i] != stats->frank_large[i+1]) {
                        temp = stats->frank_large[i];
                        stats->frank_large[i] = stats->frank_large[i+1];
                        stats->frank_large[i+1] = temp;
                    }
                }
            }

            stats->frank_mfreq[15] = word;
            for (i = 14; i >= 0; i--) {
                if (stats->frank_mfreq[i]->count[1] < stats->frank_mfreq[i+1]->count[1]) {
                    if (stats->frank_mfreq[i] != stats->frank_mfreq[i+1]) {

                        temp = stats->frank_mfreq[i];
                        stats->frank_mfreq[i] = stats->frank_mfreq[i+1];
                        stats->frank_mfreq[i+1] = temp;
                    }
                }
            }

            stats->frank_lfreq[5] = word;
            for (i = 4; i >= 0; i--) {
                if ((stats->frank_lfreq[i]->count[1] > stats->frank_lfreq[i+1]->count[1]) || (stats->frank_lfreq[i+1]->count[1] == 1)) {
                    if (stats->frank_lfreq[i] != stats->frank_lfreq[i+1]) {

                        temp = stats->frank_lfreq[i];
                        stats->frank_lfreq[i] = stats->frank_lfreq[i+1];
                        stats->frank_lfreq[i+1] = temp;
                    }
                }
            }
            break;

        //common
        case(2) :

            stats->com_large[5] = word;
            for (i = 4; i >= 0; i--) {
                if (stats->com_large[i]->len < stats->com_large[i+1]->len) {
                    if(stats->com_large[i] != stats->com_large[i+1]) {
                        temp = stats->com_large[i];
                        stats->com_large[i] = stats->com_large[i+1];
                        stats->com_large[i+1] = temp;
                    }
                }
            }

            stats->com_mfreq[15] = word;
            for (i = 14; i >= 0; i--) {
                if (stats->com_mfreq[i]->count[0] < stats->com_mfreq[i+1]->count[0]) {
                    if (stats->com_mfreq[i] != stats->com_mfreq[i+1]) {

                        temp = stats->com_mfreq[i];
                        stats->com_mfreq[i] = stats->com_mfreq[i+1];
                        stats->com_mfreq[i+1] = temp;
                    }
                }
            }

            stats->com_lfreq[5] = word;
            for (i = 4; i >= 0; i--) {
                if ((stats->com_lfreq[i]->count[0] >= stats->com_lfreq[i+1]->count[0]) || stats->com_lfreq[i+1]->count[0] == 1) {
                    if (stats->com_lfreq[i] != stats->com_lfreq[i+1]) {

                        temp = stats->com_lfreq[i];
                        stats->com_lfreq[i] = stats->com_lfreq[i+1];
                        stats->com_lfreq[i+1] = temp;
                    }
                }
            }
            break;
        
        default :
            break;

    }
    return 0;
}

void hash_free(hash_table *hash) {

    int i = 0;
    book_word *temp;
    book_word *start;

    start = list_first((hash)->table[i]);
    for (i = 0; i < (HSZ); i++) {
        start = list_first((hash)->table[i]);
        while (start != NULL) {
            temp = start;
            start = list_next((hash)->table[i]);
            free(temp);
        }
    }
    for (i = 0; i < (HSZ); i++) {
        if (hash->table[i] != NULL) {
        list_finalize((hash)->table[i]);
        }
    }
    //free((hash)->table);
    free(hash);

}





