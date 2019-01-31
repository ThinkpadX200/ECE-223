
#include "list.h"
#include "disk_queue.h"
#include<stdlib.h>
#include<stdio.h>


struct disk_queue_s	{
	list_t list;
};

struct list	{
	list_item_t current;
	list_item_t head;
	list_item_t tail;
};

disk_queue_t disk_queue_init(void)	{
	disk_queue_t dq;
	dq = (disk_queue_t)calloc(1,sizeof(struct disk_queue_s));
	dq->list=list_init();
	return dq;
}

int disk_queue_insert(disk_queue_t dq, request_t req)	{
	int success = list_append(dq->list,req);
	return success;
	
}

//returns the head of the dq
request_t disk_queue_peek(disk_queue_t dq)	{
	request_t req;
	req = dq->list->head->data;
	return req;
	
}

request_t disk_queue_remove(disk_queue_t dq)	{
	
	int empty = disk_queue_empty(dq);
	if (empty==1)	{
		return NULL;
	}
		
	dq->list->current=dq->list->head;
	request_t req;
	req = dq->list->head->data;
	int success=list_remove(dq->list);
	if (success!=0)	{
		printf("Error Removing Request\n");
		return NULL;
	}
	return req;
	
	
	
}

int disk_queue_empty(disk_queue_t dq)	{
	if (dq->list->head==NULL)	{
		return 1;
	}
	
	else 		{
		return 0;
	}
	
	
}

void disk_queue_finalize(disk_queue_t dq)	{
	
	
	int final = list_finalize(dq->list);
	if (final!=0)	{
		printf("Error Finalizing Disk Queue\n");
	}
	free(dq);
	return;
	
}