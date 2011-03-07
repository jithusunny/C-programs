/*Filename: bitrep.c
Author: Jithu Sunny
Blog: http://jithusunnyk.blogspot.com/
Date: 07-03-11
Description: A simple code to print the bit representation of any integer*/

#include <stdio.h>
int main()
{
	int num, i;
	scanf("%d", &num);
	
	for(i = 31; i >= 0; i--)
		printf("%d", (num >> i) & 1);
	printf("\n");
}
	
