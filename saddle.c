/*Filename: saddle.c
Author: Jithu Sunny

This program finds out the saddle points of a 3X3 matrix
Saddle point in a row is that element if any, that is the smallest in it's row and largest in its column*/

#include <stdio.h>

/*Returns true if a is greater than b & c. False otherwise*/
int larger(int a, int b, int c)
{
	if((a >= b) && (a >= c))
		return 1;
	return 0;
}

/*Returns the address of the smallest number in the given row. p is always given the address of the first element in any row*/
int* smallest(int *p)
{
	if(*p <= *(p + 1))
		if(*p <= *(p + 2))
			return p;
		else return p + 2;
	else 
		if(*(p + 1) <= *(p + 2))
			return p + 1;
		else return p + 2;
}

/*Returns the element at the address in p if it is the largest in it's column. Otherwise returns 0.*/
int largest(int *p, int row_no)
{
	switch(row_no)
	{
		case 0:
			if(larger(*p, *(p + 3), *(p + 6)))
				return *p;
			return 0;

		case 1:
			if(larger(*p, *(p - 3), *(p + 3)))
				return *p;
			return 0;
	
		case 2:
			if(larger(*p, *(p - 3), *(p - 6)))
				return *p;
			return 0;
	}
}
	
int main()
{
	int i, j, a[3][3];
	int saddle[3];

	printf("Enter the 3x3 matrix: ");
	for(i = 0; i < 3; i++)
	for(j = 0; j < 3; j++)
		scanf("%d", &a[i][j]);
	
	for(i = 0; i < 3; i++)
		saddle[i] = largest(smallest(&a[i][0]), i);
	
	for(i = 0; i < 3; i++)
		if(saddle[i] == 0)
			printf("No saddle point in row %d.\n", i + 1);
		else
			printf("Saddle point in row %d is %d\n", i + 1, saddle[i]);

	return 1;
}
