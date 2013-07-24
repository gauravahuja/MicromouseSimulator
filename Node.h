/*
	FileName = Node.h
	Define the Node of the list
	Node will have the abilty to point in two directions
*/
#ifndef _Node_H

#define _Node_H

#include "Element.h"

struct Node;
typedef Node* Link;

struct Node
{
	Element E;
	Link Next;
	Link Back;
};

#endif

