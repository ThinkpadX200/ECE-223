//*******************************************************************	
//*********************************list.c*****************************
//*******************************************************************

#include "list.h"
#include <stdlib.h>
#include <stdio.h>


	
struct list	{
	list_item_t current;
	list_item_t head;
	list_item_t tail;
};
	
list_t list_init(void)	{
	
	list_t list;
	list=(list_t)calloc(1,sizeof(struct list));
	if (!list)
		return list;
	list->current=NULL;
	list->head=NULL;
	list->tail=NULL;
	
	return list;
	
}

int list_insert(list_t list, data_t data)	{
	list_item_t item;
	item=list->head;
	list->head=(list_item_t)calloc(1,sizeof(struct list_item));
	if (item==NULL)	{
		list->head->data=data;
		list->head->next=NULL;
		list->head->prev=NULL;
		list->tail=list->head;
	}
	else if (list->head==list->tail)	{
		list->head=(list_item_t)calloc(1,sizeof(struct list_item));
		list->head->prev=NULL;
		list->head->next=list->tail;
		list->head->data=data;
		list->tail->prev=list->head;
	}
	
	else	{
	
		list->head->next=item;
		list->head->data=data;
		list->head->prev=NULL;
		item->prev=list->head;
	}
	return 0;
	
}

int list_append(list_t list, data_t data)	{
	
	if (list->head==NULL)	{
		int success=list_insert(list,data);
		if (success!=0)	{
			return -1;
		}
	}
	
	
	else if (list->head==list->tail)	{
		list->tail=(list_item_t)calloc(1,sizeof(struct list_item));
		list->tail->prev=list->head;
		list->tail->next=NULL;
		list->tail->data=data;
		list->head->next=list->tail;
	}
	
	
	else	{
	
		list_item_t item;
		item=list->tail;
		list->tail=(list_item_t)calloc(1,sizeof(struct list_item));
		list->tail->prev=item;
		list->tail->next=NULL;
		list->tail->data=data;
		item->next=list->tail;
	}
	return 0;
	
}

data_t list_find(list_t list, data_t data, cmpfunc cmp)	{
	struct list_item *rover;
	rover=list->head;
	int match=-1;
	while ((rover != NULL)&&(match!=0))		{
		match=(*cmp)(data, rover->data);
		if (match==-1)	{
			rover=rover->next;
		}
		else {
			list->current=rover;
			return rover->data;
		}
		
	}
	
	
	return NULL;
}



int list_insert_before(list_t list, data_t data)	{
	if (list->head->next==list->tail)	{
		if (list->current==list->head)	{
			int success = list_insert(list, data);
			if (success!=0)	{
				printf("ERROR\n");
			}
		}
		else	{
			list_item_t new;
			new=(list_item_t)calloc(1,sizeof(struct list_item));
			new->prev=list->head;
			new->next=list->tail;
			new->data=data;
			list->head->next=new;
			list->tail->prev=new;
			
		}
		
	}
	else	{
		list_item_t new, temp;
		temp=list->current;
		new=(list_item_t)calloc(1,sizeof(struct list_item));
		new->prev=temp->prev;
		new->next=temp;
		new->data=data;
		(temp->prev)->next=new;
		temp->prev=new;
	}
	return 0;
}
	
int list_insert_after(list_t list, data_t data)	{
	if (list->head->next==list->tail)	{
		if (list->current==list->head)	{
			int success = list_append(list, data);
			if (success!=0)	{
				printf("ERROR\n");
			}
		}
		else	{
			list_item_t new;
			new=(list_item_t)calloc(1,sizeof(struct list_item));
			new->prev=list->tail;
			new->next=NULL;
			new->data=data;
			list->head->next=new;
			list->tail->prev=new;
			
		}
		
	}
	else	{
		list_item_t new, temp;
		temp=list->current;
		new=(list_item_t)calloc(1,sizeof(struct list_item));
		new->prev=temp;
		new->next=temp->next;
		new->data=data;
		(temp->next)->prev=new;
		temp->next=new;
	}
	return 0;
}





int list_remove(list_t list)	{
	list_item_t temp;
	temp=list->current;
	
	if (list->head==list->tail)	{
		free(list->head);
		list->head=NULL;
		
	}
	
	else if (temp==list->head)	{
		list->head=temp->next;
		free(temp);
		list->head->prev=NULL;
	}
	
	else if (temp==list->tail)	{
		list->tail=temp->prev;
		free(temp);
		list->tail->next=NULL;
	}
	
	else	{
		(list->current->prev)->next=temp->next;
		(list->current->next)->prev=temp->prev;
	}
	return 0;
}

int list_finalize(list_t list)	{
	list_item_t rover,next_rover;
	rover=list->head;
	while (rover != NULL)	{
		next_rover=rover->next;
		free(rover);
		rover=next_rover;
	}
	free(list);
	return 0;
}