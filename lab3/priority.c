/*
   priority.c
   Richard Coffey
   ECE 223
   Program #3
 */

//#include "sim.h"
#include "priority.h"
//#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

struct priority_s {
    event_t **heap;
    int numelements;
    int maxsize;
};

/* create and initialize a new priority queue
   must be able to hold at least size items
   return pointer to the new priority queue, NULL if error */
priority_t *priority_init(int size) {

    struct priority_s *pqueue; //declare the priority queue
    pqueue = (struct priority_s *)malloc(sizeof(struct priority_s));

    struct event_s **event; //declare event space
    event = (struct event_s **)malloc(size+1 * sizeof(struct event_s *));

    pqueue->heap = event;
    pqueue->numelements = 0;
    pqueue->maxsize = size + 1;

    return(pqueue);
}




/* insert an item into the priority queue
   return 0 if successful, -1 otherwise */
//insertion should be handled additionally in main
int priority_insert(priority_t *q, event_t *ev) {

    int parentloc;
    int childloc;


    //check if event queue is full
    if (priority_full(q)) {
        printf("\nEvent Queue Full: Please rerun with larger Event Queue!\n\n");
        exit(1);
        //possible exit() right there?
    }



    //if first event is being put into the event queue
    if (q->numelements == 0) {
        q->heap[1] = ev; //placing first event into the second slot
        q->numelements = 1;

        return(0);

    }
    //if there are other elements in the tree
    else {

        childloc = q->numelements+1; //set child number to next spot
        q->heap[childloc] = ev;
        parentloc = childloc/2; 

        //reheapify based on event_time

        while(parentloc != 0) { 

            /*case where parent is NULL
              if (q->heap[parentloc] == NULL) {

              return(0);
              }*/

            //if the new child should now be the root
            //is <= ok?
            if (ev->event_time >= q->heap[parentloc]->event_time) {
                //if child is larger than parent, insert
                q->heap[childloc] = ev;
                (q->numelements)++;
                return(0); 
            }
            else {

                // struct event_s *temp; //temp to hold parent
                // temp = q->heap[parentloc];
                q->heap[childloc] = q->heap[parentloc];
                childloc = parentloc;
                parentloc = parentloc/2;
            }

        }
        //if while loop ends, insert
        q->heap[childloc] = ev;

        //on successful addition
        (q->numelements)++;
        return (0);
    }

}

//ON WHAT CASES CAN THIS ERROR?






/* remove the highest priority item from the queue
   and return it, return NULL if there is an error */
event_t *priority_remove(priority_t *q) {


    int currentloc; //location being examined
    int childloc;   //child of current
    event_t *relocate; //item to relocate
    event_t *ev; //item to return

    //if no elements in the tree
    if (priority_empty(q)) {

        return (NULL);
    }

    //if one element in the tree
    if (q->numelements == 1) {

        ev = q->heap[1];
        q->heap[1] = NULL;
        q->numelements = 0;
        return(ev);

    }

    else {

        ev = q->heap[1]; //set ev to head of tree to return later
        relocate = q->heap[q->numelements]; //last leaf value
        (q->numelements)--; //delete the last leaf
        //setting locations
        currentloc = 1; //starts at root
        childloc = 2*currentloc; //child starts at root's left child

        //reheaping
        while (childloc <= q->numelements) { //while there is a child

            //set childloc to location of larger child currentloc       
            if (childloc < q->numelements) { //if right child exists

                if (q->heap[childloc+1]->event_time <= q->heap[childloc]->event_time) {
                    childloc++;
                }
            }

            //if this position is less than item to move
            if (q->heap[childloc]->event_time >= relocate->event_time) {
                break;
            }
            else  {
                //if childitem
                q->heap[currentloc] = q->heap[childloc];
                currentloc = childloc;
                childloc = 2 * currentloc;
            }

        }

        q->heap[currentloc] = relocate;
        return (ev);
    }
}

//        q->heap[1] = q->heap[q->numelements] //set head to lowest pos
//      q->heap[q->numelements] = NULL; //null that node




/* return non-zero if the priority queue is empty */
int priority_empty(priority_t *q) {

    if (q->numelements <= 0) {
        return (99);
    }
    else {
        return (0);
    }
}

/* return nono-zero if the priority queue is full */
int priority_full(priority_t *q) {

    if(q->numelements >= q->maxsize) {
        return (99);
    }
    else {
        return (0);
    }
}

/* free all resourced used by the priority queue then free
   the queue itself */
void priority_finalize(priority_t *q) {

    free(q->heap);
    free(q);

}

