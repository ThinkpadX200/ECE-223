/* list.c
 * Nathan Bayles    
 * nbayles          
 * ECE 2230-001, Spring 2017
 * MP2
 * ECE223-1,#2
 * 
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"


typedef struct node 
{
	struct node *next;
	struct node *prev;
	data_t item;
}*node_list;

typedef struct list
{
	node_list head;
	node_list current;
	node_list tail;	
}*list_t;
 



list_t list_init()
{
	//Initialize and set everything to NULL
	list_t new_list;
	new_list = (struct list*)calloc(1, sizeof(struct list));
	new_list->head = NULL;
	new_list->current = NULL;
	new_list->tail = NULL;
	return(new_list);

};


data_t list_find(list_t list, data_t guitar, cmpfunc cmp){
	
	data_t list_item;
	list_item = list_first(list);
	
	//While loop to scroll through, waits for return to be 0
	while(list_item != NULL)
	{
		if( cmp(list_item, guitar) == 0)
		{
			return(list_item);
		}
		else
		{
			list_item = list_next(list);
		}
		
	
	}
	return(NULL);
	

}

 
int list_insert(list_t list, data_t item){
 	
 	// Allocates memory and inserts item if the list is empty
 	if( list->head == NULL)
 	{
 		node_list new_node;
 		new_node = (node_list)calloc(1,sizeof(struct node));
 		new_node->item = item;
 		new_node->prev = NULL;
 		new_node->next = NULL;
 		list->head = new_node;
 		list->tail = new_node;
 		list->current = new_node;
 		return(0);
 	}
 	// Add item when the list already has at least one item
 	else
 	{
 		node_list new_node;
 		new_node = (node_list)calloc(1,sizeof(struct node));
 		new_node->item = item;
 		new_node->next = list->head;
 		new_node->prev = NULL;
 		list->head->prev = new_node;
 		list->head = new_node;
 		list->current = new_node;
 		return(0);
 	}
 	
 	return(-1);
}

// Add to tail
int list_append(list_t list, data_t item){
 
 	//Insert if list is empty
 	if(list->head == NULL)
 	{
 		return(list_insert(list,item));
 	}
 	//Otherwise adds to end
 	else
 	{
	 	node_list new_node;
	 	new_node = (node_list)calloc(1,sizeof(struct node));
	 	new_node->item = item;
	 	new_node->prev = list->tail;
	 	new_node->next = NULL;
	 	list->tail->next = new_node;
	 	list->tail = new_node;
	 	return(0);
 	}
 
 	return(-1);
 }

/* return item at head of list, set current item */
data_t list_first(list_t list)
{
	list->current = list->head;
	if ( list->head)
	{
		return(list->current->item);
	}
	else
	{
		return(NULL);
	}
	

}

/* return next item after current item */
data_t list_next(list_t list)
{
	if(list->current)
	{
		list->current = list->current->next;
		if ( list->current)
		{
			return(list->current->item);
		}
		else
		{
			return(NULL);
		}
	}
	else
	{
		return(NULL);
	}
}

/* return prev item before current item */
data_t list_prev(list_t list)
{
	
	if(list->current)
	{
		list->current = list->current->prev;
		return(list->current->item);
	}
	else
	{
		return(NULL);
	}
}

/* return item at tail of list, set current item */
data_t list_last(list_t list)
{
	list->current = list->tail;
	if( list->tail)
	{
		return(list->current->item);
	}
	return(NULL);
}

/* before current item */
int list_insert_before(list_t list, data_t item)
{
	// Inserts if empty
	if(list->head == NULL)
	{
		return(list_insert(list, item));
		
	}
	//Checks to make sure current isn't pointing to null
	else if( list->current == NULL)
	{
		return(-1);
	}
	//Insert before if at head and change new head
	else if ( list->current == list->head)
	{
		node_list new_node;
	 	new_node = (node_list)calloc(1,sizeof(struct node));
	 	new_node->item = item;
	 	new_node->next = list->head;
	 	list->head->prev = new_node;
	 	new_node->prev = NULL;
	 	list->head = new_node;
	 	return(0);
	}
	//Inserts before if surrounded by two items
	else 
	{
		node_list new_node;
	 	new_node = (node_list)calloc(1,sizeof(struct node));
	 	new_node->item = item;
		new_node->next = list->current;
		new_node->prev = list->current->prev;
		list->current->prev->next = new_node;
		list->current->prev = new_node;
		return(0);
	}
	
	
}

/* after current item */
int list_insert_after(list_t list, data_t item)
{
	//Checks if list is empty
	if( list->head == NULL)
	{
		return(list_insert(list,item));
	}
	//Make sure current is not pointing to null
	else if ( list->current == NULL)
	{
		return(-1);
	}
	// Insert after in the case of being at the tail
	else if ( list->current == list->tail)
	{
		node_list new_node;
	 	new_node = (node_list)calloc(1,sizeof(struct node));
	 	new_node->item = item;
	 	new_node->prev = list->tail;
	 	new_node->next = NULL;
	 	list->tail->next = new_node;
	 	list->tail = new_node;
	 	return(0);
	}
	// Insert after if surrounded by two items
	else
	{
		node_list new_node;
	 	new_node = (node_list)calloc(1,sizeof(struct node));
	 	new_node->item = item;
	 	new_node->prev = list->current;
	 	new_node->next = list->current->next;
	 	list->current->next->prev = new_node;
	 	list->current->next = new_node;
	 	
	}
	return(0);
}

/* remove current item */
int list_remove(list_t list)
{
	node_list temp;
	
	// checks to see if removing something when the list is empty
	if(list->head == NULL)
	{
		return(-1);
	}
	// Delete in the case of only one item in list, reset head, tail and current
	else if ( list->current == list->head && list->current == list->tail)
	{
		free(list->current);
		list->head = NULL;
		list->current = NULL;
		list->tail = NULL;
		return(0);
	}
	// Delete at the end of list and reset tail
	else if ( list->current == list->tail)
	{
		list->current->prev->next = NULL;
		list->tail = list->current->prev;
		temp = list->current;
		list->current = list->current->prev;
		free(temp);
		return(0);
	}
	//Delete at beginning of list and reset head
	else if ( list->current == list->head)
	{
		list->current->next->prev = NULL;
		list->head = list->current->next;
		temp = list->current;
		list->current = list->current->next;
		free(temp);
		return(0);
	}
	//Delete item in between two other items
	else
	{
		list->current->next->prev = list->current->prev;
		list->current->prev->next = list->current->next;
		temp = list->current;
		list->current = list->current->next;
		free(temp);
		return(0);
	}
}

/* free all resources allocated by the list */
int list_finalize(list_t list)
{
	node_list temp1;
	node_list start;
	
	//Scroll through and free each item then free the entire list
	start = list->head;
	while ( start != NULL)
	{
		temp1 = start;
		start = start->next;
		free(temp1);
	}	
	free(list);
	return(0);
}




