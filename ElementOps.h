/*
	FileName = ElementOps.h
	Defines the Operations that can be done on the Element
*/
#ifndef _ElementOps_H

#define _ElementOps_H

#include "Element.h"
#define Greater	1
#define Less	2
#define Equal	0

extern int Compare(Element E1, Element E2);	//Returns Greater if E1 > E2, Less if E1 < E2, Equal if E1 == E2

#endif
