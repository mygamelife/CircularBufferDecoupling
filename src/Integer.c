#include "Integer.h"

void copyInt(void *dest , void *source)
{
	int *sourceInt = (int*) source;
	int *headPtr = (int *)dest;
	
	*headPtr = *sourceInt;
}