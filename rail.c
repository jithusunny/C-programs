/*Filename: rail.c
Author: Jithu Sunny
College: Govt. Engg College, Thrissur
Branch: CSE
Year: 3rd year
C compiler - GCC 4.4.3
Platform - GNU/Linux - Ubuntu 10.04

Email: jithusunnyk@gmail.com
Blog: http://jithusunnyk.blogspot.com/
Phone: 9567 175 660*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*In future when the ticket charges hike OR the train gets more seats, just edit the following macros. Can also specify the name of the file in which the data is to be stored.*/
#define SEATS 50
#define RATE 100
#define FILENAME "chart" 

/*Stores Passenger data*/
struct passenger {
	char name[100], sex;
	int age, seat, booking_no;
};

/*Calculates the train fare for a passenger considering the various discount schemes*/
float fare(struct passenger *pass)
{
	float discount;
	
	if(pass -> sex == 'f' && pass -> age > 60)
		discount = RATE * 0.06;
	else if(pass -> age > 60)
	    discount = RATE * 0.05;
	else if(pass -> sex == 'f')
	    discount = RATE * 0.01;
	else discount = 0;
	
	return RATE - discount;
}

/*Copies the fields of structure '*b' into those of structure '*a'*/
void copy_struct(struct passenger *a, struct passenger *b)
{
	a -> age = b -> age;
	a -> seat = b -> seat;
	a -> sex = b -> sex;
	a -> booking_no = b -> booking_no;
	strcpy(a -> name, b -> name);
	
	return;
}

/*Copies the array 'a' into array 'b'*/
void copy_array(int a[], int b[])
{
	int i;
		
	for(i = 0; i < SEATS; i++)
		a[i] = b[i];
		
	return;
}

/*a[i] is 1 if either a[i] or b[i] is 1. This function is used to insert the bookings saved in temporary array into original array, when a user confirms transaction*/
void or_array(int a[], int b[])
{
	int i;
	
	for(i = 0; i < SEATS; i++)
		a[i] |= b[i];
	return;
}

/*Reads & stores the various info of a passenger, '*pass'. Also uses 'booked_seats' array to know which all seats are already booked.*/
void read_dat(struct passenger *pass, int booked_seats[])
{
	int seat, i, okay = 0;
	
	printf("\nName: ");
	scanf("%s", pass -> name);
	printf("Age: ");
	scanf("%d", &(pass -> age));
	getchar();
	printf("Sex(m/f): ");
	scanf("%c", &(pass -> sex));
	
    /*Segment to handle booking of seats*/
	while (!okay)
	{
		printf("Available seats are: ");
		for(i = 0; i < SEATS; i++)
			if(!booked_seats[i])
				printf("   %d", i + 1);
			
	    printf("\nSeat number: ");
		scanf("%d", &seat);
		
		if(seat > SEATS)
			printf("Sorry, invalid selection!\n");
		else if(booked_seats[seat - 1])
			printf("Sorry, that seat has already been booked, please select another seat!\n\n");
		else if (!booked_seats[seat - 1])
		{
			pass -> seat = seat;
			booked_seats[seat - 1] = 1;
			okay = 1;
		}
		else
			printf("Sorry, invalid selection!\n");
	} 
	/*The booking number is a key that will be required later if he want to cancel the ticket. This adds more security. Otherwise anybody can cancel any ticket.*/ 
	pass -> booking_no = time(NULL) % 1000;
		printf("Your booking number: %d.\n", pass -> booking_no);
    return;
}

/*Prints the details of the passenger onto screen(except booking_no which is somewhat secret!)*/
void display_details(struct passenger *pass)
{
	printf("Seat no. %d - %s\t%d\t%c\n", pass -> seat, pass -> name, pass -> age, pass -> sex);
	return;
}

/*Returns the total number of booked seats. In the meanwhile, it also updates the passenger structure array & booked_seats array, referring to the 'FILENAME' file.*/
int update_data(struct passenger *pass[], int booked_seats[])
{
	FILE *fp;
    int seat, age, booking_no, count = 0;
    char sex, name[100];

    fp = fopen(FILENAME, "r");

	if(fp != NULL)
		while(fscanf(fp, "%d %s %d %c %d\n", &seat, name, &age, &sex, &booking_no) != EOF)
    	{
			pass[seat - 1] = malloc(sizeof(struct passenger));
    	    pass[seat - 1] -> seat = seat;
    	    strcpy(pass[seat - 1] -> name, name);
    	    pass[seat - 1] -> age = age;
    	    pass[seat - 1] -> sex = sex;
    	    pass[seat - 1] -> booking_no = booking_no;
    	    booked_seats[seat - 1] = 1;
	
    	    count++;
		}
    return count;
}

/*Updates the file used ot store the reservation details when program is not running*/
void update_file(struct passenger *pass[], int booked_seats[])
{
	int i;
	FILE *fp;
	
	fp = fopen(FILENAME, "w");/*Creates a new file if doesn't exist*/
	if(fp != NULL)
	{
		for(i = 0; i < SEATS; i++)
			if (booked_seats[i])
				fprintf(fp, "%d %s %d %c %d\n", pass[i] -> seat, pass[i] -> name, pass[i] -> age, pass[i] -> sex, pass[i] -> booking_no);
		fclose(fp);
	}
	return;
}


/*The Main Function*/
int main()
{
	int i, seat, temp, choice = 0, subchoice = 0, avail_seats = SEATS, booked_seats[SEATS], dup_booked[SEATS], num;
	float tot_fare = 0; 
	
	struct passenger *temp_pass[SEATS], *pass[SEATS];
    
    for(i = 0; i < SEATS; i++)
    	booked_seats[i] = 0;
    /*Calculates available seats. More importantly knows the current reservation details by looking in the file 'FILENAME'. See function def more more.*/
    avail_seats = SEATS - update_data(pass, booked_seats);
    
	while(choice != 4)
	{
		printf("\nRailway Reservation System\n--------------------------\n");
		printf("Total seats left for reservation: %d\n\n", avail_seats);
		printf("1.Book\n2.Cancel\n3.View Reservations\n4.Exit\nEnter your choice: ");
		scanf("%d", &choice);
		
		/*'tot_fare' stores the amount to be paid by user*/
		tot_fare = 0;
		/*'dub_booked' is used to store the bookings of a user.*/
		copy_array(dup_booked, booked_seats);
		
		switch (choice)
		{
		case 1:
			{
				printf("Enter the number of passengers: ");
				scanf("%d", &num);
			    /*Error if user requests more seats than available*/
				if (num > avail_seats)
					printf("Sorry, only %d seats are available!!\n\n", avail_seats);
				/*Otherwise*/	
				else
				{
					for(i = 0; i < num; i++)
					{
						temp_pass[i] = malloc(sizeof(struct passenger));
						
						printf("\nPlease enter the details of passenger number %d: ", i + 1);
					    read_dat(temp_pass[i], dup_booked);
					    
	        	        tot_fare += fare(temp_pass[i]);
	        	    }
	        	    
	        	    printf("The total amount to be paid: %.2f only.\nYou can confirm or cancel this transaction now. Confirm(0/1)? :", tot_fare);
	        	    scanf("%d", &subchoice);
	        	    
	        	    /*User confirmed the transaction, so update the data structures to include the change.*/
	        	    if(subchoice == 1)
	        	    {
	        	        avail_seats -= num;
	        	        or_array(booked_seats, dup_booked);
	        	    	printf("\nResevation has been made as follows:\n");
	        	    	
	        	    	for(i = 0; i < num; i++)
					    {
					    	display_details(temp_pass[i]);
					    	seat = temp_pass[i] -> seat;
					    	pass[seat - 1] = malloc(sizeof(struct passenger));
					    	copy_struct(pass[seat - 1], temp_pass[i]); /*Stores the passenger details from temporary structure to original structure, since user confirmed transaction.*/
					    }
					}				    	
				}
				break;
			}
			
		case 2:
			{
			printf("Enter the reserved seat number to be cancelled: ");
			scanf("%d", &num);
			
			if(booked_seats[num - 1])
			{
				printf("Please enter the booking number to confirm user: ");
				scanf("%d", &temp);
				if(temp == pass[num - 1] -> booking_no) 
				{   
					booked_seats[num - 1] = 0;
					avail_seats++;
					printf("\nCancelled successfully!\n");
				}
				else
					printf("\nSorry, wrong booking number. Can't cancel..!!\n");
			}
			else
				printf("\nSorry, the seat is not reserved!!\n");
					
			break;
			}
			
		case 3:
			{
				if(avail_seats < SEATS)
				{
			    	printf("\nReservation Chart\n-----------------\n");
					for(i = 0; i < SEATS; i++)
						if(booked_seats[i])
							display_details(pass[i]);
				}
				else
					printf("\nNobody has reserved tickets yet.\n");
					
				break;
			}
		
		case 4:
			{
				printf("Thank you for using the Railway Reservation System. Bye.\n");
				break;
			}
			
		}
	}
	
	update_file(pass, booked_seats);
	return 0;
}
