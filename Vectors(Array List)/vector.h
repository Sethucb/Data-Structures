#ifndef _VECTOR_H_
#define _VECTOR_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Data_ {
	int value;
}Data;



typedef struct Vector_ {
	Data * data;
	int *index_array;
	unsigned int index_size;
	unsigned int current_size;
	unsigned int max_size;
}Vector;

Vector * initVector();
void vectorInsert(Vector * array, int index, Data value);
void vectorInsertIncremental(Vector * array, int index, Data value);
void vectorInsertMine(Vector * array, int index, Data value);
void vectorInsertBase(Vector * array, int index, Data value, int max_size);
Data * vectorRead(Vector * array, int index);
void vectorRemove(Vector * array, int index);
void * deleteVector(Vector *);

#endif
