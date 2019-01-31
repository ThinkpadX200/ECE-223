/*
   Richard Coffey
   rrcoffe
   ECE 2230
   list.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
//#include "hack_object.h"
//#include "hack_inventory.h"

//remember no static or global variable calls in this file


/* This header should not depend on any other headers. */
//this functions in this file will be called EXCLUSIVELY by hack_inventory

struct list {

    struct list_node *head;
    struct list_node *tail;
    struct list_node *current;
};

struct list_node {

    struct list_node *prev;
    struct list_node *next;
    struct list_data *data;

};

/** Allocates and initializes a new empty list.
 *
 * Returns a new empty list or NULL if there was an error.
 */
list list_init(void) {

    struct list *ret;
    ret = (struct list *)malloc(sizeof(struct list));
    if (ret != NULL) {
        ret->head = NULL;
        return ret;
    }
    else {
        return NULL;
    }

}

/* Destroys the list and frees its memory.
 *
 * Frees all memory allocated for the list. List data is not freed.
 */
void list_finalize(list lst) {

    struct list_node *p = lst->head;
    struct list_node *t;

    if (lst->head == NULL) {
        free(lst);
    }
    else {
        while(p) {
            t = p;
            p = p->next;
            free(t);
            if (p == NULL) {
                 break;
            }
            }
        
        //free(lst);
    }
/*
    if ((lst->head == lst->tail) && (lst->head != NULL)) { //if there's only one node
        free(lst->head);
    }
    else if ((lst->head != NULL) && (lst->tail != NULL)) { //as long as the head and tail nodes exist
        free(lst->head);
        free(lst->tail);
        if ((lst->current != lst->head) && (lst->current != lst->tail)) { //if the current node is different than the head/tail node
            free(lst->current);
        }
    }

    free(lst);
*/
}

/** Inserts at the head of the list.
 *
 * DATA becomes the new head of the list and DATA's successor is the
 * previous head of the list. DATA must not be NULL.
 *
 * The current item is set to DATA.
 *
 * On error the list is not modified.
 *
 * Returns DATA or NULL on error.
 */
list_data list_insert(list lst, list_data data) {

    //list_data type is defined in list.h, just a data pointer
    //list data type has three list_node pointers, head, tail, current
    //each of these list_node pointers have a list_node *next pointer, list_node *prev pointer, and a list_data data pointer

    //declare temp node to store head pointer
    //   struct list_node *temphead;

    //first is to allocate 
    struct list_node *insert;
    insert = (struct list_node *)malloc(sizeof(struct list_node));

    //if the list is NULL then change the tail pointer

    if (data == NULL) { //if data is null

        free(insert);
        return(NULL);
    }

    else if ((lst->head == NULL) && (data != NULL)) { //if list is empty

        insert->data = data;
        insert->next = NULL; //because this is the only item in the list, both forward and back are NULL
        insert->prev = NULL;
        lst->head = insert; //set all three lst pointer to the only node
        lst->tail = insert;
        lst->current = insert;    

        return (insert->data);

    } else if (data != NULL) { //if there is already a head node

        insert->data = data; //assigning the data argument to the data field of the insert list_node
        insert->next = lst->head;  //set new nodes next to head's next
        lst->head->prev = insert; //set old head's prev to new node
        insert->prev = NULL; //set new node's prev to NULL
        lst->head = insert; //change head pointer
        lst->current = insert; //change current pointer


        return (insert->data);

    } else {

        free(insert); 
        return NULL;
    }


}

/** Appends to the tail of the list.
 *
 * DATA becomes the new tail and DATA's predecessor is the previous
 * tail of the list. DATA must not be NULL.
 *
 * The current item is set to DATA.
 *
 * On error the list is not modified.
 *
 * Returns DATA or NULL on error.
 */
list_data list_append(list lst, list_data data) {

    //declare temp node to store tail pointer
    // struct list_node *temptail;

    //first is to allocate 
    struct list_node *insert;
    insert = (struct list_node *)malloc(sizeof(struct list_node));

    if (data == NULL) { //if data is null

        free(insert);
        return(NULL);
    }

    else if ((lst->head == NULL) && (data != NULL)){

        insert->data = data;
        insert->next = NULL; //because this is the only item in the list, both forward and back are NULL
        insert->prev = NULL;
        lst->head = insert; //set all three lst pointer to the only node
        lst->tail = insert;
        lst->current = insert;    

        return (insert->data);
    }

    else if ((data != NULL) && (lst->tail != NULL)) { //case where we're replacing the tail

        lst->tail->next = insert;
        insert->data = data; //assigning the data argument to the data field of the insert list_node
        insert->prev = lst->tail;  //set new nodes next to head's next
        insert->next = NULL; //set new node's prev to NULL
        lst->tail = insert;
        //temptail->next = insert;
        lst->current = lst->tail; //change current pointer

        return (insert->data);

    }
    else {

        free(insert);
        return NULL;
    }


}

/** Inserts before the current item.
 *
 * DATA's predecessor will be the current item's predecessor. DATA's
 * successor will be the current item. DATA must not be NULL.
 *
 * The current item becomes DATA.
 *
 * It is an error if the current item is NULL. On error the list is
 * not modified.
 *
 * Returns DATA or NULL on error.
 */
list_data list_insert_before(list lst, list_data data) {

    //declare temp node to store head pointer
    //struct list_node *tempinsertb4;

    //first is to allocate
    struct list_node *temp;
 
    struct list_node *insert;
    insert = (struct list_node *)malloc(sizeof(struct list_node));

    if ((lst->current == NULL) || (lst->current->data == NULL)) { //if the current item is NULL return error 

        free(insert);
        return (NULL);
    }

    else if (lst->head == NULL) { //insert if list is empty

        free(insert);
        return (list_insert(lst, data));
    }


    //if there is only one node in the list, or you are inserting before the head
    else if ((data != NULL) && (lst->current != NULL) && (lst->current == lst->head)) {  

        temp = lst->head;
        insert->data = data; //assigning the data argument to the data field of the insert list_node
        insert->next = temp;  //set new nodes next to head's next
        lst->head->prev = insert; //set old head's prev to new node
        insert->prev = NULL; //set new node's prev to NULL
        lst->current = insert; //change current pointer
        lst->head = lst->current; //change head pointer

        return (insert->data);

    }

    else if ((data != NULL) && (lst->current != NULL)) { //inbetween two nodes


        insert->data = data; //assigning the data argument to the data field of the insert list_node
        insert->next = lst->current;  //set new nodes next to head's next
        insert->prev = lst->current->prev; //set new node's prev to NULL
        lst->current->prev->next = insert; //change current pointer
        lst->current->prev = insert; //change head pointer
        lst->current = insert;



        return (insert->data);

    }

    //need a case where there is only one node in the list 

    else {

        free(insert);
        return NULL;


    }


}

/** Inserts after the current item.
 *
 * DATA's predecessor will be the current item. DATA's successor will
 * be the current item's successor.  DATA must not be NULL.
 *
 * The current item becomes DATA.
 *
 * It is an error if the current item is NULL. On error the list is
 * not modified.
 *
 * Returns DATA or NULL on error.
 */
list_data list_insert_after(list lst, list_data data) {

    //declare temp node to store head pointer
    //struct list_node *tempinsertafter;

    //first is to allocate 
    struct list_node *insert;
    insert = (struct list_node *)malloc(sizeof(struct list_node));

    if ((lst->current == NULL) || (lst->current->data ==NULL)) { //if the current item is NULL return error 

        free(insert);
        return (NULL);
    }

    else if (lst->head == NULL) { //insert if list is empty

        free(insert);
        return (list_insert(lst, data));
    }

    //if there is only one node in the list, or you are inserting after the tail
    else if ((data != NULL) && (lst->current != NULL) && (lst->current == lst->tail)) {  

        insert->data = data; //assigning the data argument to the data field of the insert list_node
        insert->prev = lst->tail;  //set new nodes next to head's next
        lst->tail->next = insert; //set old head's prev to new node
        insert->next = NULL; //set new node's prev to NULL
        lst->current = insert; //change current pointer
        lst->tail = insert; //change head pointer

        return (insert->data);

    }

    //
    else if ((data != NULL) && (lst->current != NULL)) { //inbetween two nodes


        insert->data = data; //assigning the data argument to the data field of the insert list_node
        insert->prev = lst->current;  //set new nodes prev to the current
        insert->next = lst->current->next; //set new node's next to the current's next to insert after
        lst->current->next->prev = insert; //set node after current's prev to insert
        lst->current->next = insert; //set current node to insert
        lst->current = insert; //change current to insert

        return (insert->data);

    }

    else {

        free(insert);
        return NULL;
    }



}
/** Removes the current item from the list.
 *
 * Sets the new current item to the successor of the removed current
 * item. Does nothing if the current item is NULL.
 *
 * Returns the removed item (may be NULL).
 */
list_data list_remove(list lst) {

    //declare temp node to store head pointer
    struct list_data *remove;
    //remove = (struct list_node *)malloc(sizeof(struct list_node));

    struct list_node *currenttemp;


    //if lst is empty
    if (lst->head == NULL) {
        
        return (NULL);
    }

    if (lst->current == NULL) { //if the current item is NULL return error 

        return (NULL);
    }

    //case of single node
    else if ((lst->current == lst->head) && (lst->current == lst->tail)) { 

        remove = lst->current->data;
        lst->current->prev = NULL;
        lst->current->next = NULL;
        free(lst->current);
        lst->current = NULL;
        lst->head = NULL;
        lst->tail = NULL;

        return (remove);
    }

    //case of just deleting head
    else if ((lst->current == lst->head) && (lst->current != lst->tail)) { //remove the item 

        currenttemp = lst->current->next;
        remove = lst->current->data;
        lst->current->next->prev = NULL; //change this to NULL because it's going to be head
        free(lst->current);
        lst->current = currenttemp;
        lst->head = lst->current;

        return (remove);
    }

    //case of just deleting tail
    else if ((lst->current != lst->head) && (lst->current == lst->tail)) { 

        currenttemp = lst->current->prev;
        remove = lst->current->data;
        lst->current->prev->next = NULL; //change this to NULL because it's going to be tail
        free(lst->current);
        lst->current = currenttemp;
        lst->tail = lst->current;

        return (remove);
    }

    //case where you're removing a node thats not head or tail
    else if ((lst->current != lst->head) && (lst->current != lst->tail)) {

        //address the case where we are accessing the head and tail here or it will segfault
        currenttemp = lst->current->next; 
        remove = lst->current->data;
        lst->current->prev->next = lst->current->next;
        lst->current->next->prev = lst->current->prev;
        free(lst->current);
        lst->current = currenttemp;

        return (remove);
    }

    else {

        return (NULL);
    }
}

/** Returns the list head.
 *
 * Sets the current item to the list head or NULL.
 *
 * Returns the list head or NULL if the list is empty.
 */
list_data list_first(list lst) {

    if (lst->head == NULL) { //insert if list is empty

        //current item should already be NULL if head is NULL
        return (NULL);
    }
    
    else {
    lst->current = lst->head; //set the current item pointer to the head pointer

    return(lst->head->data);
    }
}

/** Moves the current item forward in the list.
 *
 * Sets the new current item to the successor of the current item. If
 * the current item is the list tail or the current item is NULL then
 * the new current item is NULL.
 *
 * Returns the new current item.
 */
list_data list_next(list lst) {

 //   struct list_node *temp;

    if (lst->head == NULL) { //if lst is empty
        return (NULL);
    }

    if ((lst->current == NULL) || (lst->current->data == NULL)) {

        return(NULL);
    }

    else if (lst->current == lst->tail) { 

        lst->current = NULL; //if the current item it the list tail, then the next current item is NULL
        return (NULL);    
    }
    

  //  lst->current->data = lst->current->next->data;
  //  lst->current->prev = lst->current->next->prev;
    else {

        lst->current = lst->current->next;
        return (lst->current->data);
    }
}

/** Moves the current item backward in the list.
 *
 * Sets the new current item to the predecessor of the current
 * item. If the current item is the list head or the current item is
 * NULL then the new current item is NULL.
 *
 * Returns the new current item.
 */
list_data list_prev(list lst) {


    if (lst->current == NULL) {

        lst->current = NULL;
        return(lst->current);
    }

    if (lst->current == lst->head) {

        lst->current = NULL;
        return (NULL);    
    }

    //lst->current->prev->data = lst->current->data;
    //lst->current->prev->next = lst->current->next;
    else {
        lst->current = lst->current->prev;

        return (lst->current->data);
    }
}
/** Returns the list tail.
 *
 * Sets the current item to the list tail or NULL.
 *
 * Returns the list tail or NULL if the list is empty.
 */
list_data list_last(list lst) {

    if (lst->tail == NULL) { //if lst is empty

        //current item should already be NULL if head is NULL
        return(NULL);
    }
    
    else {
        lst->current = lst->tail; //set the current item pointer to the tail pointer
        return(lst->tail->data);
    }
}

/** Returns the current item of the list.
 *
 * Returns the current item of LST (may return NULL).
 */
list_data list_curr(list lst) {

    if (lst->current == NULL) {
        return (NULL);
    }
    else {
    
        return (lst->current->data);
    }
    //should work for empty list, 

}
