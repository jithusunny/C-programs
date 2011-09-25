/*Filename: pascal.c
Author: Jithu Sunny
Blog: http://jithusunnyk.blogspot.com/
Date: 24-09-11
Description: /*Finds out the number at any given location(row, position) of Pascal triangle.
               Numbering starts from 1. ie, number of first row is 1. (not 0)*/

#include <stdio.h>

int element_at(int row,int pos) {
	if (pos == 1 || pos == row)
		return 1;

	return element_at(row - 1, pos - 1) + element_at(row - 1, pos);
}

int main() {
        int row, pos;
       
	printf("Enter row and position: ");
	scanf("%d%d", &row, &pos);
	
	if (pos > row)
		printf("Invalid!\n");
	else
		printf("Number: %d\n", element_at(row, pos));
	
	return 0;
}
