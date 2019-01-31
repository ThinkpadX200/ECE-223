//*******************************************************************
//******************************list.h***************************
//*******************************************************************


#if 0
Here is	the	header	for	the	list	ADT. Note all functions	are	in	terms	to	data_t.		This	
must	use	a	double-linked	list.		You	code	must	accept	as	many	entries	as	possible	
until	memory	is	exhausted.		Your	program	must	not	have	a	memory	leak	– meaning	
that	at	no	time	may	data	you	have	allocated	be	inaccessible	or	put	another	way,	you	
must always	call	free()	on	any	memory	your	program	will	no	longer	keep	up	with.		
Find,	first,	next,	prev,	and	last	return	NULL	if	the	requested	item	does not	exist.
#endif


typedef void *data_t;
typedef struct list *list_t;
typedef struct list_item	{
	data_t data;
	struct list_item *prev;
	struct list_item *next;
} *list_item_t;

typedef int (*cmpfunc)(data_t, data_t);
/* create a new empty list */
list_t list_init(void);
/* insert at head of list */
int list_insert(list_t list, data_t data);
/* append to tail of list */
int list_append(list_t list, data_t data);
/* find and sets current item using callback compare function */
data_t list_find(list_t list, data_t data, cmpfunc cmp);
/* return item at head of list, set current item */
data_t list_first(list_t list);
/* return next item after current item */
data_t list_next(list_t list);
/* return prev item before current item */
data_t list_prev(list_t list);
/* return item at tail of list, set current item */
data_t list_last(list_t list);
/* before current item */
int list_insert_before(list_t list, data_t data);
/* after current item */
int list_insert_after(list_t list, data_t data);
/* remove current item */
int list_remove(list_t list);
/* free all resources allocated by the list */
int list_finalize(list_t list);