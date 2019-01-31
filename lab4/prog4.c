/*
   prog4.c
   Richard Coffey
   ECE 223
   Program #4
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.h"

#define HSZ 8191

//prototypes
stats_table *parse_file(char *filename, hash_table *hash, int book_num, stats_table *stats);
void print_stats(hash_table *hash, stats_table *stats);



int main(int argc, char **argv) {

    hash_table *hash;


    char *book1;
    char *book2;
    int c;

    if (argc == 1) {
        printf("Please use this format './prog4 -d book1 -f book2'\n");
        exit(1);
    }

    /*checking flags with getopt*/
    while ((c = getopt(argc, argv, "d:f:")) != -1) {

        switch(c)   {

            case 'd':
                book1 = optarg;
                break;

            case 'f':
                book2 = optarg;
                break;

            case '?':
                printf("\nError using flag\n");
                return(1);

            default:
                abort();
        }
    }

    stats_table *stats = calloc(1, sizeof(stats_table));

    //initialize hash table
    hash = hash_init();


    stats = parse_file(book1, hash, 0, stats);
    stats = parse_file(book2, hash, 1, stats);

    print_stats(hash, stats);

    hash_free(hash);
    free(stats);

    return 0;

}

stats_table *parse_file(char *filename, hash_table *hash, int book_num, stats_table *stats)
{
    FILE *fpt;
    char *buf = NULL;
    size_t bufsize = 128;
  //  int hash_val;
    book_word *found_word;
    book_word *temp_word;
    //book_word *inserted_word;


    buf = (char *)malloc(bufsize * sizeof(char));
    if (buf == NULL) {
        printf("\nUnable to allocate buffer\n");
        exit(1);
    }

    if ((fpt = fopen(filename, "r")) == NULL) {
        printf("Cannot Read from File \"%s\"\n", filename);
        exit (1);
    }
    //with the file open, we read each word, hash it, place it in tree



    while (getline(&buf, &bufsize, fpt) != -1) {
        temp_word = (book_word *)malloc(sizeof(book_word));    
        buf[strcspn(buf, "\r\n")] = 0;
        //printf("%s", buf);

        //implying that this is a new word
        strcpy(temp_word->word, buf); //the key
        temp_word->count[0] = 0;
        temp_word->count[1] = 0;
        temp_word->len = strlen(buf);

        // hash_val = h(temp_word->word, HSZ); //index of array

        found_word = hash_search(hash, temp_word->word); //search for word
        //if the returned pointer is NULL, then the word was not found
        if (found_word == NULL) {
            //insert the word

            temp_word->count[book_num] = 1;
            hash_insert(hash, buf, temp_word);
        }   
        //if this word has already been entered
        else {
           // printf("%s", found_word->word);
            found_word->count[book_num]++;
        }
        //keeping track of book word counts
        if (book_num == 0) {
            stats->drac_word_count++;
        }
        else if (book_num == 1) {
            stats->frank_word_count++;
        }

        stats->com_word_count++;
        found_word = NULL;
    }

    fclose(fpt);
    return(stats);
}



void print_stats(hash_table *hash, stats_table *stats) {

    int count;
    int i;
    book_word *temp;
    book_word *populate = calloc(1, sizeof(book_word));

    //populate table
    for (i = 0; i < 5; i++) {
        stats->drac_large[i] = populate;
        stats->frank_large[i] = populate;
        stats->com_large[i] = populate;
        stats->drac_lfreq[i] = populate;
        stats->frank_lfreq[i] = populate;
        stats->com_lfreq[i] = populate;
    }
    for (i = 0; i < 15; i++) {
        stats->drac_mfreq[i] = populate;
        stats->frank_mfreq[i] = populate;
        stats->com_mfreq[i] = populate;
    }



    for (count = 0; count < (HSZ + 1); count++) {

        if ((temp = list_first(hash->table[count])) != NULL) {
        //     printf("%s", hash->table[count]);

            if (temp->count[0] != 0) {
                stats_word(temp, stats, 0);
            }
            if (temp->count[1] != 0) {
                stats_word(temp, stats, 1);
            }
            if (temp->count[1] != 0 && temp->count[0] != 0) {
                stats_word(temp, stats, 2);
            } 

            //check for unique words
            if ((temp->count[0] == 0) && (temp->count[1] != 0)) {
                stats->frank_uni += 1;
            }
            if ((temp->count[1] == 0) && (temp->count[0] != 0)) {
                stats->drac_uni += 1;
 //               printf("%d\n", stats->drac_uni);
            }
            if (temp->count[0] != 0 && temp->count[1] != 0) {
                stats->com_uni += 1;
            }


            //putting stuff into array
            //word_tables



            while((temp = list_next(hash->table[count])) != NULL) {


                if (temp->count[0] != 0) {
                    stats_word(temp, stats, 0);
                }
                if (temp->count[1] != 0) {
                    stats_word(temp, stats, 1);
                }
                if (temp->count[1] != 0 && temp->count[0] != 0) {
                    stats_word(temp, stats, 2);
                }



                //check for unique words
                if ((temp->count[0] == 0) && (temp->count[1] != 0)) {
                    stats->frank_uni += 1;
                }
                if ((temp->count[1] == 0) && (temp->count[0] != 0)) {
                    stats->drac_uni += 1;
   //                 printf("%d\n", stats->drac_uni);
                }
                if ((temp->count[0] != 0) && (temp->count[1] != 0)) {
                    stats->com_uni += 1;
                }
            }
        }
    }    
    //putting stuff into arrays

    /*
       for the largest you have a array size 21;  
       You start at the back (I = 19;); 
       Then while a[i] < word, a[i+1] = a[i];   
       When you find where the new word fits, insert it. 
     */










    // Dracula
    printf("\nECE2230 Fall 2017 Text Hashing Project\nRichard Coffey\n\n");
    printf("Dracula:\n\n");
    //printf("Number of lines processed\t %d", linesproc);
    printf("Number of words processed:\t %d\n", stats->drac_word_count);
    printf("Number of unique words:\t %d\n\n", stats->drac_uni);

    printf("5 largest words\n");
    printf("%s\t\t%d\n", stats->drac_large[0]->word, stats->drac_large[0]->count[0]);
    printf("%s\t\t%d\n", stats->drac_large[1]->word, stats->drac_large[1]->count[0]);
    printf("%s\t\t%d\n", stats->drac_large[2]->word, stats->drac_large[2]->count[0]);
    printf("%s\t\t%d\n", stats->drac_large[3]->word, stats->drac_large[3]->count[0]);
    printf("%s\t\t%d\n\n", stats->drac_large[4]->word, stats->drac_large[4]->count[0]);

    printf("15 most frequently used words\n");
    printf("%s\t\t%d\n", stats->drac_mfreq[0]->word, stats->drac_mfreq[0]->count[0]);
    printf("%s\t\t%d\n", stats->drac_mfreq[1]->word, stats->drac_mfreq[1]->count[0]);
    printf("%s\t\t%d\n", stats->drac_mfreq[2]->word, stats->drac_mfreq[2]->count[0]);
    printf("%s\t\t%d\n", stats->drac_mfreq[3]->word, stats->drac_mfreq[3]->count[0]);
    printf("%s\t\t%d\n", stats->drac_mfreq[4]->word, stats->drac_mfreq[4]->count[0]);
    printf("%s\t\t%d\n", stats->drac_mfreq[5]->word, stats->drac_mfreq[5]->count[0]);
    printf("%s\t\t%d\n", stats->drac_mfreq[6]->word, stats->drac_mfreq[6]->count[0]);
    printf("%s\t\t%d\n", stats->drac_mfreq[7]->word, stats->drac_mfreq[7]->count[0]);
    printf("%s\t\t%d\n", stats->drac_mfreq[8]->word, stats->drac_mfreq[8]->count[0]);
    printf("%s\t\t%d\n", stats->drac_mfreq[9]->word, stats->drac_mfreq[9]->count[0]);
    printf("%s\t\t%d\n", stats->drac_mfreq[10]->word, stats->drac_mfreq[10]->count[0]);
    printf("%s\t\t%d\n", stats->drac_mfreq[11]->word, stats->drac_mfreq[11]->count[0]);
    printf("%s\t\t%d\n", stats->drac_mfreq[12]->word, stats->drac_mfreq[12]->count[0]);
    printf("%s\t\t%d\n", stats->drac_mfreq[13]->word, stats->drac_mfreq[13]->count[0]);
    printf("%s\t\t%d\n\n", stats->drac_mfreq[14]->word, stats->drac_mfreq[14]->count[0]);

    printf("15 least frequently used words\n");
    printf("%s\t\t%d\n", stats->drac_lfreq[0]->word, stats->drac_lfreq[0]->count[0]);
    printf("%s\t\t%d\n", stats->drac_lfreq[1]->word, stats->drac_lfreq[1]->count[0]);
    printf("%s\t\t%d\n", stats->drac_lfreq[2]->word, stats->drac_lfreq[2]->count[0]);
    printf("%s\t\t%d\n", stats->drac_lfreq[3]->word, stats->drac_lfreq[3]->count[0]);
    printf("%s\t\t%d\n\n", stats->drac_lfreq[4]->word, stats->drac_lfreq[4]->count[0]);

    //Frankenstine
    printf("Frankenstine:\n\n");
    //  printf("Number of lines processed\t %d", linesproc);
    printf("Number of words processed:\t %d\n", stats->frank_word_count);
    printf("Number of unique words:\t %d\n\n", stats->frank_uni);

    printf("5 largest words\n");
    printf("%s\t\t%d\n", stats->frank_large[0]->word, stats->frank_large[0]->count[1]);
    printf("%s\t\t%d\n", stats->frank_large[1]->word, stats->frank_large[1]->count[1]);
    printf("%s\t\t%d\n", stats->frank_large[2]->word, stats->frank_large[2]->count[1]);
    printf("%s\t\t%d\n", stats->frank_large[3]->word, stats->frank_large[3]->count[1]);
    printf("%s\t\t%d\n\n", stats->frank_large[4]->word, stats->frank_large[4]->count[1]);

    printf("15 most frequently used words\n");
    printf("%s\t\t%d\n", stats->frank_mfreq[0]->word, stats->frank_mfreq[0]->count[1]);
    printf("%s\t\t%d\n", stats->frank_mfreq[1]->word, stats->frank_mfreq[1]->count[1]);
    printf("%s\t\t%d\n", stats->frank_mfreq[2]->word, stats->frank_mfreq[2]->count[1]);
    printf("%s\t\t%d\n", stats->frank_mfreq[3]->word, stats->frank_mfreq[3]->count[1]);
    printf("%s\t\t%d\n", stats->frank_mfreq[4]->word, stats->frank_mfreq[4]->count[1]);
    printf("%s\t\t%d\n", stats->frank_mfreq[5]->word, stats->frank_mfreq[5]->count[1]);
    printf("%s\t\t%d\n", stats->frank_mfreq[6]->word, stats->frank_mfreq[6]->count[1]);
    printf("%s\t\t%d\n", stats->frank_mfreq[7]->word, stats->frank_mfreq[7]->count[1]);
    printf("%s\t\t%d\n", stats->frank_mfreq[8]->word, stats->frank_mfreq[8]->count[1]);
    printf("%s\t\t%d\n", stats->frank_mfreq[9]->word, stats->frank_mfreq[9]->count[1]);
    printf("%s\t\t%d\n", stats->frank_mfreq[10]->word, stats->frank_mfreq[10]->count[1]);
    printf("%s\t\t%d\n", stats->frank_mfreq[11]->word, stats->frank_mfreq[11]->count[1]);
    printf("%s\t\t%d\n", stats->frank_mfreq[12]->word, stats->frank_mfreq[12]->count[1]);
    printf("%s\t\t%d\n", stats->frank_mfreq[13]->word, stats->frank_mfreq[13]->count[1]);
    printf("%s\t\t%d\n\n", stats->frank_mfreq[14]->word, stats->frank_mfreq[14]->count[1]);

    printf("15 least frequently used words\n");
    printf("%s\t\t%d\n", stats->frank_lfreq[0]->word, stats->frank_lfreq[0]->count[1]);
    printf("%s\t\t%d\n", stats->frank_lfreq[1]->word, stats->frank_lfreq[1]->count[1]);
    printf("%s\t\t%d\n", stats->frank_lfreq[2]->word, stats->frank_lfreq[2]->count[1]);
    printf("%s\t\t%d\n", stats->frank_lfreq[3]->word, stats->frank_lfreq[3]->count[1]);
    printf("%s\t\t%d\n\n", stats->frank_lfreq[4]->word, stats->frank_lfreq[4]->count[1]);


    //Common
    printf("Common vocabulary:\n\n");
    printf("Number of unique words:\t%d\n\n", stats->com_uni);

    printf("5 largest words\n");
    printf("%s\t\t%d\n", stats->com_large[0]->word, stats->com_large[0]->count[0]);
    printf("%s\t\t%d\n", stats->com_large[1]->word, stats->com_large[1]->count[0]);
    printf("%s\t\t%d\n", stats->com_large[2]->word, stats->com_large[2]->count[0]);
    printf("%s\t\t%d\n", stats->com_large[3]->word, stats->com_large[3]->count[0]);
    printf("%s\t\t%d\n\n", stats->com_large[4]->word, stats->com_large[4]->count[0]);

    printf("15 most frequently used words\n");
    printf("%s\t\t%d\n", stats->com_mfreq[0]->word, stats->com_mfreq[0]->count[0]);
    printf("%s\t\t%d\n", stats->com_mfreq[1]->word, stats->com_mfreq[1]->count[0]);
    printf("%s\t\t%d\n", stats->com_mfreq[2]->word, stats->com_mfreq[2]->count[0]);
    printf("%s\t\t%d\n", stats->com_mfreq[3]->word, stats->com_mfreq[3]->count[0]);
    printf("%s\t\t%d\n", stats->com_mfreq[4]->word, stats->com_mfreq[4]->count[0]);
    printf("%s\t\t%d\n", stats->com_mfreq[5]->word, stats->com_mfreq[5]->count[0]);
    printf("%s\t\t%d\n", stats->com_mfreq[6]->word, stats->com_mfreq[6]->count[0]);
    printf("%s\t\t%d\n", stats->com_mfreq[7]->word, stats->com_mfreq[7]->count[0]);
    printf("%s\t\t%d\n", stats->com_mfreq[8]->word, stats->com_mfreq[8]->count[0]);
    printf("%s\t\t%d\n", stats->com_mfreq[9]->word, stats->com_mfreq[9]->count[0]);
    printf("%s\t\t%d\n", stats->com_mfreq[10]->word, stats->com_mfreq[10]->count[0]);
    printf("%s\t\t%d\n", stats->com_mfreq[11]->word, stats->com_mfreq[11]->count[0]);
    printf("%s\t\t%d\n", stats->com_mfreq[12]->word, stats->com_mfreq[12]->count[0]);
    printf("%s\t\t%d\n", stats->com_mfreq[13]->word, stats->com_mfreq[13]->count[0]);
    printf("%s\t\t%d\n\n", stats->com_mfreq[14]->word, stats->com_mfreq[14]->count[0]);

    printf("15 least frequently used words\n");
    printf("%s\t\t%d\n", stats->com_lfreq[0]->word, stats->com_lfreq[0]->count[0]);
    printf("%s\t\t%d\n", stats->com_lfreq[1]->word, stats->com_lfreq[1]->count[0]);
    printf("%s\t\t%d\n", stats->com_lfreq[2]->word, stats->com_lfreq[2]->count[0]);
    printf("%s\t\t%d\n", stats->com_lfreq[3]->word, stats->com_lfreq[3]->count[0]);
    printf("%s\t\t%d\n", stats->com_lfreq[4]->word, stats->com_lfreq[4]->count[0]);

}








