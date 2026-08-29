#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Product
{
	char name[30];
	int id;
	int price;
	int quantity;
};

void init_product(Product* product, char _name[30], int id, int price, int quantity)
{	
	if (id <= 0) { id = 0; }
	if (price <= 0) { price = 0; }
	if (quantity <= 0) { quantity = 0; }

	product->id = id;
	product->price = price;
	product->quantity = quantity;
	strncpy(product->name, _name, 29);
}

int main()
{
	int cont = 1;
	int option = 0;
	int ilosc_prod = 0;

	Product* list = NULL;
	Product* buffor = NULL;

	list = (Product*)malloc(sizeof(Product));

	if (list == NULL)
	{
		printf("Couldn't allocate memory for list");
		return 1;
	}

	while (cont == 1)
	{
		system("cls");
		printf("1. Add Product\t 2. Remove Product\t 3. Update product\n4. Search by name\t 5. List products\t 6. Total value of products\n");

		scanf("%d", &option);
		while ((getchar()) != '\n');

		system("cls");

		if (option < 0 || option > 6)
		{
			cont = 0;
		}
		if (option == 1) /* Dodaje produkt do listy*/
		{
			int price = 0;
			int quantity = 0;
			char _name[30] = { 0 };

			printf("Name: \t");
			scanf("%29[^\n]", &_name);

			printf("\nPrice: \t");
			scanf("%d", &price);

			printf("\nQuantity: \t");
			scanf("%d", &quantity);

			buffor = (Product*)malloc(sizeof(Product) * (ilosc_prod + 1));
			if (buffor == NULL)
			{
				printf("Couldn't allocate memory for buffor");
				return 1;
			}
			memcpy(buffor, list, (sizeof(Product) * ilosc_prod));

			Product* product = &buffor[ilosc_prod];

			init_product(product, _name, (ilosc_prod + 1), price, quantity);

			free(list);
			list = buffor;
			buffor = NULL;

			ilosc_prod++;
			option = 0;
		}
		if (option == 2) /* Removes product */
		{
			int temp = 1;
			if (list[0].id == 1)
			{
				printf("Enter product ID to delete\n ID:\t");

				int removeID = 0;
				scanf("%d", &removeID);

				buffor = (Product*)malloc(sizeof(Product)* (ilosc_prod - 1));

				if (removeID > 0 || removeID < ilosc_prod)
				{
					// Wyjebuje bo wychodze poza blok zalokowanej pamieci
					// Przekopiowac wszystko do buffora co nie ma removeID i powtorzyc fit z free

					for (int k = 0; k < ilosc_prod; k++) // Kopiowanie
					{
						if (list[k].id != removeID)
						{
							if (k < ilosc_prod - 1 && removeID != 1)
							{
								buffor[k] = list[k];
								buffor[k].id = k + 1;
							}
							else
							{
								buffor[k - 1] = list[k];
								buffor[k - 1].id = k;
							}
						}
					}
					free(list);
					list = buffor;
					buffor = NULL;

					ilosc_prod--;
					option = 0;
				}
				else
				{
					printf("No products with this ID\n");
					printf("0. Exit \t1. Return\n");
					scanf("%d", &temp);
					if (temp != 1) { system("cls"); printf("you stupid"); break; }
					option = 0;
				}
			}
			else
			{
				printf("No products to remove\n");
				printf("0. Exit \t1. Return\n");
				scanf("%d", &temp);
				if (temp != 1) { system("cls"); printf("you stupid"); break; }
				option = 0;
			}
		}
		if (option == 3) /* Update product */
		{
			int updateID = 0;
			int updateOption = 0;

			int updatePrice = 0;
			int updateQuantity = 0;
			char updateName[30] = { 0 };

			printf("Enter product ID to modify:\t");
			scanf("%d", &updateID);

			if (updateID > 0 && updateID <= ilosc_prod)
			{
				printf("1. Change name\t2. Change price\t3. Change quantity\n");
				scanf("%d", &updateOption);

				while ((getchar()) != '\n');
				if (updateOption == 1)
				{
					printf("\nEnter update name:\t");
					scanf("%29[^\n]", &updateName);
					
					strncpy(list[updateID - 1].name, updateName, 29);
				}
				if (updateOption == 2)
				{
					printf("\nEnter update price:\t");
					scanf("%d", &updatePrice);

					list[updateID-1].price = updatePrice;
				}
				if (updateOption == 3)
				{
					printf("\nEnter update quantity:\t");
					scanf("%d", &updateQuantity);

					list[updateID - 1].quantity = updateQuantity;
				}
			}
			else 
			{
				int temp = 0;
				printf("No product\n 0. Exit 1. Return\n");
				scanf("%d", &temp);
				if (temp != 1) { system("cls"); printf("you stupid"); break; }
			}
			option = 0;
		}
		if (option == 4) /* Search by name */
		{
			// Input searched name, compare char by char (without whitespace), return the product info in the console
			// Input name for search, convert to lowercase
			int goBack = 1;
			char searchName[30] = { 0 };

			printf("Enter a search name:\t");
			scanf("%29[^\n]", &searchName);

			int temp = 0;

			Product* comparedProduct = NULL;
			char comparedName[29] = { 0 };
			temp = 0;

			// Check for substring
			for (int i = 0; i < ilosc_prod; i++)
			{
				comparedProduct = &list[i];

				strncpy(comparedName,comparedProduct->name, 29);

				if (strstr(comparedName, searchName))
				{
					printf("\nName: %s\n ID: %d\n Price: %d\n Quantity: %d\n", comparedProduct->name, comparedProduct->id, comparedProduct->price, comparedProduct->quantity);
				}
			}
			printf("0. Exit \t1. Return\n");
			scanf("%d", &goBack);
			if (goBack != 1) { system("cls"); printf("IDK:\t %d \tyou stupid", goBack); buffor = NULL; break; }
			option = 0;

		}
		if (option == 5) /* List products */
		{
			int idk = 1;
			printf("List of products:\n");
			for (int item = 0; item < ilosc_prod; item++)
			{
				Product* currentProduct = &list[item];
				printf("\nName: %s\n ID: %d\n Price: %d\n Quantity: %d\n", currentProduct->name, currentProduct->id, currentProduct->price, currentProduct->quantity);
			}
			printf("0. Exit \t1. Return\n");
			scanf("%d", &idk);
			
			if (idk != 1) { system("cls"); printf("IDK:\t %d \tyou stupid", idk); buffor = NULL; break; }
			option = 0;
		}
		if (option == 6) /* Total value of products */
		{
			// Take the price of procudt entry, multiply by amount, add to total sum
			int idk = 1;
			int totalSum = 0;

			for (int i = 0; i < ilosc_prod; i++)
			{
				totalSum = totalSum + (list[i].price * list[i].quantity);
			}

			printf("Value: %d\n", totalSum);

			printf("0. Exit \t1. Return\n");
			scanf("%d", &idk);

			if (idk != 1) { system("cls"); printf("IDK:\t %d \tyou stupid", idk); buffor = NULL; break; }
			option = 0;
		}
	}
	free(list);
	free(buffor);
}