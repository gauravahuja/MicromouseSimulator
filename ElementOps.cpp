/*
	FileName = ElementOps.c
	Implement the functions defined in ElementOps.h
*/
#include "stdafx.h"
#include <stdio.h>
#include "ElementOps.h"
#include "Element.h"

int Compare(Element E1, Element E2)
{
	if(E1.Value > E2.Value)
		return Greater;
	else if(E1.Value < E2.Value)
		return Less;
	return Equal;
}
