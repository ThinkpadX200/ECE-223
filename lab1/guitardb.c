/*
   Richard Coffey
   ECE223
   Assignment 1

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "guitardb.h"

#define max_guitars 1

struct guitardb {
    struct guitardb_guitar *guitars[max_guitars];
    int cursor;

};

/* Allocates and initializes a new empty guitar database.
 *
 * Returns the new database or NULL if out of memory.
 */

struct guitardb *guitardb_create(void) {

    struct guitardb *ret; //ret is the top of the pointer array
    ret = (struct guitardb *)malloc(1 * sizeof(struct guitardb));
    return ret; //return the top of the array for the guitardb

}


/** Adds a guitar to the database.
 *
 * Stores a pointer to the guitar (i.e. does not make a copy). The
 * caller is responsible for ensuring the validity of GTAR throughout
 * the lifetime of DB. GTAR->item_key must be unique within DB. The
 * item key must be positive.
 *
 * Returns the item key or -1 if the guitar could not be added to the
 * database.
 */
int guitardb_add(struct guitardb *db, struct guitardb_guitar *gtar) {

    int count; //dummy variable

    for (count = 0; count < max_guitars; count++) {
        if (db->guitars[count] != NULL) {
            //if item keys match exit
            if (db->guitars[count]->item_key == gtar->item_key) { 
                return (-2);
            }
        }
    }

    for (count = 0; count < max_guitars; count++) {
        if (db->guitars[count] == NULL) {
            db->guitars[count] = gtar; //if we reach empty spot set it
            return (db->guitars[count]->item_key);

        }

        //test case: if max inventory has been reached or somehow greater
        if (count >= max_guitars) {
            return -1;
        }
    }

    return -1; //if the NULL doesn't hit

    //item key functionality should be taken care of in assign.c
    //Dr. Ligon said we don't even need to check for valid item keys just increment 
    //UPDATE: Did the check for DB portability, go me it's my birthday
}


/** Returns a guitar in the database by its key.
 *
 * The returned guitar is stored internally by the database and must
 * not be freed.
 *
 * Returns the guitar with item key KEY or NULL if no such guitar was
 * found.
 */
struct guitardb_guitar *guitardb_lookup(struct guitardb *db, int key) {

    int count; //dummy variable

    struct guitardb_guitar *loc = NULL; //creating location pointer 
    for (count = 0; count < max_guitars; count++) { 
        if (db->guitars[count] != NULL) {
            if (db->guitars[count]->item_key != 0) { //avoiding weird case
                if (db->guitars[count]->item_key == key) { //if guitar key matches db key
                    loc = db->guitars[count]; //sets pointer locaiton to the guitar with the correct item key
                    db->cursor = count; //set cursor to guitar for print function to work
                }
            }
        }
    }
    if (loc == NULL) {
        return NULL;
    }
    else {
        return loc;
    }

}


/** Removes a guitar from the database by its key.
 *
 * The caller is reponsible for ensuring that the storage for the
 * guitar is eventually freed.
 *
 * Returns 0 on success or -1 if no guitar was found with item key
 * KEY.
 */
int guitardb_delete(struct guitardb *db, int key) {

    int count;
    int arraymover;
    int del = 0;
    for (count = 0; count < max_guitars; count++) { 
        if (db->guitars[count] != NULL) { 
            if (db->guitars[count]->item_key == key) { //if matching guitar key
                //not freeing that guitar here
                db->guitars[count] = NULL; //replace with null
                arraymover = count;
                while (arraymover < max_guitars) {
                    db->guitars[arraymover] = db->guitars[arraymover+1];
                    arraymover++;
                }
                printf("Guitar Deleted\n\n");
                del = 1;
            }
        }
    }
    if (del == 0) {
        printf("Guitar not found\n\n");
    }
    return 0;
}


/** Returns the first guitar in the database.
 *
 * Returns the first guitar in the database or NULL if the database is
 * empty.
 */
struct guitardb_guitar *guitardb_first(struct guitardb *db) {

    int count;
    struct guitardb_guitar *first;
    first = NULL;

    for (count = 0; count < max_guitars; count++) {
        //as long as the entry isn't null and the item key is greater than 0
        if ((db->guitars[count] != NULL) && (db->guitars[count]->item_key > 0)) {
            (db->cursor = count);
            //take the first guitar to hit in the db
            first = db->guitars[count]; //the first guitar 
            break;
        }
    }
    if (first == NULL) {
        return NULL;
    }    
    else {
        return first;
    }
}



/** Returns the next guitar in the database.
 *
 * previous call    | result
 * ------------------------------------------------
 * guitardb_first()  | the second guitar
 * guitardb_next()   | the guitar after the previous
 * guitardb_create() | error
 * guitardb_add()    | error
 * guitardb_delete() | error
 *
 * Returns the next guitar in the database or NULL on error.
 */
struct guitardb_guitar *guitardb_next(struct guitardb *db) {

    int count;
    struct guitardb_guitar *next;
    next = NULL;

    for (count = ((db->cursor)+1); count < max_guitars; count++) {
        if ((db->guitars[count] != NULL) && (db->guitars[count]->item_key > 0)) {
            (db->cursor = count);
            //should take the first guitar to hit after the cursor
            next = db->guitars[count];
            break;
        }
    }

    return next;
}


/** Deallocates storage for the database.
 *
 * The database need not be empty, but the caller is always
 * responsible for deallocating the storage for guitars.
 *
 * Returns 0.
 */
int guitardb_destroy(struct guitardb *db) {

    free(db);
    return 0;
}


