#ifndef _LIST_H_
#define _LIST_H_

typedef struct data_{
	int value;
}Data;

typedef struct node_{
	Data data;
	struct node_ * next;
	struct node_ * prev;
}Node;

typedef struct list_{
	Node * head;
	Node * tail;
	int length;
}List;

typedef struct stack_{
	List * list;
}Stack;

typedef struct queue_{
	List * list;
}Queue;

List * createList();
void insertData(List * list, int index, Data value);
int removeData(List * list, int index);
Data * readData(List * list, int index);
int isEmpty(List *);
void deleteList(List * );
int searchForward(List *, Data);
int searchBackward(List *, Data);
void push(Stack *, Data);
Data pop(Stack *);
void enqueue(Queue *, Data);
Data dequeue(Queue *);

#endif