/* 
   Richard Coffey
   ECE223
   Assignment 1

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "guitardb.h"

#define MAXLINE 50
#define MAXCOM 4
#define max_guitars 1

static int global_item_key = 1;

struct guitardb {
    struct guitardb_guitar *guitars[max_guitars];
    int cursor;
};

void print_guitar(struct guitardb *db);

//
int main() {

    //allocate for db and set cursor/IDkey
    struct guitardb *db;
    db = guitardb_create();
    db->cursor = 0;
    //char itemkey[50];
    char line[MAXLINE];
    //int args;
    int count;
    int addcheck = 0;
    char command[MAXCOM];
    int keynum;
    int g_add;
    int g_lookID;
    struct guitardb_guitar *g_lookcheck;
    int g_del;
    int g_des;
    struct guitardb_guitar *first;
    struct guitardb_guitar *next;


    //Command reader
    while(1) {

        strcpy(command, "TEST");
        setbuf(stdin, NULL);

        printf("\nEnter a command: \n");
        printf("> ADD \n");
        printf("> LOOK [item-key] \n");
        printf("> DEL [item-key] \n");
        printf("> LIST \n");
        printf("> QUIT \n\n");

        fgets(line,MAXLINE,stdin);
        sscanf(line,"%s %d", command, &keynum);
        //getchar(); //consume \n

        //ADD
        //addcheck is an structural artifact 
        if(!(strcmp(command, "ADD"))) {

            if (addcheck == 0) {

                //allocate memory for guitar input
                struct guitardb_guitar *guitar = NULL;
                guitar = (struct guitardb_guitar *)malloc(sizeof(struct guitardb_guitar));

                guitar->item_key = global_item_key;

                printf("Enter guitar make:\n");
                scanf("%s", guitar->make);

                printf("Enter guitar model:\n");
                scanf("%s", guitar->model);

                printf("Enter guitar submodel:\n");
                scanf("%s", guitar->submodel);

                printf("Enter guitar body type:\n");
                scanf("%s", guitar->body_type);

                printf("Enter guitar year:\n");
                scanf("%d", &guitar->year);

                printf("Enter guitar finish:\n");
                scanf("%s", guitar->finish);

                printf("Enter guitar strings:\n");
                scanf("%d", &guitar->strings);

                printf("Enter guitar pickups:\n");
                scanf("%d", &guitar->pickups);

                printf("Enter guitar neck:\n");
                scanf("%s", &guitar->neck);

                printf("Enter guitar middle:\n");
                scanf("%s", &guitar->middle);

                printf("Enter guitar bridge:\n");
                scanf("%s", &guitar->bridge);

                //g_add can return with 3 cases, No, No, and yes
                g_add = guitardb_add(db, guitar);

                if (g_add == -1) {
                    printf("\n\nGuitar could not be added\n");
                    free(guitar);
                }
                else if (g_add == -2) {
                    printf("\n\nGuitar Item key already exists");
                    free(guitar);
                }
                else {
                    printf("\nGuitar ID key: %i\n", guitar->item_key);
                    global_item_key++;
                   // free(guitar);

                }
            }
        }

        //LOOK
        if(!(strcmp(command, "LOOK"))) {
            g_lookID = keynum;
            g_lookcheck = guitardb_lookup(db, g_lookID);
            if (g_lookcheck == NULL) {
                printf("Item not found\n\n");
            }
            else {
                print_guitar(db);
            }

        }

        //DELETE
        if(!(strcmp(command, "DEL"))) {
            g_del = guitardb_delete(db, keynum);

            if (g_del == -1) {//if returns with 0 no message
                printf("Guitar could not be deleted, try again.\n\n");
            }
        }

        //LIST 
        if(!(strcmp(command, "LIST"))) {
            first = guitardb_first(db);
            if (first == NULL) {
                printf("Inventory is empty\n\n");
            }
            else {
                while(1) {
                    print_guitar(db);
                    next = guitardb_next(db);
                    if (next == NULL) {
                        break;
                    }
                }
            }
        }


        //QUIT
        if(!(strcmp(command, "QUIT"))) {
            for (count = 0; count < max_guitars; count++) {
                if (db->guitars[count] != NULL) {
                    free(db->guitars[count]);
                }
            }

            g_des = guitardb_destroy(db);
            if (g_des == -1) {
                printf("Could not destroy database, try again\n\n");
            }
            else {
                exit(0); //if we get a 0, break loop to quit program
            }
        }
    }

    return(0); //once loop is exited, exit main
}

void print_guitar (struct guitardb *db) {
    printf("\nItem Key: %d\n", db->guitars[db->cursor]->item_key);
    printf("Make: %s\n", db->guitars[db->cursor]->make);
    printf("Model: %s\n", db->guitars[db->cursor]->model);
    printf("Submodel: %s\n", db->guitars[db->cursor]->submodel);
    printf("Body Type: %s\n", db->guitars[db->cursor]->body_type);
    printf("Year: %d\n", db->guitars[db->cursor]->year);
    printf("Finish: %s\n", db->guitars[db->cursor]->finish);
    printf("Strings: %d\n", db->guitars[db->cursor]->strings);
    printf("Pickups: %d\n", db->guitars[db->cursor]->pickups);
    printf("Neck: %c\n", db->guitars[db->cursor]->neck);
    printf("Middle: %c\n", db->guitars[db->cursor]->middle);
    printf("Bridge: %c\n", db->guitars[db->cursor]->bridge);

}
