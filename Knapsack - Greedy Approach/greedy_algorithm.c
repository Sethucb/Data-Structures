#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define ITEM_SIZE 10

typedef struct knap_{
	int weight;
	int profit;
	int unit_ben;
}KNAP;

KNAP elements[ITEM_SIZE];
int elem_num;
int capacity;

int ben_max_weight,ben_max_profit;int ben_items[10];
int gd2_max_weight,gd2_max_profit;int gd2_items[10];
int gd3_max_weight,gd3_max_profit;int gd3_items[10];
int gd4_max_weight,gd4_max_profit;int gd4_items[10];

// Solve the knapsack using maximum benefit first greedy approach
void max_benefit(){

   int i,j;
	int cnt = 0;
	
   //Sort the struct of items based on benefit
   for (i = 0; i < elem_num-1; i++){
      for (j = i+1; j < elem_num; j++) {
         if (elements[j].profit > elements[i].profit) {
            KNAP temp = elements[j];
            elements[j] = elements[i];
            elements[i] = temp;
         }
      }
   }
  
  // Place the sorted struct into bag
   for(i = 0; i < elem_num; i++){
   	if(ben_max_weight + elements[i].weight <= capacity){
   		ben_max_weight += elements[i].weight;
    		ben_max_profit += elements[i].profit;
    		ben_items[cnt++] = i;
   	}
   }
   printf("\n--------------GREEDY 1 MAXIMUM BENEFIT--------------------\n");
   printf("\n-------------Total profit and weight--------------\n");
   printf("Total weight = %d\n", ben_max_weight);
   printf("Total profit = %d\n", ben_max_profit);  
   
   printf("\n-------------Selected items' profit and weight--------------\n");
   for(j = 0;j < cnt;j++){
   	printf("Weight of item%d is %d \n",j+1,elements[ben_items[j]].weight);
   	printf("Profit of item%d is %d \n",j+1,elements[ben_items[j]].profit);
   }
   printf("\n");
}

// Solve the knapsack using minimum weight greedy approach
void min_weight(){
	int i,j;
	int cnt = 0;

   //Sort the struct of items based on weight
	for (i = 0; i < elem_num-1; i++){
      for (j = i+1; j < elem_num; j++) {
         if (elements[j].weight < elements[i].weight) {
            KNAP temp = elements[j];
            elements[j] = elements[i];
            elements[i] = temp;
         }
      }
  }

  // Place the sorted struct into bag
   for(i = 0; i < elem_num; i++){
      if(gd2_max_weight + elements[i].weight <= capacity){
      	gd2_max_weight += elements[i].weight;
      	gd2_max_profit += elements[i].profit;
      	gd2_items[cnt++] = i;	
      }
   }
   printf("\n--------------GREEDY 2 MINIMUM WEIGHT--------------------\n");
   printf("\n-------------Total profit and weight--------------\n");
   printf("Total weight = %d\n", gd2_max_weight);
   printf("Total profit = %d\n", gd2_max_profit);  
   
   printf("\n-------------Selected items' profit and weight--------------\n");
   for(j = 0;j < cnt;j++){
   	printf("Weight of item%d is %d \n",j+1,elements[gd2_items[j]].weight);
   	printf("Profit of item%d is %d \n",j+1,elements[gd2_items[j]].profit);
   }
   printf("\n");
}

// Solve the knapsack using maximum weight greedy approach
void max_weight(){
	int i,j;
	int cnt=0;
  
  //Sort the struct of items based on weight
	for (i = 0; i < elem_num-1; i++){
      for (j = i+1; j < elem_num; j++) {
         if (elements[j].weight > elements[i].weight) {
            KNAP temp = elements[j];
            elements[j] = elements[i];
            elements[i] = temp;
         }
      }
  }

  // Place the sorted struct into bag
   for(i = 0; i < elem_num; i++){
   	if(gd3_max_weight + elements[i].weight <= capacity){
   		gd3_max_weight += elements[i].weight;
     		gd3_max_profit += elements[i].profit;
     		gd3_items[cnt++] = i;	
   	}
   }

   printf("\n--------------GREEDY 3 MAXIMUM WEIGHT--------------------\n");
   printf("\n-------------Total profit and weight--------------\n");
   printf("Total weight = %d\n", gd3_max_weight);
   printf("Total profit = %d\n", gd3_max_profit);

   printf("\n-------------Selected items' profit and weight--------------\n");
   for(j = 0;j < cnt;j++){
      printf("Weight of item%d is %d \n",j+1,elements[gd3_items[j]].weight);
      printf("Profit of item%d is %d \n",j+1,elements[gd3_items[j]].profit);
   }
   printf("\n");
}

// Solve the knapsack using maximum first greedy approach
void max_unit_ben(){
	int i,j;
	int cnt = 0;
  
   //Sort the struct of items based on benefit per unit item
	for (i = 0; i < elem_num-1; i++){
      for (j = i+1; j < elem_num; j++) {
         if (elements[j].unit_ben > elements[i].unit_ben) {
            KNAP temp = elements[j];
            elements[j] = elements[i];
            elements[i] = temp;
         }
      }
  }
  
  // Place the sorted struct into bag
   for(i = 0; i < elem_num; i++){
      if(gd4_max_weight + elements[i].weight <= capacity){
      	gd4_max_weight += elements[i].weight;
      		gd4_max_profit += elements[i].profit;
      		gd4_items[cnt++] = i;
      }
   }
   printf("\n------------GREEDY 4 MAXIMUM BENEFIT PER ITEM---------------\n");
   printf("\n-------------Total profit and weight--------------\n");
   printf("Total weight = %d\n", gd4_max_weight);
   printf("Total profit = %d\n", gd4_max_profit);

   printf("\n-------------Selected items' profit and weight--------------\n");
   for(j = 0;j < cnt;j++){
   	printf("Weight of item%d is %d \n",j+1,elements[gd4_items[j]].weight);
   	printf("Profit of item%d is %d \n",j+1,elements[gd4_items[j]].profit);
   }
   printf("\n");
}

int main()
{
	FILE * file = fopen("knapsack.txt","r");
	char buffer[100];
	int line_ind = 1;

   // Read the file using fgets
	while(fgets(buffer,100,file) != NULL)	{
		int length = strlen(buffer);
		if(buffer[length-1] == '\n'){
			buffer[length-1] = '\0';
		}
		if(line_ind == 1){
			elem_num = atoi(buffer);
		}
      else if(line_ind == 2){
			int cnt = 0;
			char * tok;
			tok = strtok(buffer,", ");
			while(tok != NULL){
				elements[cnt++].weight = atoi(tok);
				tok = strtok(NULL,", ");
			}
		}
		else if(line_ind == 3){
			int cnt = 0;
			char * tok;
			tok = strtok(buffer,", ");
			while(tok != NULL){
				elements[cnt++].profit = atoi(tok);
				tok = strtok(NULL,", ");
			}
		}else if(line_ind == 4){
			capacity = atoi(buffer);
		}

		line_ind++;

	}
	
	int ind = 0;
	for(ind = 0;ind < elem_num;ind++){
		elements[ind].unit_ben = elements[ind].profit/elements[ind].weight;
	}
	
   // Greedy 1
	max_benefit();
   // Greedy 2
	min_weight();
   // Greedy 3
	max_weight();
   // Greedy 4
	max_unit_ben();
	
  fclose(file);
  return 0;

}