#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int main()
{
	int elem_num;
	int capacity;
	int max_weight = 0;
	int max_profit;
	int sel_weights[10];
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
		}else if(line_ind == 2){
			int cnt = 1;
			char * tok;
			tok = strtok(buffer,", ");
			while(tok != NULL){
				weights[cnt++] = atoi(tok);
				tok = strtok(NULL,", ");
			}
		}
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

	int matrix[elem_num+1][capacity+1];
	int keep[elem_num+1][capacity+1];
	
	int i,j;
	int k,w;
	int cnt = 0;
	for(w = 0;w <= capacity;w++){
		matrix[0][w] = 0;
	}
	
	//  Loop through every row that repeates for the number of elements
	for(k = 1;k <= elem_num; k++){
		matrix[k][0] = 0;
		// Loop through till the capacity of the bag is reached
		for(w = 0;w <= capacity; w++){
			
			if(weights[k] <= w && (matrix[k-1][w-weights[k]] + profits[k] > matrix[k-1][w])){
				matrix[k][w] = matrix[k-1][w-weights[k]] + profits[k];
				keep[k][w] = 1;
				max_profit = matrix[k][w];
				
			}
			else{
				matrix[k][w] = matrix[k-1][w];
				keep[k][w] = 0;
			}
		}
	}
	int K = capacity;
	
	for(i = elem_num;i >= 1;i--){
		if(keep[i][K] == 1){
			sel_weights[cnt++] = i;
			max_weight += weights[i];
			K = K - weights[i];
		}
	}
	
	printf("\n-------------Total profit and weight--------------\n");
	printf("Total weight = %d\n", max_weight);
	printf("Total profit = %d\n", max_profit); 

	printf("\n-------------Selected items' profit and weight--------------\n");
   for(j = 0;j < cnt;j++){
   	printf("Weight of item%d is %d \n",j,weights[sel_weights[j]]);
	printf("Profit of item%d is %d \n",j,profits[sel_weights[j]]);
   }
   printf("\n");
   fclose(file);
	
}