/*
   Richard Coffey
   rrcoffe
   ECE 2230
   rrcoffe_assign2.c
 */

//this file should call functions in hack_inventory.c
//As well as give a user interface, should not have to  anything in here since we are only using the functions from hack_inventory.c

#define MAXLINE 50

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "hack_object.h"
#include "hack_inventory.h"
#include "string.h"

int global_item_key;

int main() {

    struct h_inventory *inventory;
    inventory = h_inventory_create(); //creating the inventory and linked list within

    char line[MAXLINE];
    char command[MAXLINE];
    h_object *add_return_obj; //add return object
    h_object *item_look; //look return object
    h_object *item_del; //del return object 
    h_object *item_list; //item first return object, replacement object for list
    h_object *item_first; //first return object 
    h_object *item_next; //next return object 
    h_object *item_last; //last return object 
    h_object *item_temp; //holder for item_last
    h_object *item_quit;
    
    h_object *object = NULL;
    int lookID;
    int keynum;


    while(1) {

        strcpy(command, "TESTS");
        setbuf(stdin, NULL);

        printf("\nEnter a command: \n");
        printf("> ADD \n");
        printf("> LOOK [item-key] \n");
        printf("> DEL [item-key] \n");
        printf("> LIST \n");
        printf("> FIRST \n");
        printf("> LAST \n");
        printf("> NEXT \n");
        printf("> QUIT \n\n");

        fgets(line,MAXLINE,stdin);
        sscanf(line,"%s %d", command, &keynum);

        //ADD
        if(!(strcmp(command, "ADD"))) {

            //  memset(&object, 1, sizeof(object));
            //allocate memory for item input
            object = (h_object *)malloc(sizeof(h_object));


            object->id = global_item_key++;

            printf("Enter item location (Level):\n");
            scanf("%d", &object->loc.l);

            printf("Enter item location (X-Coordinate):\n");
            scanf("%d", &object->loc.x);

            printf("Enter item location (Y-Coordinate):\n");
            scanf("%d", &object->loc.y);

            printf("Enter item type in integer form:\n");
            scanf("%u", &object->type);

            printf("Enter item class in integer form:\n");
            scanf("%u", &object->class);

            printf("Enter item status in integer form:\n");
            scanf("%u", &object->status);

            printf("Enter item charge\n");
            scanf("%d", &object->charge);

            printf("Enter item weight\n");
            scanf("%d", &object->weight);

            //adding the item using the hack_inventory function, can return the object or NULL
            add_return_obj = h_inventory_add(inventory, object);

            if (add_return_obj == NULL) {
                printf("\n\nItem could not be added!\n");
                free(object);
            }
            //if the function returns the added object
            else {
                printf("\nItem ID key: %i\n", object->id);
            }

            //  free(object);
        }

        //LOOK
        if(!(strcmp(command, "LOOK"))) {
            lookID = keynum;
            item_look = h_inventory_find_id(inventory, lookID);
            if (item_look == NULL) {
                printf("Item not found\n\n");
            }
            else {
                h_object_print(stdout, item_look);
            }

        }

        //DELETE
        if(!(strcmp(command, "DEL"))) {
            item_del = h_inventory_find_id(inventory, keynum);

            item_del = h_inventory_delete(inventory);

            if (item_del == NULL) {//if returns with 0 no message
                printf("Item could not be deleted, try again.\n\n");
            }

            else {
                printf("Item deleted\n\n");
            }

        }

        //LIST 
        if(!(strcmp(command, "LIST"))) {

            item_list = h_inventory_first(inventory);
            if (item_list == NULL) {
                printf("Inventory is empty\n\n");
            }
            else {
                while(1) {
                    h_object_print(stdout, item_list);
                    item_list = h_inventory_next(inventory);
                    if (item_list == NULL) {
                        break;
                    }
                }
            }
        }

        //FIRST
        if(!(strcmp(command, "FIRST"))) {

            item_first = h_inventory_first(inventory);
            if (item_first == NULL) {
                printf("Inventory is empty\n\n");
            }
            else {
                h_object_print(stdout, item_first);
            }


        }

        //LAST
        if(!(strcmp(command, "LAST"))) {

            item_last = h_inventory_first(inventory);
            if (item_last == NULL) {
                printf("Inventory is empty\n\n");
            }

            else {

                while (item_last != NULL) {
                    item_temp = item_last; //save item_last in item_temp in case we hit end of list

                    item_last = h_inventory_next(inventory); //item last should turn into the next item or hit the end

                    if (item_last == NULL) {
                        h_object_print(stdout, item_temp);
                        break;
                    }
                }
            }

        }

        //NEXT
        if(!(strcmp(command, "NEXT"))) {

            item_next = h_inventory_next(inventory);
            if (item_next == NULL) {
                printf("No next item!\n\n");
            }
            else {
                h_object_print(stdout, item_next);
            }


        }
        //QUIT
        if(!(strcmp(command, "QUIT"))) {
            item_quit = h_inventory_first(inventory);
            if (item_quit == NULL) {
                h_inventory_destroy(inventory);
             //   free(object);
                exit(0);
            }
            else {
                while(item_quit != NULL) { //freeing every item data piece until no more are left` 
                    item_quit = h_inventory_next(inventory);
                    free(item_quit);
                }        
                h_inventory_destroy(inventory);
            }
            free(object);
            exit(0); //if we get a 0, break loop to quit program
        }

    }

    return(0); //once loop is exited, exit main
}
