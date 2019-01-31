/* list.h
 * Nathan Bayles    
 * nbayles          
 * ECE 2230-001, Spring 2017
 * MP2
 * ECE223-1,#2
 * 
 */
#if 0
Here is	the header for the list	ADT. Note all functions	are in terms to	data_t.
This must use a	double-linked list. You	code must accept as many entries as possible until	memory is exhausted. Your program must not have	a memory leak –	 meaning that at no time	may data you have allocated be inaccessible or put another way, you must always	call free() on any memory your program will no longer keep up with.Find, first, next, prev, and last return	NULL if	the requested item doesnt exist.	
#endif

#ifndef LIST_H
#define LIST_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>



typedef void *data_t;
typedef struct list *list_t;
typedef struct node *node_list;
typedef int (*cmpfunc)(data_t, data_t);
list_t list_init(); 			/* create a new empty list */
int list_insert(list_t, data_t); 	/* insert at head of list */
int list_append(list_t, data_t); 	/* append to tail of list */
data_t list_find(list_t, data_t, cmpfunc cmp); /* find and sets current item using callback 							  compare function */
data_t list_first(list_t); 	/* return item at head of list, set current item */
data_t list_next(list_t); 	/* return next item after current item */
data_t list_prev(list_t); 	/* return prev item before current item */
data_t list_last(list_t); 	/* return item at tail of list, set current item */
int list_insert_before(list_t, data_t); 	/* before current item */
int list_insert_after(list_t, data_t); 		/* after current item */
int list_remove(list_t); 	/* remove current item */
int list_finalize(list_t);	/* free all resources allocated by the list */
#endif
