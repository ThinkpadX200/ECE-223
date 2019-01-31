

typedef struct disk_queue_s *disk_queue_t;
typedef struct request_s //struct customer_s customer_t	{
    int track;
    double arrival_time;
    double start_time;
    double finish_time;
} *request_t;



disk_queue_t disk_queue_init(void);
int disk_queue_insert(disk_queue_t eq, request_t req);
request_t disk_queue_peek(disk_queue_t dq);
request_t disk_queue_remove(disk_queue_t dq);
int disk_queue_empty(disk_queue_t dq);
void disk_queue_finalize(disk_queue_t dq);
