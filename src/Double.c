#include "Double.h"

void copyDouble(void *dest , void *source)
{
	int *sourceDouble = (int *)source;
	char *headPtr = (char *)dest;
	
	*headPtr = *sourceDouble; 
}