#include "Integer.h"

void copyInt(void *dest , void *source)
{
	int *sourceInt = (int*) source;
	char *headPtr = (char *)dest;
	
	*headPtr = *sourceInt;
}