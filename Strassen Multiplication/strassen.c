#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int n_val;
int n_val_init = 0;

// Display the elements of matrix 
void display(int size,float mat[][size]){

	int i,j;
	if(n_val_init != 0 ){
		size = n_val_init;
	}
	for(i = 0; i < size ; i++){
		for(j = 0;j < size ;j++){
			printf("%8.2f", mat[i][j]);
		}
		printf("\n");
	}
}

// Set the indices of the metrix to 0
void initialize(int count,float init[][count]){
	int i,j;
	for(i = 0;i < count;i++){
		for(j = 0;j < count;j++){
			init[i][j] = 0;
		}
	}
}

// Split a source matrix into 4 matrices
void split_Mat(int val,float src_mat[][val],float S1_mat[][val/2],float S2_mat[][val/2],float S3_mat[][val/2],float S4_mat[][val/2]){
	
	int i,j;
	initialize(val/2,S1_mat);
	initialize(val/2,S2_mat);
	initialize(val/2,S3_mat);
	initialize(val/2,S4_mat);

	for(i = 0; i < val; i++){
		for(j = 0; j < val ; j++){
			if( (i >= 0 && i < val/2 && j >= 0 && j < val/2)){
				S1_mat[i][j] = src_mat[i][j];
			}
			else if((i >= 0 && i < val/2) && (j >= val/2 && j<val)){
				S2_mat[i][j-(val/2)] = src_mat[i][j];
			}
			else if((i >= val/2 && i<val) && (j >= 0 && j < val/2)){
				S3_mat[i-(val/2)][j] = src_mat[i][j];
			}
			else{
				S4_mat[i-(val/2)][j-(val/2)] = src_mat[i][j];
			}
		}
	}
}

// Subtract two matrices
void subtract_mat(int sub_size,float mat1[][sub_size],float mat2[][sub_size],float sub[][sub_size]){

	int i,j;
	for(i = 0;i < sub_size;i++){
		for(j = 0;j < sub_size;j++){
			sub[i][j] = mat1[i][j] - mat2[i][j];
		}
	}
}

// Add two matrices
void add_mat(int add_size,float mat1[][add_size],float mat2[][add_size],float add[][add_size]){

	int i,j;
	for(i = 0;i < add_size;i++){
		for(j = 0;j < add_size;j++){
			add[i][j] = mat1[i][j] + mat2[i][j];
		}
	}
}

// Apply Strassen algorithm to determine the result matrix
void strassen(int num,float A_mat[][num],float B_mat[][num],float mul_mat1[][num]){

	if(num==1){
		mul_mat1[0][0] = A_mat[0][0] * B_mat[0][0];
		return;
	}
	if(num == 2){

		float p1 = A_mat[0][0] * (B_mat[0][1] - B_mat[1][1]);
		float p2 = B_mat[1][1] * (A_mat[0][0] + A_mat[0][1]);
		float p3 = B_mat[0][0] * (A_mat[1][0] + A_mat[1][1]);
		float p4 = A_mat[1][1] * (B_mat[1][0] - B_mat[0][0]);
		float p5 = (A_mat[0][0] + A_mat[1][1]) * (B_mat[0][0] + B_mat[1][1]);
		float p6 = (A_mat[0][1] - A_mat[1][1]) * (B_mat[1][0] + B_mat[1][1]);
		float p7 = (A_mat[0][0] - A_mat[1][0]) * (B_mat[0][0] + B_mat[0][1]);

		mul_mat1[0][0] = p4 + p5 - p2 + p6;
		mul_mat1[0][1] = p1 + p2;
		mul_mat1[1][0] = p3 + p4;
		mul_mat1[1][1] = p5 + p1 - p3 - p7;

		return;
	}

	float p1[num/2][num/2],p2[num/2][num/2],p3[num/2][num/2],p4[num/2][num/2];
	float p5[num/2][num/2],p6[num/2][num/2],p7[num/2][num/2];

	float A1_mat[num/2][num/2],A2_mat[num/2][num/2],A3_mat[num/2][num/2],A4_mat[num/2][num/2];
	float B1_mat[num/2][num/2],B2_mat[num/2][num/2],B3_mat[num/2][num/2],B4_mat[num/2][num/2];
	
	float merg1[num/2][num/2],merg2[num/2][num/2],merg3[num/2][num/2],merg4[num/2][num/2];

	split_Mat(num,A_mat,A1_mat,A2_mat,A3_mat,A4_mat);
	split_Mat(num,B_mat,B1_mat,B2_mat,B3_mat,B4_mat);

	initialize(num/2,p1);
	initialize(num/2,p2);
	initialize(num/2,p3);
	initialize(num/2,p4);
	initialize(num/2,p5);
	initialize(num/2,p6);
	initialize(num/2,p7);
	
	float temp[num/2][num/2];
	initialize(num/2,temp);

	//p1
	subtract_mat(num/2,B2_mat,B4_mat,temp);	
	strassen(num/2,A1_mat,temp,p1);

	initialize(num/2,temp);
	//p2
	add_mat(num/2,A1_mat,A2_mat,temp);
	strassen(num/2,temp,B4_mat,p2);

	initialize(num/2,temp);
	//p3
	add_mat(num/2,A3_mat,A4_mat,temp);
	strassen(num/2,temp, B1_mat,p3);

	initialize(num/2,temp);
	//p4
	subtract_mat(num/2,B3_mat,B1_mat,temp);
	strassen(num/2,A4_mat,temp,p4);

	initialize(num/2,temp);
	float temp1[num/2][num/2];
	initialize(num/2,temp1);
	//p5
	add_mat(num/2,B1_mat,B4_mat,temp);
	add_mat(num/2,A1_mat,A4_mat,temp1);
	strassen(num/2,temp1, temp, p5);

	initialize(num/2,temp);
	initialize(num/2,temp1);
	//p6
	add_mat(num/2,B3_mat,B4_mat,temp);
	subtract_mat(num/2,A2_mat,A4_mat,temp1);
	strassen(num/2,temp1,temp,p6);


	initialize(num/2,temp);
	initialize(num/2,temp1);
	//p7
	add_mat(num/2,B1_mat,B2_mat,temp);
	subtract_mat(num/2,A1_mat,A3_mat,temp1);
	strassen(num/2,temp1,temp,p7);

	// 0,0
	initialize(num/2,merg1);
	initialize(num/2,temp);
	initialize(num/2,temp1);
	add_mat(num/2,p4,p5,temp);
	add_mat(num/2,temp,p6,temp1);
	subtract_mat(num/2,temp1,p2,merg1);

	//0,1
	initialize(num/2,merg2);
	add_mat(num/2,p1,p2,merg2);
	
	//1,0
	initialize(num/2,merg3);
	add_mat(num/2,p3,p4,merg3);

	//1,1
	initialize(num/2,merg4);
	initialize(num/2,temp);
	initialize(num/2,temp1);
	add_mat(num/2,p5,p1,temp);
	add_mat(num/2,p3,p7,temp1);
	subtract_mat(num/2,temp,temp1,merg4);

	int i,j;
	for(i = 0;i<num;i++){
		for(j=0;j<num;j++){
			if( (i >= 0 && i < num/2 && j >= 0 && j < num/2)){
				mul_mat1[i][j] = merg1[i][j];
			}
			else if((i >= 0 && i < num/2) && (j >= num/2 && j<num)){
				mul_mat1[i][j] = merg2[i][j-(num/2)];
			}
			else if((i >= num/2 && i<num) && (j >= 0 && j < num/2)){
				mul_mat1[i][j] = merg3[i-(num/2)][j];
			}
			else{
				mul_mat1[i][j] = merg4[i-(num/2)][j-(num/2)];
			}
		}
	}
}

// Accept two matrices as input and find the product of them strassen multiplication
void strassensMultiplication(float A_mat[][n_val],float B_mat[][n_val],float mul_mat1[][n_val]){

	initialize(n_val,mul_mat1);	
	strassen(n_val,A_mat,B_mat,mul_mat1);

	printf("\nStrassen multiplication Output:\n");
	display(n_val,mul_mat1);
	printf("\n");
}

// Accept two matrices as input and find the product of them using standard multiplication
void standardMultiplication(float A_mat[][n_val],float B_mat[][n_val],float mul_mat[][n_val]){

	initialize(n_val,mul_mat);
	
	int i,j,k;
	for(i = 0; i < n_val; i++){
		for(j = 0; j < n_val; j++){
			for(k = 0; k < n_val; k++){
				mul_mat[i][j] += A_mat[i][k] * B_mat[k][j];
			}
		}
	}
	printf("\nStandard multiplication Output:\n");
	display(n_val,mul_mat);
}

// Create matrix A
void generate_A(float A_mat[][n_val]){

	int i,j;
	float rand_val = 5.0;
	float start = -5;
	srand(time(NULL));
	for(i = 0;i < n_val ; i++){
		for(j = 0;j < n_val;j++){

			A_mat[i][j] = ((float)rand()/(float)RAND_MAX) * (rand_val - start) + start;

			if(n_val_init != 0 && (i >= n_val_init || j >= n_val_init)){
				A_mat[i][j] = 0;
			}
		}
	}
	
}

// Create matrix B
void generate_B(float B_mat[][n_val]){
	int i,j;
	float rand_val = 5.0;
	float start = -5;
	for(i = 0;i < n_val; i++){
		for(j = 0;j < n_val; j++){

			B_mat[i][j] = ((float)rand()/(float)RAND_MAX) * (rand_val - start) + start;

			if(n_val_init != 0 && (i >= n_val_init || j >= n_val_init)){
				B_mat[i][j] = 0;
			}
		}
	}
	
}

// Checks if a number is a power of 2
int isPower(int num){
	if(num  && !(num & (num-1))){
		return 0;
	}
	return 1;
}

//Finds the next closest power of 2
int nextPower(int num){
	double newNum = ceil( log(num)/log(2) );
	int finNum = (int) pow(2 , newNum);
	return finNum;
}

int main(int argc,char * argv[]){

	if(argc != 2){
		printf("Enter matrix size\n");
		return -1;
	}
	n_val = atoi(argv[1]);
	int is_Power = isPower(n_val);
	if(is_Power == 1){
		//find next power of 2
		n_val_init = n_val;
		n_val = nextPower(n_val_init);
	}
	float A_mat[n_val][n_val];
	float B_mat[n_val][n_val];
	float mul_mat[n_val][n_val];
	float mul_mat1[n_val][n_val];
	
	generate_A(A_mat);
	printf("Matrix A:\n");
	display(n_val,A_mat);
	generate_B(B_mat);
	printf("\nMatrix B:\n");
	display(n_val,B_mat);
	
	strassensMultiplication(A_mat,B_mat,mul_mat1);
	standardMultiplication(A_mat,B_mat,mul_mat);
	
	
	return 0;
}