#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int count = 1;

// Display the board
void display(int num,int mat[][num]){

	int i,j;
	for(i = 0;i < num;i++){
		for(j = 0;j < num;j++){
			printf("%5d ", mat[i][j]);
		}
		printf("\n");
	}
}

// Create a board with missing tile on specific index
void createBoard(int num,int mat[][num],int row,int col){

	int i,j;
	for(i = 0;i < num;i++){
		for(j = 0;j < num;j++){
			mat[i][j] = 0;
		}
	}
	mat[row][col] = -1;
}

// Function to solve the Tromino problem
void trominoTile(int size,int num,int mat[][size],int row,int col,int r_hole,int c_hole){

	// base case
	if(num == 2){
		int i,j;
		for(i = row;i < row + num; i++){
			for(j = col;j < col + num; j++){
				if(!(i == r_hole && j == c_hole)){
					mat[i][j] = count;
				}
			}
		}
		count++;
	}
	else{
		//recursive case
		int half_size = num/2;
		
		int x_hole,y_hole;
		int row_ind = 0,col_ind = 0;
		int new_count = count;
		count++;
		if(r_hole < row + half_size && c_hole < col + half_size){
			// up_left
			x_hole = r_hole;
			y_hole = c_hole;
			row_ind = row;
			col_ind = col;
			trominoTile(size,half_size,mat,row_ind,col_ind,x_hole,y_hole);
		}
		else{
			x_hole = row + half_size - 1;
			y_hole = col + half_size - 1;
			row_ind = row;
			col_ind = col;
			mat[x_hole][y_hole] = new_count; 
			trominoTile(size,half_size,mat,row_ind,col_ind,x_hole,y_hole);
		}
		if(r_hole < row + half_size && c_hole >= col + half_size){
			// up_right
			x_hole = r_hole;
			y_hole = c_hole;
			row_ind = row;
			col_ind = col + half_size;
			trominoTile(size,half_size,mat,row_ind,col_ind,x_hole,y_hole);
		}
		else{
			x_hole = row + half_size - 1;
			y_hole = col + half_size;
			row_ind = row;
			col_ind = col + half_size;
			mat[x_hole][y_hole] = new_count;
			trominoTile(size,half_size,mat,row_ind,col_ind,x_hole,y_hole);

		}
		 if(r_hole >= row + half_size && c_hole < col + half_size){
			// dwn_left
			x_hole = r_hole;
			y_hole = c_hole;
			row_ind = row + half_size;
			col_ind = col;

			trominoTile(size,half_size,mat,row_ind,col_ind,x_hole,y_hole);
		}
		else{
			x_hole = row + half_size;
			y_hole = col + half_size - 1;
			row_ind = row + half_size;
			col_ind = col;
			mat[x_hole][y_hole] = new_count;
			trominoTile(size,half_size,mat,row_ind,col_ind,x_hole,y_hole);
		}
		
		if(r_hole >= row + half_size && c_hole >= col + half_size){
			// dwn_right
			x_hole = r_hole;
			y_hole = c_hole;
			row_ind = row + half_size;
			col_ind = col + half_size;
			trominoTile(size,half_size,mat,row_ind,col_ind,x_hole,y_hole);
		}
		else{
			x_hole = row + half_size;
			y_hole = col + half_size;
			row_ind = row + half_size;
			col_ind = col + half_size;
			mat[x_hole][y_hole] = new_count;
			trominoTile(size,half_size,mat,row_ind,col_ind,x_hole,y_hole);
		}
	}
}

int main(int argc,char * argv[]){

	  int k_val = atoi(argv[1]);
	  int row_num = atoi(argv[2]);
	  int col_num = atoi(argv[3]);

	  int val = pow(2,k_val);
	  int board[val][val];
	  
	  createBoard(val,board,row_num,col_num);
	  
	  trominoTile(val,val,board,0,0,row_num,col_num);
	  display(val,board);
	  return 0;
}