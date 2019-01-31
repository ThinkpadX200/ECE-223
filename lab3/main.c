/*
   main.c
   Richard Coffey
   ECE 223
   Program #3

    **NOTE**

    1. Please set both parameters or let them go to defaults
    2. Keep event queue size above 1000
    3. Change customer count by changing the define MAX_CUST
    4. If I have sarcastic comments to myself left in please ignore them
    


 */

#define MAX_CUST 100000
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "sim.h"
//#include "list.h"
#include "priority.h"
#include "randsim.h"
#include <string.h>

//prototypes for random numbers
double randsim_uni();
double randsim_exp();
double randsim_gauss();

//prototype for event creation
void schedule(priority_t *eventqueue, double time, int type, customer_t *cust,int queue_num);

//global for customer count
int numcustomers;


int main(int argc, char *argv[]) {

    int maxevents = 0;
    int numqueues = 0;

    //handling the command line arguments
    if (argc == 1) {

        maxevents = 10000;
        numqueues = 7;

        printf("\nNo flags set, default sizes for Event Queue Size (10000) and Number of Queues (7) were used.\n"); 

    }

    else if (argc == 5) {

        if ((strcmp(argv[1], "-e") == 0) && (strcmp(argv[3],"-q") == 0)) {

            maxevents = atoi(argv[2]);
            numqueues = atoi(argv[4]);


            printf("\nEvent Queue set to size %d and Number of Queues set to %d\n", maxevents, numqueues); 
        }

        else {
            printf("\nPlease use command arguments:\n./prog -e [Size of Event Queue] -q [Number of Queues]\n");
            exit(1);
        }
    }

    else {

        printf("\nIf you would like to run the program with default values, please use no arguments.\n\n Otherwise please use command arguments:\n./prog -e [Size of Event Queue] -q [Number of Queues]\n\n");
        exit(1);
    }

    int inits;
    int queuemaxsize = 100; //arbitrary variable for queue_init
    queue_t *cashiers[numqueues]; //this is the queue array
    priority_t *eventqueue;
    double curr_time = 0;
    event_t *new_ev;
    double shop_time; //used for random num gen
    double next_customer; //
    double checkout; //
    int i;
    int shortestline;
    int shortestqueue;
    int queueselect;
    double queue_time, total_time, shopping_time;
    double mintotaltime = 1000;
    double minqueuetime = 1000;
    double maxtotaltime = 0;
    double maxqueuetime = 0;
    double totqueuetime = 0;
    double tottotaltime = 0;
    double totshoptime = 0;
    double avetotaltime, avequeuetime, aveshoptime;

    customer_t *new_customer;
    customer_t *peek_customer;
    customer_t *rc;




    //initializing the Array of Queues # of cashiers

    //cashiers = (queue_t *)malloc(numqueues * sizeof(queue_t));
    for (inits = 0; inits < numqueues; inits++) {
        cashiers[inits] = queue_init(queuemaxsize);     
    }

    //initializing the priority queue
    //eventqueue is a pointer to the eventqueue
    eventqueue = priority_init(maxevents);

    //creating a first event
    customer_t *firstcustomer;
    firstcustomer = (customer_t *)malloc(sizeof(customer_t));
    schedule(eventqueue, curr_time, 1, firstcustomer, -1); 

    while (!priority_empty(eventqueue)) {

        //pop an event off of the event_queue
        new_ev = priority_remove(eventqueue);
        //
        curr_time=new_ev->event_time;
        //time set statement here



        switch (new_ev->event_type) {

            case(1): 

                new_ev->customer->arrival_time = curr_time;

                //schedule an enqueue time
                shop_time = TIME_SHOP() + curr_time;
                schedule(eventqueue, shop_time, 2, new_ev->customer, -1);

                //malloc a new customer event if customer # isn't reached
                if (MAX_CUST > numcustomers++) {

                    new_customer = (customer_t *)malloc(sizeof(customer_t));
                    next_customer = TIME_ARRIVE() + curr_time;
                    schedule(eventqueue, next_customer, 1, new_customer, -1);

                }

                break;

            case(2):

                new_ev->customer->enqueue_time = curr_time;

                /* 
                   for (i=0; i <numqueues; i++) {
                   printf("%d\n", queue_size(cashiers[i]));
                   }
                   printf("\n");
                 */

                //find shortest line
                //queues are a bit fucked

                shortestline = queue_size(cashiers[0]);
                shortestqueue = 0;

                for (i = 0; i < numqueues; i++) {

                    if (queue_size(cashiers[i]) < shortestline) {
                        //if new shorter line found
                        shortestline = queue_size(cashiers[i]);
                        shortestqueue = i;
                    }
                }

                //if line is empty, send directly to checkout
                if (shortestline == 0) { 

                    schedule(eventqueue, curr_time, 3, new_ev->customer, shortestqueue);
                }

                //always insert into queue
                queue_insert(cashiers[shortestqueue], new_ev->customer);

                break;

            case (3):

                /* On case 3 we're getting 2 cases
                   1. There's one person checking out with no one behind them
                   / 2. Checkout with someone in line behind them
                 */

                //new_ev->customer->checkout_time = curr_time;

                //picking queue from which this customer is coming from
                queueselect = new_ev->queue_number; 

                checkout = TIME_CHECKOUT() + curr_time;

                peek_customer = queue_peek(cashiers[queueselect]);

                //if no one is in line behind
                if (peek_customer == NULL) {
                    //find checkout time
                    //new_ev->customer->checkout_time = curr_time;

                    //schedule leave event for new_ev customer                   
                    schedule(eventqueue, checkout, 4, new_ev->customer, queueselect);
                }
                //if there is someone behind them
                else {

                    peek_customer->checkout_time = curr_time;

                    //schedule a leave event for this event
                    schedule(eventqueue, checkout, 4, new_ev->customer, queueselect);
                }

                break;

            case(4):

                /* Two possible cases:
                   1. Customer leaving behind an empty line
                   2. Customer leaving and next customer is brought up
                 */

                //get queue number for next customer if necessary
                queueselect = new_ev->queue_number;

                //removing next customer/ peek customer
                rc = queue_remove(cashiers[queueselect]);


                if (rc != NULL) {

                    new_ev->customer->leave_time = curr_time;

                    rc->leave_time = curr_time;

                    //if there is someone behind them
                    if (queue_size(cashiers[queueselect]) != 0) {

                        //if this line hits, then someone will always be behind 
                        //otherwise we could seg fault at line 196
                        schedule(eventqueue, curr_time, 3, rc, queueselect);
                    }
                }
                //statistics
                queue_time = rc->checkout_time - rc->enqueue_time;
                total_time = rc->leave_time - rc->arrival_time; 
                shopping_time = rc->enqueue_time - rc->arrival_time;                    

                tottotaltime += total_time;
                totqueuetime += queue_time;
                totshoptime += shopping_time;


                //Update Stats
                if (queue_time > maxqueuetime)	{
                    maxqueuetime = queue_time;
                }
                if (queue_time < minqueuetime)	{
                    minqueuetime = queue_time;
                }
                if (total_time > maxtotaltime)	{
                    maxtotaltime = total_time;
                }
                if (total_time < mintotaltime)	{
                    mintotaltime = total_time;
                }

                       
                break;

            default:
                

                break;
        }
        if (new_ev != NULL) {
        free(new_ev);        
              }
  
    }

    //freeing
    for (i = 0; i < numqueues; i++) {
        queue_finalize(cashiers[i]);
    }
    //free(cashiers);

    priority_finalize(eventqueue);

    free(firstcustomer);
    free(new_customer);

    /*subtract 1 customer because I have an extra increment somewhere*/
    numcustomers--;

    avequeuetime =  totqueuetime/numcustomers;
    avetotaltime =  tottotaltime/numcustomers;
    aveshoptime = totshoptime/numcustomers;


    if (numcustomers == 0) {
        printf("No Customers in Database\n");
    }
    else {

        printf("Simulation Finished: Here are the stats:\n");
        printf("Customer Count: %d\n", numcustomers);
        printf("Average Shopping Time: %f\n", aveshoptime);
        printf("Minimum Queue Time: %f\n", minqueuetime);
        printf("Maximum Queue Time: %f\n", maxqueuetime);
        printf("Average Queue Time: %f\n", avequeuetime);
        printf("Minimum Total Time: %f\n", mintotaltime);
        printf("Maximum Total Time: %f\n", maxtotaltime);
        printf("Average Total Time: %f\n", avetotaltime);

    }



    return(0);

}

//arguments: priorty queue, event_t struct
void schedule(priority_t *eventqueue, double time, int type, customer_t *cust, int queue_num) {

    struct event_s *ev;
    ev = (struct event_s *)malloc(sizeof(struct event_s));
    ev->event_time = time;
    ev->event_type = type;
    ev->customer = cust;
    ev->queue_number = queue_num;

    priority_insert(eventqueue, ev);

}


