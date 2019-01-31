

#define MAX_PROCESS 1000000
#include "disk_queue.h"
#include "event_queue.h"
#include "list.h"
#include "disk.h"
#include "randsim.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double randsim_exp();
double randsim_gauss();
event_t create_event(event_t oev, int type, double current_time);


int main(void)	{	
	double global_time=0;
	int pq_number=0;
	int event_count=0;
	int request_count=0;
	int dq_number=0;
	double maxqueue=0,minqueue=0,avgqueue,totqueue=0;
	double maxio=0,minio=0,avgio,totio=0;
	double maxtot=0,mintot=0,avgtot,tottot=0;
	event_queue_t eq;
	int size;
	printf("Enter the size of the Priority Queue: ");
	scanf("%d",&size);
	eq = event_queue_init(size);
	disk_queue_t dq;
	dq = disk_queue_init();
	event_t iev;
	iev=create_event(NULL,1,global_time);
	event_count++;
	int success = event_queue_insert(eq,iev);
	if (success==-1)	{
		free(iev);
		pq_number=0;
	}
	pq_number++;
	int current_track=0;
	request_t req=NULL;
	request_t removed=NULL;
	event_t ev, nev;
	while (pq_number)	{
		int ev_empty = event_queue_empty(eq);
		if (ev_empty==1)	{
			pq_number=0;
		}
		ev = event_queue_remove(eq);
		event_count--;
		global_time=ev->event_time;
		ev_empty = event_queue_empty(eq);
		if (ev_empty==1)	{
			nev = create_event(ev,1,global_time);
			event_count++;
			success = event_queue_insert(eq,nev);
			if (success==-1)	{
				free(nev);
				pq_number=0;
				
			}
			pq_number++; 
		}
		switch (ev->event_type)	{
			case (1) :
				
				if ((request_count<MAX_PROCESS)&&(event_queue_full(eq)!=-1))	{
					nev = create_event(ev,1,global_time);
					event_count++;
					success = event_queue_insert(eq,nev);
					if (success==-1)	{
						free(nev);
						pq_number=0;
					}
					pq_number++;
				}
				else	{
					pq_number=0;
				}
				if (disk_queue_empty(dq))	{
					nev = create_event(ev,2,global_time);
					event_count++;
					nev->event_time=global_time;
					success = event_queue_insert(eq,nev);
					if (success==-1)	{
						free(nev);
						pq_number=0;
					}
				}
				success = disk_queue_insert(dq,ev->request);
				dq_number++;
				free(ev);
				ev=NULL;
				break;
			case (2) :     
				
				req=disk_queue_peek(dq);
				req->start_time=global_time;
				double track_time=seek_time(current_track,req->track);
				req->finish_time=track_time+global_time;
				current_track=req->track;
				nev = create_event(ev,3,global_time);
				event_count++;
				nev->event_time=req->finish_time;
				success = event_queue_insert(eq,nev);
				if (success==-1)	{
					free(nev);
					pq_number=0;
				}
				free(ev);
				ev=NULL;
				break;
			case (3) :
				if (dq_number>0)	{
					removed=disk_queue_remove(dq);
				}	
				dq_number--;

				if (dq_number>0)	{
					nev=create_event(ev,2,global_time);
					event_count++;
					nev->event_time=global_time;
					success = event_queue_insert(eq,nev);
				}
				

				
				if (success==-1)	{
					free(nev);
					pq_number=0;
				}
				
				
				
				//Calculate Times free
				double queue_time;
				double io_time;
				double tot_time;
				queue_time=(removed->start_time)-(removed->arrival_time);
				io_time=(removed->finish_time)-(removed->start_time);
				tot_time=queue_time+io_time;
				
				
				//Update Stats
				if (queue_time>maxqueue)	{
					maxqueue=queue_time;
				}
				if (io_time>maxio)	{
					maxio=io_time;
				}
				if (tot_time>maxtot)	{
					maxtot=tot_time;
				}
				totqueue=totqueue+queue_time;
				totio=totio+io_time;
				tottot=tottot+tot_time;
				if ((queue_time<minqueue)||(minqueue==0))	{
					minqueue=queue_time;
				}
				if ((io_time<minio)||(minio==0))	{
					minio=io_time;
				}
				if ((tot_time<mintot)||(mintot==0))	{
					mintot=tot_time;
				}
				if (removed!=NULL)	{
					free(removed);
				}
				removed=NULL;
				request_count++;
				free(ev);
				ev=NULL;
				break;
			default:
				printf("Invalid Event\n");
				free(ev);
				ev=NULL;
				break;
		}
		int empty = event_queue_empty(eq);
		if (empty==1)	{
			printf("The Priority Queue is empty. Simulation is over.");
			pq_number=0;
		}
		
		
		
				
	}
	//Calculate Averages
	avgqueue=totqueue/request_count;
	avgio=totio/request_count;
	avgtot=tottot/request_count;
	
	//Print Stats
	if (request_count==0)	{
		printf("No Requests Processed.\n");
	}
	else	{
	
		printf("Simulation Finished. Your stats are:\n");
		printf("Requests Processed: %d\n",request_count);
		printf("Minimum Queue Time: %f\n",minqueue);
		printf("Maximum Queue Time: %f\n",maxqueue);
		printf("Average Queue Time: %f\n",avgqueue);
		printf("Minimum IO Time: %f\n", minio);
		printf("Maximum IO Time: %f\n", maxio);
		printf("Average IO Time: %f\n", avgio);
		printf("Minimum Total Time: %f\n", mintot);
		printf("Maximum Total Time: %f\n", maxtot);
		printf("Average Total Time: %f\n", avgtot);
	}
	
	
	
	
	
	while (removed!=NULL)	{
		removed=disk_queue_remove(dq);
		free(removed);
	}
	disk_queue_finalize(dq);
	while ((event_count>0))	{
		ev=event_queue_remove(eq);
		if (ev!=NULL)	{
			if (ev->request!=NULL)	{
				free(ev->request);
				ev->request=NULL;
			}
			free(ev);
			ev=NULL;
					
		}
		event_count--;
	}
	event_queue_finalize(eq);
		
	
	
	
}

event_t create_event(event_t oev, int type, double current_time)	{
	
	event_t ev;
	ev = (event_t)calloc(1,sizeof(struct event_s));
	ev->event_time=randsim_exp()+current_time;
	ev->event_type=type;
	if (type==1)	{
		request_t req;
		req=(request_t)calloc(1,sizeof(struct request_s));
		req->track=request_track();
		
		ev->request=req;
	}
	else if ((type==2)||(type==3))	{
		ev->request=oev->request;
	}
	else	{
		printf("Invalid Type\n");
	}
	
	
	return ev;
}
	

