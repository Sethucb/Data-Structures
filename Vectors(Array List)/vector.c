#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

Vector * initVector() {
	Vector * vec;
	vec = (Vector *) malloc(sizeof(Vector));
	vec->current_size = 0;
	vec->max_size = 0;
	vec->data = NULL;
	vec->index_array = NULL;
	vec->index_size = 0;
	return vec;
}

void vectorInsert(Vector * array, int index, Data value) {
	vectorInsertBase(array, index, value, index * 2 + 1);
}
void vectorRemove(Vector * array, int index) {
	if(index >= array->current_size){
		return;
	}

	int index_pos = -1;
	int i =0;
	for(i = 0;i < array->index_size; i++){
		if(index == array->index_array[i]){
			index_pos = i;
			break;
		}
	}
	if(index_pos > -1){
		for (i = index_pos; i < array->index_size - 1; i++){
			array->index_array[i] = array->index_array[i + 1];
		}
		array->index_array[array->index_size] = -1;
		array->index_size--;
	}
	array->current_size--;
}
/* Insert data based on index value
*
*/

void vectorInsertBase(Vector * array, int index, Data value, int max_size){
	if(index >= array->max_size) {
		int prev_max_size = array->max_size;
		array->max_size = max_size;
		Data * arr =(Data*) malloc(sizeof(Data)*array->max_size);
		memset(arr,-1,(sizeof(Data)*array->max_size));
		memcpy(arr,array->data,sizeof(Data)*prev_max_size);
		free(array->data);
		array->data=arr;

		int * index_ar = (int *) malloc(sizeof(int) * array->max_size);
		memset(index_ar, -1, (sizeof(int) * array->max_size));
		memcpy(index_ar, array->index_array, sizeof(int)*array->index_size);
		free(array->index_array);
		array->index_array = index_ar;
	}

	array->index_array[array->index_size] = index;
	array->index_size++;
	array->data[index] = value;
	if(index > array->current_size)
		array->current_size = index+1;
}

void vectorInsertIncremental(Vector * array,int index, Data value) {
	vectorInsertBase(array, index, value, index+1);
}

void vectorInsertMine(Vector * array,int index, Data value) {
	vectorInsertBase(array, index, value, 3 * index+1);
}
void * deleteVector(Vector * array) {
	free(array->data);
	free(array->index_array);
	free(array);
	return NULL;
}

/*  Removes the data from the vector based on the index. 
 *
 */
Data * vectorRead(Vector * array, int index) {
	if(index >= array->max_size) {
		return NULL;
	}

	int index_exist = 0;
	int i =0;
	Data * not_initialized = NULL;

	for(i =0; i < array->index_size; i++){
		if(array->index_array[i] == index){
			index_exist = 1;
			break;
		}
	}
	if(index_exist == 1){
		return &(array->data[index]);	
	}else{
		not_initialized = &array->data[index];
		not_initialized->value = -1;
		return not_initialized;
	}
	
}
