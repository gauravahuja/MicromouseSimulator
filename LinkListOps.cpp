/*
	FileName = LinkListOps.c
	Implents the Functions defined in LinkListOps.h
*/
#include "stdafx.h"
#include <stdio.h>
#include <cstdlib>
#include "Element.h"
#include "ElementOps.h"
#include "Node.h"
#include "LinkList.h"
#include "LinkListOps.h"

LinkList CreateLinkList()
{
	LinkList Temp;
	Temp.Head = NULL;
	Temp.Size = 0;
	return Temp;
}
Link FindMax(Link StartNode)
{
	Element EMax;
	
	EMax = StartNode->E;
	Link MaxElementNode = StartNode;
	Link CurrentNode = StartNode->Next;
	while(CurrentNode != NULL)
	{
		if(Compare(CurrentNode->E, EMax) == Greater)
		{
			EMax = CurrentNode->E;
			MaxElementNode = CurrentNode;
		}
		CurrentNode = CurrentNode->Next;
	}
	return MaxElementNode;
}

LinkList Sort(LinkList List)
{
	unsigned int i;
	Link CurrentNode;
	Link MaxNode;
	Element Temp;
	
	CurrentNode = List.Head;

	for(i = 0; i < List.Size; i++)
	{
		MaxNode = FindMax(CurrentNode);
		Temp = MaxNode->E;
		MaxNode->E = CurrentNode->E;
		CurrentNode->E = Temp;
		CurrentNode = CurrentNode->Next;
	}
	return List;	
}

LinkList Insert(LinkList List, Element E)
{
	Link NewNode = new Node;//(Link)malloc(sizeof(Node));
	if(NewNode == NULL)
		return List;
	NewNode->E = E;
	NewNode->Next = List.Head;
	NewNode->Back = NULL;
	List.Head = NewNode;
	List.Size++;
	return List;
}

LinkList DeleteAtPos(LinkList List, unsigned int Pos)
{
	unsigned int i = 0;
	if((Pos > List.Size)||(Pos == 0))
	{
		//printf("\nInvalid Position\n");
		return List;
	}
	Pos--;
	Link NodeToDelete = NULL;
	Link Temp = NULL;
	if(Pos == 0)
	{
		NodeToDelete = List.Head;
		List.Head = NodeToDelete->Next;
		free(NodeToDelete);
	}
	else
	{
		Temp = List.Head;
		for(i = 1; i < Pos; i++)
		{
			Temp = Temp->Next;
		}
		NodeToDelete = Temp->Next;
		Temp->Next = NodeToDelete->Next;
		free(NodeToDelete);
	}
	List.Size--;
	return List;
}	

unsigned int Search(LinkList List, Element E)
{
	int Pos = 0;
	Link CurrentNode = NULL;
	CurrentNode = List.Head;
	while(CurrentNode != NULL)
	{
		Pos++;
		if(Compare(E, CurrentNode->E) == Equal)
		{
			return Pos;
		}
		CurrentNode = CurrentNode->Next;
	}
	return 0;
}
			
LinkList DeleteList(LinkList List)
{
	unsigned int i;
	unsigned int Size = List.Size;
	for(i = 0; i < Size; i++)
	{
		List = DeleteAtPos(List, 1);
	}
	List.Head = NULL;
	return List;
}
		
	
	
