
typedef struct request_s *request_t; //struct customer_s customer_t
typedef struct event_queue_s *event_queue_t; //struct priority_s priority.c
typedef struct event_s	{ //event_s
	int event_type;
	double event_time;
	request_t request;
}*event_t;

event_queue_t event_queue_init(int size);
int event_queue_insert(event_queue_t eq, event_t ev);
event_t event_queue_remove(event_queue_t eq);
int event_queue_empty(event_queue_t eq);
int event_queue_full(event_queue_t eq);
void event_queue_finalize(event_queue_t eq);
