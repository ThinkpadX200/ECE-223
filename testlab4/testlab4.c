/* lab4.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "table.h"
#define TABLESIZE 51


int main(){
	
	table_t hash_table;
	int i = 0;
	double no_coll_insert = 0;
	double no_coll_find = 0;
	double no_coll_update = 0;
	double no_coll_remove = 0;			
	data_t data;
	clock_t start;
	clock_t end;
	
	hash_table = Table_new(TABLESIZE);

	// Tests 1 without collisions
	start = clock();
	for( i=0; i<5; i++){
		// insert time
		data = 0;
		start = 0;
		end = 0;
		start = clock();
		Table_insert(hash_table, i, data);
		end = clock();
		no_coll_insert += (end-start);
	}
	for( i=0; i<5; i++){
		// find time
		start = 0;
		end = 0;
		start = clock();
		Table_find(hash_table, i);
		end = clock();
		no_coll_find += (end-start);
	}
	for( i=0; i<5; i++){
		// update time
		data = 0;
		start = 0;
		end = 0;
		start = clock();
		Table_update(hash_table, i, data);
		end = clock();
		no_coll_update += (end-start);
	}

	for(i=0; i<5; i++){
		// remove time
		start = 0;
		end = 0;
		start = clock();
		Table_remove(hash_table, i);
		end = clock();
		no_coll_remove += (end-start);
	}

	no_coll_insert = no_coll_insert/(5*CLOCKS_PER_SEC);
	no_coll_find  = no_coll_find/(5*CLOCKS_PER_SEC);
	no_coll_update = no_coll_update/(5*CLOCKS_PER_SEC);
	no_coll_remove = no_coll_remove/(5*CLOCKS_PER_SEC);
	printf("\nNo Collisions:");
	printf("\n%0.3e\n%0.3e\n%0.3e\n%0.3e\n", no_coll_insert, no_coll_find, no_coll_update, no_coll_remove);
	Table_free(&hash_table);
	
	table_t hash_table_coll;
	double coll_insert = 0;
	double coll_find = 0;
	double coll_update = 0;
	double coll_remove = 0;
	int key_array[1000000];
	
	hash_table_coll = Table_new(TABLESIZE);
	// Testing Insert with collisions
	for(i=0;i<1000000;i++){
		key_array[i] = rand()%1000000;
		start = 0;
		end = 0;
		data = 0;
		start = clock();
		Table_insert(hash_table_coll, key_array[i], data);
		end = clock();
		coll_insert += (end-start);
	}
	coll_insert = coll_insert/(1000000*CLOCKS_PER_SEC);
	printf("\nCollisions:\n");
	printf("%0.3e\n", coll_insert);

	// Testing Find with collisions
	for(i=0;i<1000000;i++){
		start = 0;
		end = 0;
		start = clock();
		Table_find(hash_table_coll, key_array[i]);
		end = clock();
		coll_find += (end-start);	
	}
	coll_find = coll_find/(1000000*CLOCKS_PER_SEC);
	printf("%0.3e\n", coll_find);	
	
	// Testing Update with collisions
	for(i=0;i<1000000;i++){
		start = 0;
		end = 0;
		data  = 0;
		start = clock();
		Table_update(hash_table_coll, key_array[i], data);
		end = clock();
		coll_update += (end-start);
	}
	coll_update = coll_update/(1000000*CLOCKS_PER_SEC);
	printf("\n%0.3e\n", coll_update);
	
	// Testing remove with collisions
	for(i=0;i<1000000;i++){
		start = 0;
		end = 0;
		start = clock();
		Table_remove(hash_table_coll, key_array[i]);
		end = clock();
		coll_remove += (end-start);	
	}
	coll_remove = coll_remove/(1000000*CLOCKS_PER_SEC);
	printf("%0.3e\n", coll_remove);	
	
	double Insert_constant = 0;
	double Find_constant = 0;
	double Update_constant = 0;
	double Remove_constant = 0; 
	
	Insert_constant = coll_insert / no_coll_insert;
	Find_constant = coll_find / no_coll_find;
	Update_constant = coll_update / no_coll_update;
	Remove_constant = coll_remove / no_coll_remove;
	
	printf("\nO(n) Constants:\n");
	printf("Insert Constant: %f\n", Insert_constant);
	printf("Find Constant: %f\n", Find_constant);
	printf("Update Constant: %f\n", Update_constant);
	printf("Remove Constant: %f\n", Remove_constant);

	Table_free(&hash_table_coll);
	
	


}
