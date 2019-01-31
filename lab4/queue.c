/*
   queue.c
   Richard Coffey
   ECE 223
   Program #3
 */

#include <stdio.h>
#include <stdlib.h>
//#include "list.h"
#include "queue.h"
//#include "sim.h"


//queue is a linked list so should never be full
struct queue_s {

    list list;
    int numelements;
    int maxsize;
};

/* create and initialize a new queue
   must be able to hold at least size items
   return pointer to the new queue, NULL if error */

//int size is input in main file where queue init is called
//should allocate a queue pointer that has size of 

//mallocs a new queue_t, then calls list_init
//int size doesn't really matter, 
queue_t *queue_init(int size) {

    struct queue_s *queue;
    queue = (struct queue_s *)malloc(sizeof(struct queue_s));
    if (queue == NULL) {
        return(NULL);
    }
    else {
        // queue is valid,initialize the linked list in that queue
        queue->list = list_init();

        if (queue->list == NULL) {

            free(queue);
            return (NULL);
        }

        //set counter variables
        //queue->numelements = 0;
        //queue->maxsize = size+1;

        return(queue);
    }
}

/* insert an item into the queue
   return 0 if successful, -1 otherwise */

//first in first out queue
//no need to check for max length because it's a linked list

int queue_insert(queue_t *q, customer_t *c) {

    //create a temp customer pointer
    customer_t *ctemp;

    //always put the new customer at the back of the list b/c FIFO
    ctemp = list_append(q->list, c);
    if (ctemp == NULL) {
        return(-1);
    }

    //add 1 to the customer counter
    (q->numelements)++;

    //if the customer is successfully added to the back of the queue
    return (0);

}



/* return the next item in the queue but do not remove it

   return NULL if the queue is empty or on error */
customer_t *queue_peek(queue_t *q) {

    //set list to the first element
    customer_t *cfirst;

    cfirst = list_first(q->list);

    if (cfirst == NULL) {

        return (NULL);
    }

    else {

        return (cfirst);
    }

}





/* remove the next item from the queue
   and return it, return NULL if there is an error */
customer_t *queue_remove(queue_t *q) {

    //remove first item in the queue according to FIFO
    //use list_first to set head to current item

    customer_t *cfirst;
    customer_t *cremoved;

    cfirst = list_first(q->list);

    if (cfirst == NULL) {

        return (NULL);
    }

    //removes the current item, and which should be head
    //list_remvoe should always hit the "just delete head" case 
    cremoved = list_remove(q->list);

    if (cremoved == NULL) {

        return (NULL);
    }

    (q->numelements)--;
    return(cremoved);

}



/* return the number of items in the queue
   You can see if queue is empty with this */
int queue_size(queue_t *q) {

    return (q->numelements);

}

/* return nono-zero if the queue is full
   This may be trivial using a linked implementation */
int queue_full(queue_t *q) {

    //will always return 0 since linked list in queue is infinite
    return(0);

}

/* free all resourced used by the queue then free
   the queue itself */
void queue_finalize(queue_t *q) {

    list_finalize(q->list);
    free(q);

}

