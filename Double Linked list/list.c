#include"list.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

//allocates memory for the list

List * createList(){
    List * list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    return list;
}

//inserts data value at the specified index into the list passed
void insertData(List * list, int index, Data value){
    Node * newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next =NULL;
    newNode->prev =NULL;
    Node * curr = list->head;
    if(curr==NULL){
        newNode->prev = list->tail;
        list->head = newNode;
        list->tail = newNode;
        list->length = list->length + 1;        
        return;
    }
    newNode->prev = list->tail;
    list->tail->next = newNode;
    list->tail = newNode;
    list->length= list->length + 1;        
}

void push(Stack * stack, Data value){
    Node * newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    Node * curr = stack->list->head;
    if(curr==NULL){
        newNode->prev = stack->list->tail;
        stack->list->head = newNode;
        stack->list->tail = newNode;
        stack->list->length++;
        return;
    }
    newNode->prev = stack->list->tail;
    stack->list->tail->next = newNode;
    stack->list->tail = newNode;
    stack->list->length++;
    return;
}

//Displays the value from the list in LIFO(Last in First Out) manner
Data pop(Stack * stack){
    Node * temp = stack->list->tail;
    Data dat = temp->data;
    if(stack->list->length==1){
        stack->list->tail = temp->prev;
        stack->list->head = NULL;
        stack->list->length-=1;
        free(temp);
        return dat;
    }
    stack->list->length-=1;
    stack->list->tail = temp->prev;
    stack->list->tail->next = NULL;
    free(temp);
    return dat;
}

void enqueue(Queue * queue, Data value){
    Node * newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    Node * curr = queue->list->head;
    if(curr==NULL){
        newNode->prev = queue->list->tail;
        queue->list->head = newNode;
        queue->list->tail = newNode;
        queue->list->length++;
        return;
    }
    newNode->prev = queue->list->tail;
    queue->list->tail->next = newNode;
    queue->list->tail = newNode;
    queue->list->length++;
    return;
}

//Displays the value from the list in FIFO(First in First Out) manner
Data dequeue(Queue * queue){
    Node * temp = queue->list->head;
    Data dat = temp->data;
    if(queue->list->length ==1){  
        queue->list->head = queue->list->tail= temp->next;
        free(temp);
        return dat;
    }
    queue->list->length-=1;
    queue->list->head = temp->next;
    queue->list->head->prev = NULL;
    free(temp);
    return dat;
}

//Returns data value based on the index of the list
Data * readData(List * list, int index){
    if(index<list->length)
    {   
        int num = isEmpty(list);
        if(num==0){
        	Node * temp = list->head;
	        if(index ==0) 
	            return &(temp->data);
	        int i=1;
	        while(i<=index)
	        {
	            temp = temp->next;
	            i++;
	        }
	        return &(temp->data);
        }       
    }
    return NULL;
}

//Returns the index of the value by traversing list from front
int searchForward(List * list, Data value){
    int i;
    Node * temp = list->head;
    for (i = 1; i <= list->length ; i++)
    {
        if(temp->data.value == value.value){
            return --i;
        }
        temp = temp->next;
    }
    return -1;

}

//Returns the index of the value by traversing list from back
int searchBackward(List * list, Data value){
    int i;
    Node * temp = list->tail;
    for (i = list->length; i >=1 ; i--)
    {
        if(temp->data.value == value.value){
            return ++i;
        }
        temp = temp->prev;
    }
      return -1;
}

//Remove the memory allocated for the list
void deleteList(List *list){
   Node * temp = list->head;
   while(temp!=NULL){
        Node * next = temp->next;
        free(temp);
        temp = next;
   }
   free(list);
}

//Returns 1 if list is empty else 0
int isEmpty(List *list){
    if(list->length==0)
        return 1;
    else
        return 0;
}

//Remove the data from the list based on the index
int removeData(List * list, int index){
    if(index>1){
        Node * temp = list->tail;
        list->tail = temp->prev;
        list->tail->next = NULL;
        free(temp);
        list->length--;
        return 0;
    }
    Node * temp = list->tail;
    list->tail =  temp->prev;
    list->head = NULL;
    list->length--;
    free(temp);
    return 0;
}