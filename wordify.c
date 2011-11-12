/*Filename: wordify.c
Author: Jithu Sunny
Blog: http://jithusunnyk.blogspot.com/
Date: 12-11-11
Description: Prints numbers below 1 Crore(10 million) in words*/

#include <stdio.h>

void ones(int number) {
		
	switch (number) {

		case 0: printf("zero");	
			return;
		case 1: printf("one");
			return;
		case 2: printf("two");
			return;
		case 3: printf("three");
			return;
		case 4: printf("four");
			return;
		case 5: printf("five");
			return;
		case 6: printf("six");
			return;
		case 7: printf("seven");
			return;
		case 8: printf("eight");
			return;
		case 9: printf("nine");
			return;
	}
}

void tens(int number) {
	
	if (number < 10) {
		ones(number);
		return;
	}

	if (number <= 20)
		switch (number) {

			case 10: printf("ten");
				 return;
			case 11: printf("eleven");
				 return;
			case 12: printf("twelve");
				 return;
			case 13: printf("thirteen");
				 return;
			case 14: printf("fourteen");
				 return;
			case 15: printf("fifteen");
				 return;
			case 16: printf("sixteen");
				 return;
			case 17: printf("seventeen");
				 return;
			case 18: printf("eighteen");
				 return;
			case 19: printf("nineteen");
				 return;
			case 20: printf("twenty");
				 return;
		}
		
	if (number % 10 == 0)
		switch (number) {

			case 30: printf("thirty");
				 return;
			case 40: printf("forty");
				 return;
			case 50: printf("fifty");
				 return;
			case 60: printf("sixty");
				 return;
			case 70: printf("seventy");
				 return;
			case 80: printf("eighty");
				 return;
			case 90: printf("ninety");
				 return;
		}
		
	tens(number - number % 10);
	printf(" ");
	ones(number % 10);
	
	return;
}

void hundreds(int number) {

	if (number < 100) {
		tens(number);
		return;
	}
		
	if (number % 100 == 0) {
		
		ones(number / 100);
		printf(" hundred");
		return; 
	}

	hundreds(number - number % 100);
	printf(" and ");
	tens(number % 100);
	
	return;
}

void thousands(int number) {
	
	if (number < 1000) {
		hundreds(number);
		return;
	}
	
	if (number % 1000 == 0) {
		ones(number / 1000);
		printf(" thousand");
		return;
	}

	thousands(number - number % 1000);
	printf(" ");
	hundreds(number % 1000);	

	return;
}

void tenthousands(int number) {

	if (number < 10000) {
		thousands(number);
		return;
	}
	
	if (number % 1000 == 0) {
		
		tens(number / 1000);
		printf(" thousand");
		return; 
	}

	tenthousands(number - number % 1000);
	printf(" ");
	hundreds(number % 1000);
	
	return;
}

void lakhs(int number) {

	if (number < 100000) {
		tenthousands(number);
		return;
	}
	
	if (number % 100000 == 0) {
		
		ones(number / 100000);
		printf(" lakh");
		return; 
	}

	lakhs(number - number % 100000);
	printf(" ");
	tenthousands(number % 100000);
	
	return;
}

void tenlakhs(int number) {

	if (number < 1000000) {
		lakhs(number);
		return;
	}
	
	if (number % 100000 == 0) {
		
		tens(number / 100000);
		printf(" lakh");
		return; 
	}

	tenlakhs(number - number % 100000);
	printf(" ");
	tenthousands(number % 100000);
	
	return;
}

void wordify(int number) {

	if (number < 10)
		ones(number);

	else if (number < 100)
		tens(number);

	else if (number < 1000)
		hundreds(number);

	else if (number < 10000)
		thousands(number);
		
	else if (number < 100000)
		tenthousands(number);
		
	else if (number < 1000000)
		lakhs(number);
		
	else if (number < 10000000)
		tenlakhs(number);
	else
		printf("Sorry, number not below 1,00,00,000\n");
	
	return;
}
	
int main() {

	int number;
 	char *str;
	
	printf("Enter: ");
	scanf("%d", &number);

	wordify(number);

	printf("\n");
		
	return 0;
}

