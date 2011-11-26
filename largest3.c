/*Author: Jithu Sunny
Date: 26-11-11
Blog: http://jithusunnyk.blogspot.com/
Description: Finds out the consecutive 3 numbers in a list with greatest sum.*/

#include <stdio.h>

#define SIZE 100

int main() {

	int set[SIZE] = {2, 4, 6, 4, 7, 9, 4, 1, 8, 2, 7, 1, 7, 0, 8, 8, 9, 0, 6, 5, 3, 7, 9, 1, 3, 4, 5, 6, 8, 0};

	int i, sum = 0, max_sum = 0, max_index = 0;

	for (i = 0; i < SIZE - 2; i++) {
	
		sum = set[i] + set[i + 1] + set[i + 2];
	
		if (sum > max_sum) {
			max_sum = sum;
			max_index = i;
		}
	}

	i = max_index;

	printf("The 3 consecutive numbers with maximum sum: %d, %d, %d\n", set[i], set[i + 1], set[i + 2]);

	return 0;
}
			
