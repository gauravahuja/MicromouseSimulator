/*
	FileName = LinkListOps.h
	Defines the implementation for the linklist
*/
#ifndef _LinkListOps_H

#define _LinkListOps_H

#include "LinkList.h"
#include "Element.h"

extern LinkList CreateLinkList();				//Returns an empty LinkList
extern LinkList DeleteAtPos(LinkList List, unsigned int Pos);
extern LinkList Insert(LinkList List, Element E);		//Inserts Element E to the beginning of the list
extern LinkList DeleteList(LinkList List);			//Deletes the entire list
extern unsigned int Search(LinkList List, Element E);		//Returns the Position of the Element in the List relative to 1, Returns 0 if not found
extern LinkList Sort(LinkList List);				//Sorts the List in Ascending order

#endif
