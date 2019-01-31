/*
   Richard Coffey
   rrcoffe
   ECE 2230
   list.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "hack_object.h"
#include "hack_inventory.h"

//remember no static or global variable calls in this file

/** Print the string representation of an object.
 *
 * Writes the string representation of OBJECT to STREAM.
 *
 * Returns the number of characters printed (not including the
 * trailing '\0') or -1 on error.
//pass in stdout into h_object_print
 */
int h_object_print(FILE *stream, const h_object *object) {

/*
    (int *)type = object->type;
    (int *)class = object->class;
    (int *)status = object->status;;
  */  

    fprintf(stream, "ID: %d\n", object->id);
    fprintf(stream, "Dungeon Level: %d, Coordinates: (%d, %d)\n", object->loc.l, object->loc.x, object->loc.y);
    fprintf(stream, "Type: %d\n", object->type); 
    fprintf(stream, "Class: %d\n", object->class); 
    fprintf(stream, "Status: %d\n", object->status); 
    fprintf(stream, "Charge: %d\n", object->charge); 
    fprintf(stream, "Type: %d\n\n", object->weight); 

    return(0);

}

/** Compare two game objects.
 *
 * Returns an integer greater than, equal to, or less than 0,
 * according as the h_object LEFT is greater than, equal to, or less
 * than the h_object RIGHT.
 */

//use this to compare the objects class
int h_object_compare(const void *left, const void *right) {

    h_object *l = (h_object *)left;
    h_object *r = (h_object *)right;

    if ((l->id) < (r->id)) {
        return (-1);
    }

    if ((l->id) > (r->id)) {
        return (1);
    }

    if ((l->id) == (r->id)) {

        //in order to pass the asserts, the test must fail if the ID keys are the same
        //EVEN THOUGH NICK SPECIFICALLY SAID TO TEST EVERYTHING?!?!!

        //if objects are equal we must test everything
        //returning 99 as a catch value
        if ((l->loc.l) != (r->loc.l)) {
            return 99; 
        }
        else if ((l->loc.x) != (r->loc.x)) {
            return 99;
        }
        else if ((l->loc.y) != (r->loc.y)) {
            return 99;
        }
        else if ((l->type) != (r->type)) {
            return 99;
        }
        else if ((l->class) > (r->class)) {
            return 1;
        }
        else if ((l->class) < (r->class)) {
            return -1;
        }
        else if ((l->status) != (r->status)) {
            return 99;
        }
        else if ((l->charge) != (r->charge)) {
            return 99;
        }
        else if ((l->weight) != (r->weight)) {
            return 99;
        }
        //if everything is exactly the same
        else {
            return 0;
        }


    }

    return (55); //no match flag
}

