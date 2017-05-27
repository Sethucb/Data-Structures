#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MATRIX_SIZE 10

int cost[MATRIX_SIZE][MATRIX_SIZE];
int vert_cnt = 0;
void dijkstra(int);

void dijkstra(int start){
	
	// Enter the shortest distance to that node in distance array where index is the node number
	// Visited tells if the node is visited or not
	// The previous node is tracked using prev which helps find the shortest path
	int distance[vert_cnt],visited[vert_cnt],prev[vert_cnt];
	int min,next;
	int i,j;
	for(i = 0 ;i < vert_cnt;i++){
		visited[i] = 0;
		distance[i] = cost[start][i];
		prev[i] = start;
	}
	distance[start] = 0;
	visited[start] = 1;

	int cnt;
	for(cnt = 0;cnt < vert_cnt; cnt++){
		min = 100;
		for(i = 0;i < vert_cnt; i++){
			// min = 100;
			if(distance[i] < min && visited[i] == 0){
				min = distance[i];
				next = i;
			}
		}
		visited[next] = 1;
		for(i = 0;i < vert_cnt; i++){
			if(visited[i] == 0){
				if(min + cost[next][i] < distance[i]){
					distance[i] = min + cost[next][i];
					prev[i] = next;
				}
			}
		}
		
	}

	for(i = 0;i < vert_cnt;i++)
        if(i != start)
        {	
        	if(distance[i] >= 1000){
        		printf("\nDistance of node %d = Infinity",i);
        	}
        	else{
            printf("\nDistance of node %d = %d",i,distance[i]);
            printf("\nPath = %d",i);
            
            j = i;
            
            while(j != start){
                j = prev[j];
                printf("<=%d",j);
            }
        }
    }
	    else{
	    	printf("\nDistance of node %d = %d",i,distance[i]);
	    }
	    printf("\n");
}

int main(){
	FILE * file = fopen("matrix_input.txt","r");
	int row_cnt = 0;
	int col_cnt = 0;
	
	char buffer[100];
	
	int i=0,j=0;
	for(i = 0;i < MATRIX_SIZE;i++)
		for(j = 0;j < MATRIX_SIZE;j++)
			cost[i][j] = 0;
		
	i=0;j=0;
	while(fgets(buffer,100,file) != NULL){
		j=0;
		int length = strlen(buffer);
		if(buffer[length-1] == '\n'){
			buffer[length-1] = '\0';
		}
		char * tok;
		tok = strtok(buffer,",");
		while(tok != NULL){
			cost[i][j++] = atoi(tok);
			tok = strtok(NULL,",");
		}
		i++;
	}
	row_cnt = col_cnt = vert_cnt = i;
	
	for(i = 0;i < row_cnt;i++){
		for(j = 0;j < col_cnt;j++){
			if(cost[i][j] < 0){
				cost[i][j] = 1000;
			}
		}
	}

	// Pass the first row as the start node which is s-node
	// dijkstra(vert_cnt-1);
	 dijkstra(0);
	fclose(file);
	return 0;
}