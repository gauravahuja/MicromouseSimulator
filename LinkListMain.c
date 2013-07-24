/*
	FileName = LinkListMain.c
*/

#include <stdio.h>
#include <stdlib.h>

#include "Element.h"
#include "ElementOps.h"
#include "LinkList.h"
#include "LinkListOps.h"

void Wait()
{
	printf("\nPress any key to continue...\n");
	getchar();
}


int main()
{
	LinkList List;
	Element Temp;
	char ch;
	unsigned int i;
	do
	{
		printf("\n\nMenu\n");
		printf("\n1.\tCreateList");
		printf("\n2.\tInsert");
		printf("\n3.\tInsert and Sort");
		printf("\n4.\tSearch");
		printf("\n5.\tPrintList");
		printf("\n6.\tDelete Element");
		printf("\n7.\tSort in Descending Order");
		printf("\n8.\tDelete List");
		printf("\n0.\tExit\n");
		printf("\nEnter Your Choice\t: ");
		scanf("%c", &ch);
		switch(ch)
		{
			case '1':
				List = CreateLinkList();
				Wait();
				break;
			case '2':
				Temp = InputElement();
				List = Insert(List, Temp);
				Wait();
				break;
			case '3':
				Temp = InputElement();
				List = InsertToSorted(List, Temp);
				Wait();
				break;

			case '4':
				Temp = InputElement();
				printf("\nFound at Postion\t: %d\n",Search(List,Temp));
				Wait();
				break;
			case '5':
				PrintLinkList(List);
				Wait();
				break;
			case '6':
				printf("\nEnter the Postion of Element to Delete\t: ");
				scanf("%d", &i);
				List = DeleteAtPos(List, i);
				Wait();
				break;
			case '7':
				printf("\nSorting...\n");
				List = Sort(List);
				printf("\nList ha been sorted.\n");
				Wait();
				break;
			case '8':
				List = DeleteList(List);
				printf("\nThe List has been deleted\n");
				Wait();
				break;
			default:
				break;
		}
	}while(ch != '0');
	printf("\nBye!!\n\n");
	return 0;
}

				
