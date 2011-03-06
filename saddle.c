/*Filename: Saddle.c
Author: Jithu Sunny
Blog: http://jithusunnyk.blogspot.com/
Date: 06-03-11
Description: This program finds out the saddle points and their positions in a matrix of any order.*/

/*Change these macros to change the order*/
#define ROWS 3
#define COLUMNS 3

#include <stdio.h>

struct saddle
{
	int num;
	int row, column;
};

/*Returns 1 if element at p is the smallest in its row. Returns 0 otherwise*/
int is_min_in_row(int* p, int col)
{
	int *i;
	int *first_in_row = p - col;
    int *last_in_row = first_in_row + COLUMNS - 1;

	for(i = first_in_row; i <= last_in_row; i++)
		if(*p <= *i)
			continue;
		else
			return 0;
	return 1;
}

/*Returns 1 if element at p is the largest in its column. Returns 0 otherwise*/
int is_max_in_col(int* p, int row)
{
	int *i;
	int *first_in_col = p - (COLUMNS * row);
	int *last_in_col = first_in_col + COLUMNS * (ROWS - 1);

   	for(i = first_in_col; i <= last_in_col; i += COLUMNS)
		 if(*p >= *i)
			continue;	
		else
			return 0;
	return 1;
}

/*Returns 1 if element at p is a saddle point. Returns 0 otherwise*/			
int is_saddle(int* p, int row, int col)
{
	if((is_min_in_row(p, col)) && (is_max_in_col(p, row)))
		return 1;
	return 0;
}

int main()
{
	int i, j, k = 0;	
	int a[ROWS][COLUMNS];

	struct saddle saddles[1000];

	printf("Enter the %dx%d matrix:", ROWS, COLUMNS);	
	for(i = 0; i < ROWS; i++)
		for(j = 0; j < COLUMNS; j++)
			scanf("%d", &a[i][j]);

	for(i = 0; i < ROWS; i++)
	for(j = 0; j < COLUMNS; j++)
		if(is_saddle(&a[i][j], i, j))
		{
			saddles[k].num = a[i][j];
			saddles[k].row = i;
			saddles[k].column = j;
			++k;
		}

	for(i = 0; i < k; i++)  
			printf("Saddle point: %d at position %d,%d\n", saddles[i].num, saddles[i].row, saddles[i].column);
	return 1;
}
