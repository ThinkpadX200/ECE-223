/* table.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"
#include "list.h"
#include "item.h"


typedef struct Item{

	data_t data;
	key_t key;

}*Item_t;

typedef struct table {


	list_t *hash_array;
	int TableSize;

} *table_t;

/* initialize the table */
table_t Table_new(int table_size){
	
	int i = 0;
	table_t t;
	t  = (table_t)calloc(1, sizeof(struct table));
	t->TableSize = table_size;
	t->hash_array = (list_t*)calloc(1,(sizeof(list_t)*table_size));
	for ( i = 0; i < table_size; i++){
		t->hash_array[i] = list_init();
	}
	return(t);

} 

/* insert one item */
int Table_insert (table_t table, key_t key, data_t data){
	
	Item_t found;
	int hash_value;
	hash_value = key % (table->TableSize);
	found = Table_find(table, key);
	if( found == NULL){
		found = (Item_t)calloc(1,sizeof(struct table));
		found->key = key;
		found->data = data;
		list_append(table->hash_array[hash_value], found);
		return(0);
	}
	else{
		return(-1);
	}
	

}

/* find an item with key */
data_t Table_find (table_t table, key_t key){
	
	Item_t start;
	int hash_value;
	hash_value = key % (table->TableSize);
	start = list_first(table->hash_array[hash_value]);
		while( start != NULL){
		if(start->key == key){
			return(start);
		}
		else{
			start = list_next(table->hash_array[hash_value]);
		}	
	}
	return(NULL);
	
}

/* update item data in place */
int Table_update(table_t table, key_t key, data_t data){
	
	Item_t found;
	found = Table_find(table, key);
	if( found != NULL){
		//found->data = data;
		return(0);
	}
	else{
		return(-1);
	}
	

} 

/* remove one item */
data_t Table_remove (table_t table, key_t key){

	Item_t found;
	data_t data;
	int hash_value;
	hash_value = key % (table->TableSize);
	found = Table_find(table, key);
	if( found != NULL){
		list_remove(table->hash_array[hash_value]);
		data = found->data;
		free(found);
		return(data);
	}
	else{
		return(NULL);
	}
	

} 

/* free the entire table */
void Table_free (table_t *table){
	
	int i = 0;
	Item_t temp;
	Item_t start;
	start = list_first((*table)->hash_array[i]);
	for( i=0; i< (*table)->TableSize;i++){
		start = list_first((*table)->hash_array[i]);
		while( start != NULL){
			temp = start;
			start = list_next((*table)->hash_array[i]);
			free(temp);
		}
	}
	for( i=0; i< (*table)->TableSize; i++){
		list_finalize((*table)->hash_array[i]);
	}
	free((*table)->hash_array);
	free(*table);
	
}
