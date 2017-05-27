#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int max_profit = 0;
int items[10];
int max_num_weights = 0;
int max_weight = 0;

int main(){

	int elem_num;
	int capacity;
	int weights[10];
	int profits[10];
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
		// Read the weights
		else if(line_ind == 2){
			int cnt = 1;
			char * tok;
			tok = strtok(buffer,", ");
			while(tok != NULL){
				weights[cnt++] = atoi(tok);
				tok = strtok(NULL,", ");
			}
		}
		// Read the profits
		else if(line_ind == 3){
			int cnt = 1;
			char * tok;
			tok = strtok(buffer,", ");
			while(tok != NULL){
				profits[cnt++] = atoi(tok);
				tok = strtok(NULL,", ");
			}
		}
		else if(line_ind == 4){
			capacity = atoi(buffer);
		}
		line_ind++;
	}

	int i;
	int j;
	char elem[elem_num];

	for(i = 1; i <= elem_num ; i++){
		elem[i-1] = (char)i;
	}

	// Find 2^n subsets from the elements-count and save
	// every subset in variable perm.Use those indices to find 
	// maximum profit and maximum weight
	for(i = 0; i < pow(2,elem_num); i++)
    {
		char perm[elem_num];
		int ind = 0;
	    for(j = 0; j < elem_num; j++){
	      	if(i & (1<<j)){
	      		perm[ind++] = elem[j];
	      }
	   }
	   perm[ind] = '\0';

	   int len;
	   int weight_taken = 0;
	   int profit_taken = 0;
	   int weight_arr[strlen(perm)];

	   for(len = 0;len < strlen(perm); len++){
	   		int num = (int)perm[len];
	   		weight_taken += weights[num];
	   		profit_taken += profits[num];
	   		weight_arr[len] = num;
	   }

	   if(weight_taken <= capacity && profit_taken > max_profit){
	   		max_profit = profit_taken;
	   		max_weight = weight_taken;
	   		max_num_weights = sizeof(weight_arr)/sizeof(int);
	   		memcpy(items,weight_arr,sizeof(items));
	   }
    }
    printf("\n-------------1.a) Total profit and weight--------------\n");
    printf("Total weight = %d\n", max_weight);
    printf("Total profit = %d\n\n", max_profit);
    
    
    int w;
    printf("\n-------------1.b) Selected items' profit and weight--------------\n");
    for(w = 0;w < max_num_weights;w++){
    	printf("Weight of %d item == %d\n",items[w],weights[items[w]]);
    }
    printf("\n");
    for(w = 0;w < max_num_weights;w++){
    	printf("Profit of %d item == %d\n",items[w],profits[items[w]]);
    }
    printf("\n");
    fclose(file);
}
