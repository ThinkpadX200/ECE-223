/* table.h */

#ifndef TABLE_H
#define TABLE_H
typedef void *data_t;

typedef int key_t;

typedef struct Item *Item_t;

typedef struct table *table_t; /* define struct table int table.c */

table_t Table_new(int table_size); /* initialize the table */

int Table_insert (table_t, key_t, data_t); /* insert one item */

data_t Table_find (table_t, key_t); /* find an item with key */

int Table_update(table_t, key_t, data_t); /* update item data in place */

data_t Table_remove (table_t, key_t); /* remove one item */

void Table_free (table_t *); /* free the entire table */

#endif
/* end of table.h */

