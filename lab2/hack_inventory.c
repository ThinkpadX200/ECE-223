/*
   Richard Coffey
   rrcoffe
   ECE 2230
   hack_inventory.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "hack_object.h"
#include "hack_inventory.h"


//functions in here called by assign2.c and then this file will call list.c functions 
//remember no global or static varibale in this file

/** pointer to opaque inventory type to be defined in hack_inventory.c */
//typedef struct h_inventory *h_inventory;
//defining h_inventory

struct h_inventory {

    list items; //this should be a linked list
    /* current? */
};


/** Object comparison function.
 *
 * An object comparison function shall compare the two objects LEFT
 * and RIGHT. If LEFT compares equal to RIGHT then it returns zero,
 * otherwise it returns nonzero.
 */
//A type called "h_inventory_cmp_f" that is a pointer to a function returning an int and taking two const h_object pointers as arguments


//ignoring this function as it's impossible to implement
/*
   typedef int (*h_inventory_cmp_f)(const h_object *left, const h_object *right) {


   }
 */

/** Creates a new empty inventory.
 *
 * The current object is initially NULL.
 *
 * Returns the new inventory or NULL on error.
 */
h_inventory h_inventory_create(void) {

    // int value;
    struct h_inventory *inventory = malloc(sizeof(struct h_inventory));

    if (inventory == NULL) {

        return(NULL);

    } else {

        inventory->items  = list_init();

        if (inventory->items == NULL) {

            free(inventory);
            return (NULL);
        }

        return(inventory);    
    }

}
/** Adds a new object to the inventory.
 *
 * OBJECT is inserted into the inventory in order sorted by
 * OBJECT->class. The new object is appended to the end of all the

 * objects with the same class (see example).
 *
 * OBJECT->id must be unique within the inventory. Attempting to add
 * an object with a duplicate id is an error.
 *
 * The current object remains the same.
 *
 * Example:
 * | call                   | inventory                 |
 * |------------------------+---------------------------|
 * | inventory_add(potion1) | potion1                   |
 * | inventory_add(tool)    | tool,potion1              |
 * | inventory_add(food)    | tool,potion1,food         |
 * | inventory_add(potion2) | tool,potion1,potion2,food |
 *
 * Returns OBJECT or NULL on error.
 */

//this will call list_first(), list_next(), until it finds a spot to add new object, then call list_insert_after()
h_object *h_inventory_add(h_inventory inventory, h_object *object) {

    //given inventory and object, run through list and use h_object_compare to add to correct class
    //while current is less than or equal to the the class, move current over.
    //At the point where that condition is no longer valid, you've reached the end of the class
    //use list_insert_before to place it at the end of the class

    //begin at the beginning of the list
    //inventory->items
    //struct list_data data;
    //int place;
    h_object *holder_obj;
    int id_check;

    //h_object *data = (h_object *)


    h_object *test_obj = list_first(inventory->items); //set pointer to head of list   

    if (test_obj == NULL) { //if list is empty
        list_insert(inventory->items, object); //insert the object into the head 
        return (object); //then return that object

    }

    while (1) {    
        if (test_obj->id == object->id) { //if object just has same ID
                return (NULL);
        }
        else if (test_obj == NULL) {
            break;
        }
        else {
            test_obj = list_next(inventory->items);
            if (test_obj == NULL) {
                break;
            }
        }
    }
    
    test_obj = list_first(inventory->items);

    //if the first object in the list in not NULL, test to make sure that they aren't a match
    id_check = h_object_compare(object, test_obj);

    if (id_check != 0) { 

        while(1) {
            if (test_obj->class <= object->class) { //compares test object (current) and new object class

                test_obj = list_next(inventory->items); //move current pointer down

                if (test_obj == NULL) { //if data reaches the end, append object to the back of the list

                    //test_obj = list_prev(inventory->items); //sets current back to tail item;
                    holder_obj = list_append(inventory->items, object);
                    return (holder_obj); 
                }

                else if (test_obj->id == object->id) { //if object just has same ID
                    
                    return (NULL);
                }

                else if ((h_object_compare(test_obj, object)) == 0) { //if the object matches completely

                    return (NULL); //null since the object has the same ID and attributes
                } 
                 
            }

            else { //if the test_object finds the end of it's grouping

                holder_obj = list_insert_before(inventory->items, object); 
                return (holder_obj); 
            }

            //on review remember to test for the 4 cases

        }
    }

    return (NULL); //if nothing else hits return null
}
/** Removes the current object from the inventory.
 *
 * The new current object becomes the object after the current object
 * (or NULL if there is no object after the current object).
 *
 * Returns the object that was removed or NULL if the current object
 * was NULL.
 */
h_object *h_inventory_delete(h_inventory inventory) {

    h_object *current_obj;

    current_obj = list_remove(inventory->items);

    if (current_obj == NULL) {

        return (NULL);
    }

    else {

        return (current_obj);
    }

}

/** Move to the first object in the inventory.
 *
 * Siets the current object to the first object in the inventory (or
 * NULL if the inventory is empty).
 *
 * Returns the first object in the inventory or NULL if the inventory
 * is empty.
 */
h_object *h_inventory_first(h_inventory inventory) {

    h_object *first_obj;

    first_obj = list_first(inventory->items);

    if (first_obj == NULL) {

        return (NULL); //if the list_first function errors, return NULL
    }

    else {
        return (first_obj);
    }


}

/** Move to the next object in the inventory.
 *
 * Sets the new current object to the object after the current
 * object. There is no object after the NULL current object.
 *
 * Returns the object after the current object or NULL if there is no
 * object after the current object.
 */
h_object *h_inventory_next(h_inventory inventory) {

    h_object *next_obj;

    next_obj = list_next(inventory->items);

    if (next_obj == NULL) {

        return (NULL); //if the list_next function errors, return NULL
    }

    else {

        return (next_obj);
    }

}

/** Finds an object by its id.
 *
 * Sets the current object to the object whose id is equal to ID (or
 * NULL if no such object was found).
 *
 * Returns the matching object or NULL if no such object was found.
 */
h_object *h_inventory_find_id(h_inventory inventory, int id) {

    h_object *current_obj = list_first(inventory->items); //set pointer to head of list
    if (current_obj == NULL) { //if list is empty
        return (NULL);

    }

    if ((current_obj->id) == id) { //if head of list hits, return it
        return (current_obj);
    } 

    while (1) { //if head doesn't hit then cycle through the list

        current_obj = list_next(inventory->items); //sets a new current object

        if (current_obj == NULL) {
            return (NULL); //if the while loop never finds the right ID, then exit

        }
        if ((current_obj->id) == id) { //if the new current object matches ID, then return that current obj
            return (current_obj); 
        }

    }
}

/** Finds an object using the provided comparison function.
 *
 * The search begins at the current object and continues until OBJCMP
 * returns 0 or until the end of the inventory. If the current object
 * was NULL then the search begins at the first object in the
 * inventory.
 *
 * The current object is set to the first object for which OBJCMP
 * returns 0, and then the search stops. If the search reaches the end
 * before OBJCMP returns 0 then the current object is set to NULL.
 *
 * Returns the first object for which OBJCMP returns 0 or NULL if no
 * such object was found.
 */
//h_object *h_inventory_find_func(h_inventory inventory, h_inventory_cmp_f objcmp) 




/** Destroys the inventory and frees its memory.
 *
 * Storage for any objects in the inventory is never freed.
 */
void h_inventory_destroy(h_inventory inventory) {

    list_finalize(inventory->items);
    //free(inventory->items);
    free(inventory);

}
