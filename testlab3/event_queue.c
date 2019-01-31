
#include "event_queue.h"
#include "disk_queue.h"
#include<stdlib.h>
#include<stdio.h>



struct event_queue_s	{
	event_t *heap;
	int count;
	int max;
};
	

event_queue_t event_queue_init(int size)	{
	event_queue_t eq;
	eq = (event_queue_t)calloc(1, sizeof(struct event_queue_s));
	event_t *data;
	data = (event_t *)calloc(size+1, sizeof(struct event_s));
	eq->heap=data;
	eq->count=0;
	eq->max=size+1;
	return eq;
	
}

int event_queue_insert(event_queue_t eq, event_t ev)	{
		
	int full = event_queue_full(eq);
	if (full==1)	{
		printf("ERROR: Priority Queue Overflow.\n");
		return -1;
	}
	
	
	
	if (eq->count==0)	{
		eq->heap[1]=ev;
		eq->count=1;
		return 0;
	}
	else	{
		int parent;
		int current=eq->count+1;
		eq->heap[eq->count+1]=ev;
		//Sort the newly entered event by event_time
		while (current>1)	{
			parent=(current)/2;
			
			if (eq->heap[parent]==NULL)	{
				return 0;
			}
			
			if (eq->heap[current]->event_time<eq->heap[parent]->event_time)	{
				event_t temp;
				temp=eq->heap[parent];
				eq->heap[parent]=eq->heap[current];
				eq->heap[current]=temp;	
			}
			current=parent;
		}
		eq->count++;
		return 0;
	}
	
	
	
}

event_t event_queue_remove(event_queue_t eq)	{
	
	if (eq->count==0)	{
		return NULL;
	}
	
	
	
	event_t ev;
	ev=eq->heap[1]; //set ev to the root of the tree
	if (eq->count==1)	{ //if ev is the only element?
		eq->heap[1]=NULL;
		eq->count=0;
		
	}
	else	{
		eq->heap[1]=eq->heap[eq->count];
		eq->heap[eq->count]=NULL;
		int location=1;
		int left, right, min;
		eq->count--;
		while (location<eq->count)	{
			left=2*location;
			right=2*location+1;
			if (eq->heap[right]==NULL)	{
				min=left;
			}
			else if (eq->heap[left]==NULL)	{
				min=right;
			}
			
			else	{
				if (eq->heap[left]->event_time<=eq->heap[right]->event_time)	{
					min=left;
				}
				else	{
					min=right;
				}
			}	
			if (eq->heap[min]==NULL)	{
				return ev;
			}
			else	{ 
				if ((eq->heap[min]->event_time)<(eq->heap[location]->event_time))	{
					event_t temp;
					temp=eq->heap[location];
					eq->heap[location]=eq->heap[min];
					eq->heap[min]=temp;
					
				}
			}
			
			location=min;
		}
	}
	return ev;		
	
	
}

int event_queue_empty(event_queue_t eq)	{
	if (eq->count<=0)	{
		return 1;
	}
	else	{
		return 0;
	}
	
	
}

int event_queue_full(event_queue_t eq)	{
		
	if (eq->count>=eq->max)	{
		return 1;
	}
	else	{
		return 0;
	}
	
}

void event_queue_finalize(event_queue_t eq)	{
	
	/*int i;
	for (i=0; i<eq->max; i++)	{
		if (eq->heap[i]!=NULL)	{
			if (eq->heap[i]->request!=NULL)	{
				free(eq->heap[i]->request);
			}
			free(eq->heap[i]);
		}
	}*/
	free(eq->heap);
	free(eq);
	return;	
	
}
