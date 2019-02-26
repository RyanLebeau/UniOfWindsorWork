/*
Ryan Lebeau
04/10/2016
*/

#include <stdio.h>
int main(void)
{
	//initializing the integer and float variables
	int item_number, purchase_date_m, purchase_date_d, purchase_date_y;
	float unit_price;
	
	//getting the item number
	printf("Enter item number: ");
	scanf("%d", &item_number);
	//getting the unit price
	printf("Enter unit price: ");
	scanf("%f", &unit_price);
	//getting the purchase date
	printf("Enter purchase date (mm/dd/yyyy): ");
	scanf("%d/%d/%d", &purchase_date_m, &purchase_date_d, &purchase_date_y);
	
	//formatting and outputitng the required lines
	printf("\n");
	printf("Item\t\t\tUnit\t\t\tPurchase\n");
	printf("Number\t\t\tPrice\t\t\tDate\n");
	printf("-----\t\t\t------\t\t\t---------\n");
	printf("%i\t\t\t$%.2f\t\t\t%i/%i/%i", item_number, unit_price, purchase_date_m, purchase_date_d, purchase_date_y);
}