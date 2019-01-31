/*
   sim.h
   Richard Coffey
   ECE 223
   Program #3
 */

typedef struct customer_s
{
    double arrival_time; /* gets to the store */
    double enqueue_time; /* gets in line for cashier */
    double checkout_time; /* gets to cashier */
    double leave_time; /* leaves the store */
} customer_t;

typedef struct event_s
{
    int event_type; /* type of event – see below */
    double event_time; /* sim time when event occurs */
    customer_t *customer; /* customer related to this event */
    int queue_number; /* queue related to this event */
} event_t;

/*
event types:
1 = EV_ARRIVE
2 = EV_ENQUEUE
3 = EV_CHECKOUT
4 = EV_LEAVE
*/
